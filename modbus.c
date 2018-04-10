/*
 * modbus.c
 *
 * Created: 23/03/2018 22:16:15
 *  Author: Thierry
 */

#include "kernel.h"
#include "CRC16MODBUS.h"

#include "modbus_private.h"

 uint32_t*	const registerMap[]={
	&RTC->RTC_TIMR,		//RTC Time Register
	&RTC->RTC_CALR,		//RTC Calendar Register
};

uint32_t Modbus(uint32_t sc,...)
{
	switch(sc)
	{
	case MODBUS_NEW:
#define _moduleAddr		((char)pa1)
		modbus.reg=0;
		if((modbus.moduleAddr=_moduleAddr)==0) mBitsSet(modbus.status,ST_MODULE_IS_MASTER);
#undef _moduleAddr
		break;

	case MODBUS_WRITE_MULTIPLE_REGISTERS:
#define _slaveAddr			((char)pa1)
#define _startingAddr		((uint16_t)pa2)
#define _registerQty		((uint16_t)pa3)
#define _dataPtr			((uint16_t*)pa4)
#define _pModbusTxFramePtr	((t_modbusFrame*)sc)
		sc=rs485_GetBufPtr();
		modbus.crc=CRC16MODBUSbyte((_pModbusTxFramePtr->moduleAddr=_slaveAddr),0xFFFF);
		modbus.crc=CRC16MODBUSbyte((_pModbusTxFramePtr->functionCode=WRITE_MULTIPLE_REGISTERS),modbus.crc);
		modbus.crc=CRC16MODBUSword((_pModbusTxFramePtr->writeMultipleRegister_header.startingAddr=swap16(_startingAddr)),modbus.crc);
		modbus.crc=CRC16MODBUSword((_pModbusTxFramePtr->writeMultipleRegister_header.registerQty=swap16(_registerQty)),modbus.crc);
		modbus.crc=CRC16MODBUSbyte((_pModbusTxFramePtr->writeMultipleRegister_header.byteCount=_registerQty*2),modbus.crc);
#undef _startingAddr
#define _k	pa2
		for (_k=0;_k<_registerQty;_k++)
		{
			modbus.crc=CRC16MODBUSword((_pModbusTxFramePtr->writeMultipleRegister_header.dataField[_k]=swap16(_dataPtr[_k])),modbus.crc);
		}
		_pModbusTxFramePtr->writeMultipleRegister_header.dataField[_k]=swap16(modbus.crc);
		rs485_Send(_registerQty*2+9,(_slaveAddr!=MODBUS_BROADCAST_ADDRESS));
#undef _slaveAddr
#undef _registerQty
#undef _dataPtr
#undef _pModbusTxFramePtr
#undef _k
		break;

	/// PRIVATE SERVICE IMPLEMENTATION ////////////////////////////////////////////////////////////////////
	case _MODBUS_PROCESS_RECEIVED_FRAME:
		if(IsMaster())
		{
			LcdPutstr("_MODBUS_IS_MASTER   ",3,0);
			rs485_FlushRx();
		}
		else
		{
#define _pModbusRxFramePtr	((t_modbusFrame*)sc)
			sc=rs485_GetBufPtr();
			if((_pModbusRxFramePtr->moduleAddr!=modbus.moduleAddr)&&(_pModbusRxFramePtr->moduleAddr!=MODBUS_BROADCAST_ADDRESS))
			{
				LcdPutstr("_MODBUS_SLAVE_FLUSH ",3,0);
				rs485_FlushRx();
				return 0;
			}
			if(_pModbusRxFramePtr->moduleAddr!=MODBUS_BROADCAST_ADDRESS) mBitsSet(modbus.status,ST_FRAME_ACK_REQ);
			switch(_pModbusRxFramePtr->functionCode)
			{
			case WRITE_MULTIPLE_REGISTERS:
				switch(swap16(_pModbusRxFramePtr->writeMultipleRegister_header.startingAddr))
				{
				case MODBUS_SYNCRONIZATION_TOKEN:
					while ((RTC->RTC_SR & RTC_SR_SEC) != RTC_SR_SEC);
					RTC->RTC_CR |= (RTC_CR_UPDTIM | RTC_CR_UPDCAL) ;
					while ((RTC->RTC_SR & RTC_SR_ACKUPD) != RTC_SR_ACKUPD);
					RTC->RTC_SCCR = RTC_SCCR_ACKCLR;
					_pModbusRxFramePtr->writeMultipleRegister_header.dataField[0]=swap16(_pModbusRxFramePtr->writeMultipleRegister_header.dataField[0]);
					_pModbusRxFramePtr->writeMultipleRegister_header.dataField[1]=swap16(_pModbusRxFramePtr->writeMultipleRegister_header.dataField[1]);
					_pModbusRxFramePtr->writeMultipleRegister_header.dataField[2]=swap16(_pModbusRxFramePtr->writeMultipleRegister_header.dataField[2]);
					_pModbusRxFramePtr->writeMultipleRegister_header.dataField[3]=swap16(_pModbusRxFramePtr->writeMultipleRegister_header.dataField[3]);
					*registerMap[0]=*(uint32_t*)&_pModbusRxFramePtr->writeMultipleRegister_header.dataField[0];
					*registerMap[1]=*(uint32_t*)&_pModbusRxFramePtr->writeMultipleRegister_header.dataField[2];
					RTC->RTC_CR &= ((~RTC_CR_UPDTIM)&(~RTC_CR_UPDCAL));
					if(mIsBitsSet(modbus.status,ST_FRAME_ACK_REQ))
					{
						
					}
					rs485_FlushRx();
					Putstr("\r\n\tMODBUS_SYNCRONIZATION_TOKEN\r\n\n");
					break;
				default:
					rs485_FlushRx();
					break;
				}
				break;
			case READ_HOLDING_REGISTERS:
				//break;	
			default:
				rs485_FlushRx();
				break;
			}

#undef _pModbusRxFramePtr
		}
		break;


	///// DEFAULT SWITCH BAD SC ERROR TRAP ////////////////////////////////////////////////////////////////
	default:
		Error(ERROR_MODBUS_SWITCH_BAD_SC,sc);
	}


	return 0;
}

