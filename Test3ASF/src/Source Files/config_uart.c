/*
 * config_uart.c
 *
 * Created: 05/02/2018 15:20:12
 *  Author: eleve
 */ 

#include "../Header/appli.h"

#include <string.h>

//#define USART_SERIAL					USART0
//#define USART_SERIAL_ID					ID_USART0
//#define USART_SERIAL_BAUDRATE			115200
//#define USART_SERIAL_CHAR_LENGTH		US_MR_CHRL_8_BIT
//#define USART_SERIAL_PARITY				US_MR_PAR_NO
//#define USART_SERIAL_STOP_BIT			US_MR_NBSTOP_1_BIT
//
//#define USART_SERIAL_TXD_PIN			PIN_USART0_TXD
//#define USART_SERIAL_TXD_IDX			PIN_USART0_TXD_IDX
//#define USART_SERIAL_TXD_FLAGS			PIN_USART0_TXD_FLAGS
//
//#define USART_SERIAL_RXD_PIN			PIN_USART0_RXD
//#define USART_SERIAL_RXD_IDX			PIN_USART0_RXD_IDX
//#define USART_SERIAL_RXD_FLAGS			PIN_USART0_RXD_FLAGS
//
//const sam_usart_opt_t usart_console_settings = {
	//USART_SERIAL_BAUDRATE,
	//USART_SERIAL_CHAR_LENGTH,
	//USART_SERIAL_PARITY,
	//USART_SERIAL_STOP_BIT,
	//US_MR_CHMODE_NORMAL
//};



char shellcomTxBuf[SHELLCOM_TXBUF_LEN];
char shellcomRxBuf[SHELLCOM_RXBUF_LEN+2];		//+2 pour pouvoir placer 2 caratères '\0' en fin de saisie de commande : nécessaire pour le traitement !

char shellcomEscSeqBuf[SHELLCOM_ESCSEQBUF_LEN];

#define ST_SHELL_MODE_INSERT	0x000001


typedef enum {
	IDLE	=0,
	ESCAPE,
	ESCAPE_SEQUENCE,
	EDITION,
	ED_ESCAPE,
	ED_ESCAPE_SEQUENCE,
	EXECUTE
}t_state;

struct {
	char*		pTxWrite;
	char*		pTxRead;
	char*		pEdit;
	char*		pEnd;
	char*		pEscSeq;
	t_state		state;
	uint32_t	escTimer;
	uint32_t	editTimer;
	uint16_t	crc;
	uint16_t	nbChar;
	uint16_t	nStatus;
} shellcom;


typedef void(*t_ptfVV)(void*);


typedef struct tt_cmdEntry{
	uint16_t	hashCode;
	t_ptfVV	pCmdFunc;
}t_cmdEntry;




const char separators[]=" :/;,\t.";

///////// PRIVATE SERVICES CODES /////////////////////////////////////////////////////////////////////////////////
enum{
	_SHELLCOM_KBHIT	= 1,
	_SHELLCOM_PUTHEXA,
	_SHELL_TIMER = 3,
	_SHELL_CHECK_SEPARATORS,
	_SHELL_CLEANUP_CMDLINE
};

#define _CheckSeparators(pSep,ch)		Shellcom(_SHELL_CHECK_SEPARATORS,(uint32_t)pSep,(uint32_t)ch)


uint32_t Shellcom(void)
{

	usart_enable_tx(USART0);
	usart_enable_rx(USART0);
	//usart_putchar(USART_SERIAL, 'a');
	
	
	return 0;
}

//
//void USART0_Handler()
//{
	//uint32_t dw_status = usart_get_status(USART_SERIAL);
	////if(usart_is_rx_ready(USART_SERIAL)) {
//
	//if (dw_status & US_CSR_RXRDY)
	//{
		////PushTask(Shellcom,_SHELLCOM_KBHIT,USART_SERIAL->US_RHR & US_RHR_RXCHR_Msk,0);
	//}
//
	//if (dw_status & US_CSR_TXRDY)
	//{
		//if(shellcom.pTxRead!=shellcom.pTxWrite)
		//{
			////usart_putchar(USART_SERIAL,*shellcom.pTxRead++);
			//USART_SERIAL->US_THR = US_THR_TXCHR(*shellcom.pTxRead++);
			//if(shellcom.pTxRead>=shellcomTxBuf+SHELLCOM_TXBUF_LEN) shellcom.pTxRead=shellcomTxBuf;
		//}
		//else
		//{
			//usart_disable_interrupt(USART_SERIAL,US_IER_TXRDY);
		//}
	//}
//}

