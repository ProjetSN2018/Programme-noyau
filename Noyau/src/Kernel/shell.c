/*
 * shell.c
 *
 * Created: 06/02/2018 17:19:43
 *  Author: eleve
 */ 

#include <string.h>

#include "./Headers/appli.h"
#include "CRC16MODBUS.h"
#include "shellcmd.h"

 char shellBuf[SHELL_EDIT_BUFFER_LEN];
 char shellEscSeq[SHELL_ESCSEQ_BUFFER_LEN];
 
typedef enum { 
	IDLE = 0, 
	EDITION, 
	EXECUTION, 
	ESCAPE, 
	ESCAPE_SEQ,
	ED_ESCAPE,
	ED_ESCAPE_SEQ
} t_state;

 struct{
	t_state		state;
	uint32_t	nStatus;
	char*		pEdit;
	uint32_t	nbChar;
	uint16_t	crc;
 }shell;

const uint32_t flashSequ[]={
	50,500,50,1200,0
};
 //////Nicely shortcuts........ ///////////////////
#define nStatus		shell.nStatus
#define pEdit		shell.pEdit
#define nbChar		shell.nbChar
#define crc			shell.crc 
#define state		shell.state		


/////Shell Private services codes ////////////////////
enum{
	_SHELL_KBHIT = 1,
	_SHELL_HEARTBEAT,
	_SHELL_ESC_KBHIT,
	_SHELL_PROMPT
}; 

////////////////////RTC//////////////////////////////////////////////////////////////
enum { JANUARY=0, 
	FEBRUARY, 
	MARCH, 
	APRIL, 
	MAY, 
	JUNE, 
	JULY, 
	AUGUST, 
	SEPTEMBER, 
	OCTOBER, 
	NOVEMBER, 
	DECEMBER 
};

enum { SUNDAY=0, 
	MONDAY, 
	TUESDAY, 
	WEDNESDAY, 
	THURSDAY, 
	FRIDAY, 
	SATURDAY 
};

const uint8_t nbDaysInMonth[] ={31,28,31,30,31,30,31,31,30,31,30,31};

const char* daysOfWeek[] ={
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

const char* months[] ={
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

const char* thhh[]={
	"th",
	"st",
	"nd",
	"rd"
};


uint8_t __RTCdayByDate(uint32_t date, uint32_t month, uint32_t centYear);
bool	__RTCIsLeapYear(uint32_t centYear);
bool __RTCIsSummerTime(uint32_t day, uint32_t date, uint32_t month, uint32_t hours);



//////////////////////////////////////////////////////////////////////////////////////
 uint32_t Shell(uint32_t sc, ...)
 {
	 uint32_t u1;
	 uint32_t u2;
	 uint32_t hh;
	 uint32_t mn;
	 uint32_t sec;

	switch(sc)
	{
	case SHELL_NEW:
		gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
		gpio_set_pin_low(LED0_GPIO);
		Shellcom(SHELLCOM_NEW);
		state = IDLE;
		
		sysclk_enable_peripheral_clock(ID_RTC);
		
		rtc_set_hour_mode(RTC, 0);
		rtc_set_time(RTC, 1, 2, 3);
		//rtc_enable_interrupt(RTC,RTC_TIMR_SEC_Msk);
		PushTask(Shell,_SHELL_HEARTBEAT,0,0);
		PushTask(Shell,_SHELL_PROMPT,0,500);
		PushTask(Appli, APPLI_NEW, 0, 500);
		break;

	////Private services implementation ///////////////////////////////
	case _SHELL_KBHIT:
#define _kbhitChar ((char)pa1)
		switch(state)
		{
		case IDLE:
			switch(_kbhitChar)
			{
			case '\e':
				break;
			case ' ':
			case '\t':
			case '\b':
			case '\r':
			case '\n':
				break;	
			default:
				Putstr("\r\n>");
				pEdit = shellBuf;
				*pEdit++ = _kbhitChar;
				nbChar = 1;
				Putch(_kbhitChar);
				state = EDITION;
				
				break;
			}
			break;
		case ESCAPE:
			break;
		case ESCAPE_SEQ:
			break;
		case EDITION:
			switch(_kbhitChar)
			{
			case '\e':
				//state = _SHELL_KBHIT;
				break;
			case '\t':
			case '\b':
			case '\n':
				break;
			case '\r':
				*pEdit++ = '\0';
				state = EXECUTION;
				PushTask(Shell, _SHELL_KBHIT, 0, 0);
				break;
			default:
				if(nbChar < SHELL_EDIT_BUFFER_LEN - 2)
				{
					*pEdit++ = _kbhitChar;
					nbChar++;
					Putch(_kbhitChar);
				}
				break;
			}
			break;
		case ED_ESCAPE:
			break;
		case ED_ESCAPE_SEQ:
			break;
		case EXECUTION:
			Putstr("\r\n>>>");
			Putstr(shellBuf);
			Putstr("\r\n");
#define pToken sc
			pToken = (uint32_t)strtok(shellBuf, " \r\n");
			if(pToken)
			{
				crc = CRC16MODBUSFRAME(pToken, strlen(pToken));

#define k u1
				k = 0;
				while(_cmdEntries[k].cmdCode && (_cmdEntries[k].cmdCode != crc)) k++;
				if(_cmdEntries[k].pCmdFunc)
				{
					_cmdEntries[k].pCmdFunc(0, shellBuf + strlen(pToken) + 1);
				}
				else
				{
					sprintf(buf,"\r\nunknown cmd: %04X\r\n",crc);
					Putstr(buf);
				}
#undef k
#undef pToken	
			}

			state = IDLE;
			break;
		default:
			Putch(_kbhitChar);
			break;
		}
#undef _kbhitChar
		break;
		
		
		
	case _SHELL_HEARTBEAT:
#define k	pa1
		k++; if(flashSequ[k]==0) k=0;
		if(k%2==0) gpio_set_pin_high(LED0_GPIO);
		else gpio_set_pin_low(LED0_GPIO);
		PushTask(Shell,_SHELL_HEARTBEAT,k,flashSequ[k]);
#undef k
		break;

	case _SHELL_PROMPT:
		if(state==IDLE)
		{
			
			rtc_get_time(RTC, &hh, &mn, &sec);
			sprintf(buf, "\r\e[k\r%02d:%02d:%02d", hh, mn, sec);
			//Putstr(buf);
#define yr	u1
#define mm	hh
#define dd	mn
#define wk	sec
#define day	u2
			rtc_get_date(RTC, &yr, &mm, &dd, &wk);
			day = __RTCdayByDate(dd, mm, yr/100);
			sprintf(buf, "	%s %02d %s %02d", daysOfWeek[day - 3], dd, months[mm-1], yr);
			//Putstr(buf);
#undef  yr
#undef	mm
#undef	dd
#undef	wk
		}
		PushTask(Shell,_SHELL_PROMPT,0,300);
		break;
		
		
	////////////////////////////////////////////////////////////////////////////////////////////////	
	default:
		Error(ERR_SHELL_SWITCH_BAD_SC,sc);
	}

	return 0;
 }


 void RTC_Handler(void )
 {
	//PushTask(Shell,_SHELL_PROMPT,0,0);
 }
  
 uint8_t __RTCdayByDate(uint32_t date, uint32_t month, uint32_t centYear)
 {
	uint8_t  D; //Day of the week
#define y   centYear
	//Mike Keith algorithme ----------------------------------------------------------------//
	if(month>=3)
	{
		D = ( ((uint16_t)month*23)/9 + date + 4 + y + y/4 - y/100 + y/400 - 2 ) % 7 + 1;
	}
	else
	{
		D = ( ((uint16_t)month*23)/9 + date + 4 + y + (y-1)/4 - (y-1)/100 + (y-1)/400 ) % 7 + 1;
	}
#undef y
	return D; //Normaly 1 to 7 !!!!
 }

 bool	__RTCIsLeapYear(uint32_t centYear)
 {
	 return (((centYear%4==0)&&(centYear%100!=0)) || (centYear%400==0));
 }

 bool __RTCIsSummerTime(uint32_t day, uint32_t date, uint32_t month, uint32_t hours)
 {


 }

