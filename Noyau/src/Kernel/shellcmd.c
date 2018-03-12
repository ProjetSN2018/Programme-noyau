/*
 * shellcmd.c
 *
 * Created: 07/02/2018 17:29:14
 *  Author: Mod_loc
 */ 
 #include <string.h>

#include "./Headers/appli.h"
#include "shellcmd.h"
#include "CRC16MODBUS.h"


const t_cmdEntry _cmdEntries[] ={
	{ 0x6CAB, _cmd_set		},		//set	
	{ 0xAAF6, _cmd_show		},		//show
	{ 0x10E1, _cmd_menu },			//menu
	

	//////////////////LIST TERMINATOR ////////////////////////////
	{	0,	NULL			}	
};


uint32_t u1, u2, u3, u4;

void _cmd_set(uint32_t sc, void* pParam)
{
	uint16_t crc;
#define pToken sc
	pToken = (uint32_t)strtok(pParam, " \r\n");
	if(pToken)
	{
		crc = CRC16MODBUSFRAME((unsigned char*)pToken, strlen((char*)pToken));
		switch(crc)
		{
		case 0x7327:			//time
#define hh	u1
#define mn	u2
#define sec	u3
			pToken = strtok(NULL, " : \r\n");
			if(pToken) hh = atoi(pToken);
			pToken = strtok(NULL, " : \r\n");
			if(pToken) mn = atoi(pToken);
			pToken = strtok(NULL, " : \r\n");
			if(pToken) sec = atoi(pToken);
			rtc_set_time(RTC, hh, mn, sec);
			gpio_set_pin_high(PIO_PA16_IDX);
#undef  hh
#undef	mn
#undef	sec
			break;

		case 0xE1A9:			//date
#define yr	u1
#define mm	u2
#define dd	u3
#define wk	u4
			pToken = strtok(NULL, " : \r\n");
			if(pToken) yr = atoi(pToken);
			pToken = strtok(NULL, " : \r\n");
			if(pToken) mm = atoi(pToken);
			pToken = strtok(NULL, " : \r\n");
			if(pToken) dd = atoi(pToken);
			pToken = strtok(NULL, " : \r\n");
			if(pToken) wk = atoi(pToken);
			rtc_set_date(RTC, yr, mm, dd, wk);

#undef  yr
#undef	mm
#undef	dd
#undef	wk
			break;
		default:
			sprintf(buf,"\r\nunknown cmd: %04X\r\n",crc);
			Putstr(buf);
			break;
		}		
#undef pToken
	}
	

	
}

void _cmd_show(uint32_t sc, void* pParam)
 {
	if(ioport_get_pin_level(PIN_LED_IDX))
	{
		sprintf(buf, "L'etat de la broche etait haut \r\n");
		ioport_set_pin_level(PIN_LED_IDX,0);
		Putstr(buf);
	}
	else
	{
	sprintf(buf, "L'etat de la broche etait bas \r\n");
	ioport_set_pin_level(PIN_LED_IDX,1);
	Putstr(buf);

	}
	//sprintf(buf, "Hello!!! \r\n");
	//Putstr(buf);
	uint32_t data_read[4];
	//if(nvm_init(INT_FLASH) == STATUS_OK);
	if(nvm_read(INT_FLASH, TEST_ADDRESS_INT, (void *)data_read, sizeof(data_read))
	== STATUS_OK) {
		//Check read content
		if(data_read[0] == 0xAA)
		{
			sprintf(buf, "NO DATA FOUND\r\n");
			Putstr(buf);
			LcdPutstr(buf, 2, 0);
		}
		else
		{
			sprintf(buf, "%d/%d/%d/%d\r\n",data_read[0], data_read[1], data_read[2], data_read[3]);
			Putstr(buf);
			LcdPutstr(buf, 2, 0);
		}
	}
 }

 void _cmd_menu(uint32_t sc, void* pParam)
 {
	uint16_t crc;
#define pToken sc
	pToken = (uint32_t)strtok(pParam, " \r\n");
	if(pToken)
	{
		crc = CRC16MODBUSFRAME((unsigned char*)pToken, strlen((char*)pToken));
		switch(crc)
		{
		case 0x8B8B:			//switch
			Menu(MENU_SWITCH_BUTTON);
			break;
		case 0x8862:			//select
			Menu(MENU_SELECT_BUTTON);
			break;	
		default:
			Error(ERR_SHELL_CMD_MENU_SWITCH_BAD_SC, sc);
			break;		
		}
#undef pToken
	}
	

 }

 