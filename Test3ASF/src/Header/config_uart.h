/*
 * config_uart.h
 *
 * Created: 05/02/2018 15:18:25
 *  Author: eleve
 */ 


#ifndef CONFIG_UART_H_
#define CONFIG_UART_H_

#define SHELL_ESC_TIMEOUT					100
#define SHELL_EDIT_TIMEOUT					0

#define SHELLCOM_TXBUF_LEN					256
#define SHELLCOM_RXBUF_LEN					256
#define SHELLCOM_ESCSEQBUF_LEN				128


uint32_t Shellcom(void);

#define SHELLCOM_NEW						100
#define SHELLCOM_PUTC						102
#define SHELLCOM_PUTSTR						103
#define SHELLCOM_PUTSTRLEN					104

#define Putc(c)					Shellcom(SHELLCOM_PUTC,(uint32_t)c)
#define Putstr(str)				Shellcom(SHELLCOM_PUTSTR,(uint32_t)str)
#define Putstrlen(str,len)		Shellcom(SHELLCOM_PUTSTRLEN,(uint32_t)str,(uint32_t)len)


#endif /* CONFIG_UART_H_ */