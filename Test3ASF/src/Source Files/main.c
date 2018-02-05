/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "../Header/appli.h"




#define SABLIER_NEW		100
#define SABLIER_RUN		102

	typedef union {
		uint32_t u32;
		struct{
			unsigned led:1;
			unsigned k:3;
			unsigned dummy:28;
		};
	}t_param;

void Sablier(uint32_t sc, t_param i);
void s(void);




#define USART_SERIAL					USART0
#define USART_SERIAL_ID					ID_USART0
#define USART_SERIAL_BAUDRATE			115200
#define USART_SERIAL_CHAR_LENGTH		US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY				US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT			US_MR_NBSTOP_1_BIT

#define USART_SERIAL_TXD_PIN			PIN_USART0_TXD
#define USART_SERIAL_TXD_IDX			PIN_USART0_TXD_IDX
#define USART_SERIAL_TXD_FLAGS			PIN_USART0_TXD_FLAGS

#define USART_SERIAL_RXD_PIN			PIN_USART0_RXD
#define USART_SERIAL_RXD_IDX			PIN_USART0_RXD_IDX
#define USART_SERIAL_RXD_FLAGS			PIN_USART0_RXD_FLAGS

const sam_usart_opt_t usart_console_settings = {
	USART_SERIAL_BAUDRATE,
	USART_SERIAL_CHAR_LENGTH,
	USART_SERIAL_PARITY,
	USART_SERIAL_STOP_BIT,
	US_MR_CHMODE_NORMAL
};



int main (void)
{
	uint32_t cpt=0;
	/* Insert system clock initialization code here (sysclk_init()). */
	cpu_irq_disable();
	sysclk_init();
	board_init();

	delay_init(sysclk_get_cpu_hz());

	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	/* Insert application code here, after the board has been initialized. */
	//Taskman(TASKMAN_NEW);
	gpio_set_pin_high(LED0_GPIO);
	//pushTask(Sablier, SABLIER_NEW,0 ,0);
	

		sysclk_enable_peripheral_clock(USART_SERIAL_ID);
		usart_init_rs232(USART_SERIAL, &usart_console_settings,	sysclk_get_cpu_hz());
		gpio_configure_pin(USART_SERIAL_TXD_IDX,USART_SERIAL_TXD_FLAGS);
		gpio_configure_pin(USART_SERIAL_RXD_IDX,USART_SERIAL_RXD_FLAGS);
		//usart_enable_interrupt(USART_SERIAL, US_IER_RXRDY);
		//NVIC_EnableIRQ(USART_SERIAL_ID);

		 usart_putchar(USART_SERIAL,'x');
	
	for(;;cpt++)
	{
		//Taskman(TASKMAN_POP_TASK);
		if(cpt%100000==0)
		{
			 usart_putchar(USART_SERIAL,'a');
			 gpio_toggle_pin(LED0_GPIO);
		}
	}
return 0;
	
}


void Sablier(uint32_t sc, t_param i)
{
		const uint32_t beat[] = {
		60,400,60,1000,0
		};

		switch(sc)
		{
		case SABLIER_NEW:
			//gpio_set_pin_high(LED0_GPIO);
			//gpio_set_pin_low(LED0_GPIO);
			i.k=1;
			
		case SABLIER_RUN:
			i.led ^= 1;
			//if(i.led == 1) gpio_set_pin_high(LED0_GPIO);
			//else gpio_set_pin_low(LED0_GPIO);
			if(!beat[++i.k]) i.k=0;
			pushTask(Sablier, SABLIER_RUN, i.u32, beat[i.k]);
			break;	
		default:
			Error(ERR_SABLIER_SWITCH_BAD_SC, sc);
			break;

		}

	//switch(sc)
	//{
	//case SABLIER_NEW:
		//gpio_set_pin_low(LED0_GPIO);
		//
	//case SABLIER_RUN:
		//if(i%50000==0)		gpio_set_pin_high(LED0_GPIO);
		//if(i%50000==2000)	gpio_set_pin_low(LED0_GPIO);
		//pushTask(Sablier, SABLIER_RUN, ++i, 0);
		//break;
		//
	//default:
		//Error(ERR_SABLIER_SWITCH_BAD_SC, sc);
		//break;
	//}

}
void s(void)
{
	gpio_toggle_pin(LED0_GPIO);
	delay_ms(2000);
	gpio_toggle_pin(LED0_GPIO);
	delay_ms(2000);

}
