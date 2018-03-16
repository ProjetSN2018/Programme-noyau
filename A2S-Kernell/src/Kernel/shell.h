/*
 * shell.h
 *
 * Created: 06/02/2018 17:19:29
 *  Author: eleve
 */ 

#define  SHELL_EDIT_BUFFER_LEN			256
#define  SHELL_ESCSEQ_BUFFER_LEN		16

#define CONFIG_RTC_PRESCALER			RTC_PRESCALER_DIV1024_gc
#define	CONFIG_RTC_SOURCE				SYSCLK_RTCSRC_ULP

#define LED_HEARTBEAT					PIO_PB20_IDX
#define LED__HEARTBEAT_FLAGS			(PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)


uint32_t Shell(uint32_t sc, ...);

#define SHELL_NEW			100

#include "shellcom.h"
//#define Putch(c)			Shellcom(SHELLCOM_PUTC,(uint32_t)c)
//#define //Putstr(str)			Shellcom(SHELLCOM_//Putstr,(uint32_t)str)
//#define //Putstrlen(str,len)	Shellcom(SHELLCOM_//PutstrLEN,(uint32_t)str,(uint32_t)len)
