/*
 * comRS485.c
 *
 * Created: 23/03/2018 19:00:52
 *  Author: Thierry
 */

#include "kernel.h"
#include "CRC16MODBUS.h"

extern const char hexDigits[];
extern char buf[];

typedef enum{
	IDLE = 1,
	RX_WAITING_BACK_ANWSER,
	RX_WAITING_END_FRAME
}t_state;

struct {
	char*		pWrite;
	char*		pRead;
	uint16_t	crcA,crcB,crcC;
	uint16_t	recCrc;
	uint16_t	timer;
	t_state		state;
	uint16_t	nChar;
}comRS485;

#define COMRS485_BUFFER_GUARD	2

static char comRS485TxRxBuf[COMRS485_TXRX_BUFFER_LEN+COMRS485_BUFFER_GUARD];

const sam_usart_opt_t usart_console_settings = {
	COMRS485_BAUDRATE,
	COMRS485_CHAR_LENGTH,
	COMRS485_PARITY,
	COMRS485_STOP_BIT,
	US_MR_CHMODE_NORMAL
};

/// PRIVATE SERVICE CODES ////////////////////////////////////////////////////////////////////////
enum{
	_COMRS485_TIMER = 1
};


uint32_t ComRS485(uint32_t sc, ...)
{
	switch(sc)
	{
	case COMRS485_NEW:
		rs485_FlushRx();
		comRS485.timer = 0;

		sysclk_enable_peripheral_clock(COMRS485_USART_ID);
		usart_init_rs485(COMRS485_USART, &usart_console_settings, sysclk_get_cpu_hz());
		gpio_configure_pin(COMRS485_TX,		COMRS485_TX_FLAGS);
		gpio_configure_pin(COMRS485_RX,		COMRS485_RX_FLAGS);
		gpio_configure_pin(COMRS485_TXEN,	COMRS485_TXEN_FLAGS);
		usart_disable_interrupt(COMRS485_USART,0xFFFFFFFF);
		usart_enable_interrupt(COMRS485_USART, US_IER_RXRDY);
		NVIC_EnableIRQ(COMRS485_USART_ID);
		usart_enable_tx(COMRS485_USART);
		usart_enable_rx(COMRS485_USART);
		Putstr("\r\n\tCOMRS485_NEW:\r\n");
		break;

	case COMRS485_FLUSH_RX:
		comRS485.state=IDLE;
		comRS485.pRead=comRS485.pWrite=comRS485TxRxBuf;
		comRS485.crcA=0xFFFF;
		comRS485.nChar=0;
		break;

	case COMRS485_FLUSH_TX:
		comRS485.pRead=comRS485.pWrite=comRS485TxRxBuf;
		break;

	case COMRS485_SEND:
#define _frameLen	pa1
#define _needAck	pa2
		Putstr("\r\n========================================================\r\n");
		Puthexacode(comRS485TxRxBuf,_frameLen);
		Putstr("\r\n========================================================\r\n");		
		comRS485.pWrite+=_frameLen;
		if(_needAck)
		{
			comRS485.state=RX_WAITING_BACK_ANWSER;
			comRS485.timer=COMRS485_TX_TRY_TIMEOUT_VAL;
		}
		usart_enable_interrupt(COMRS485_USART,US_IER_TXRDY);
#undef _frameLen
#undef _needAck
		break;

	case COMRS485_GET_BUF_PTR:
		return comRS485TxRxBuf;
		//no break;

	/// PRIVATE SERVICE IMPLEMENTATION ////////////////////////////////////////////////////////////////////

	/// MODBUS PRIVATE SERVICE CODES //////////////////////////////////////////////
	enum{
		_MODBUS_PROCESS_RECEIVED_FRAME = 1
	};

	case _COMRS485_TIMER:
		if(comRS485.timer)
		{
			if(--comRS485.timer==0)
			{
				switch(comRS485.state)
				{
				case RX_WAITING_END_FRAME:
					//LcdPutstr("_COMRS485_TIMER     ",3,0);
					Putstr("\r\n========================================================\r\n");
					Puthexacode(comRS485TxRxBuf,comRS485.nChar);
					sprintf(buf,"\trecCrc:%04X crcC:%04X ",comRS485.recCrc,comRS485.crcC);
					Putstr(buf);
					Putstr("\r\n========================================================\r\n");
					
					if(comRS485.recCrc==comRS485.crcC)
						PushTask(Modbus,_MODBUS_PROCESS_RECEIVED_FRAME,0,0);
					else
					{
						LcdPutstr("_COMRS485_RECV_FLUSH",3,0);
						rs485_FlushRx();
					}
					break;
				case RX_WAITING_BACK_ANWSER:
					rs485_FlushRx();
					break;
				default:
					rs485_FlushRx();
					break;
				}
			}
		}
		break;


	///// DEFAULT SWITCH BAD SC ERROR TRAP ////////////////////////////////////////////////////////////////
	default:
		Error(ERROR_COMRS485_SWITCH_BAD_SC, sc);
	}


	return 0;
}


void COMRS485_Handler()
{
	uint32_t dw_status = usart_get_status(COMRS485_USART);
	uint8_t dummy;
	
	if((mIsBitsSet(COMRS485_USART->US_IMR,US_IMR_RXRDY))&&(dw_status & US_CSR_RXRDY))
	{
#ifdef MASTER
		if(comRS485.state!=RX_WAITING_BACK_ANWSER)
		{
			dummy = COMRS485_USART->US_RHR & US_RHR_RXCHR_Msk;
			return;
		}
		dummy = COMRS485_USART->US_RHR & US_RHR_RXCHR_Msk;
		return;
#else
		comRS485.state=RX_WAITING_END_FRAME;
		comRS485.timer=COMRS485_RX_TIMEOUT_VAL;
		*comRS485.pWrite=COMRS485_USART->US_RHR & US_RHR_RXCHR_Msk;
		comRS485.crcC=comRS485.crcB;
		comRS485.crcB=comRS485.crcA;
		comRS485.crcA=CRC16MODBUSbyte(*comRS485.pWrite,comRS485.crcA);
		comRS485.recCrc<<=8;
		comRS485.recCrc&=0xFF00;
		comRS485.recCrc|=*comRS485.pWrite;
		comRS485.nChar++;
		if(++comRS485.pWrite>=comRS485TxRxBuf+COMRS485_TXRX_BUFFER_LEN+COMRS485_BUFFER_GUARD) /*comRS485.pWrite=comRS485TxRxBuf;*/
		/*if(comRS485.pWrite==comRS485.pRead)*/ Error(ERROR_COMRS485_RX_BUFFER_FULL,0);
#endif	
	}

	
	if((mIsBitsSet(COMRS485_USART->US_IMR,US_IMR_TXRDY))&&(dw_status & US_CSR_TXRDY))
	{
		if(comRS485.pRead!=comRS485.pWrite)
		{
			COMRS485_USART->US_THR = US_THR_TXCHR(*comRS485.pRead++);
			if(comRS485.pRead>=comRS485TxRxBuf+COMRS485_TXRX_BUFFER_LEN+COMRS485_BUFFER_GUARD) /* comRS485.pRead=comRS485TxRxBuf;*/
			{
				usart_disable_interrupt(COMRS485_USART,US_IER_TXRDY);
				rs485_FlushTx();
				Putstr("\r\n");
			}
		}
		else
		{
			usart_disable_interrupt(COMRS485_USART,US_IER_TXRDY);
			rs485_FlushTx();
			Putstr("\r\n");
		}
	}
}