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

typedef enum {
	IDLE = 0,
	EDITION,
	EXECUTION,
	ESCAPE,
	ESCAPE_SEQ,
	ED_ESCAPE,
	ED_ESCAPE_SEQ,
	SWITCH
} t_state;


uint32_t Shell(uint32_t sc, ...);
void ShellSetState(t_state setState);
t_state ShellGetState(void);

#define SHELL_NEW			100

#include "shellcom.h"
#define Putch(c)			Shellcom(SHELLCOM_PUTC,(uint32_t)c)
#define Putstr(str)			Shellcom(SHELLCOM_PUTSTR,(uint32_t)str)
#define Putstrlen(str,len)	Shellcom(SHELLCOM_PUTSTRLEN,(uint32_t)str,(uint32_t)len)

