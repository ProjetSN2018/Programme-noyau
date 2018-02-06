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
#include <asf.h>
#include "..\Headers\appli.h"

#define SABLIER_NEW		100
#define SABLIER_RUN		102





void Sablier(uint32_t sc, uint32_t i);
void Prompt(uint32_t sc, uint32_t i);

char buf[256];


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
		
	cpu_irq_disable();
	sysclk_init();
	board_init();
	delay_init(sysclk_get_cpu_hz());
	//////////////////////////////////////////////////////////////////
	
	Taskman(TASKMAN_NEW);
	Shell(SHELL_NEW);


	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	gpio_set_pin_low(LED0_GPIO);

	PushTask(Sablier, SABLIER_NEW, 0, 0);
	PushTask(Prompt, 0, 0, 800);
	
	cpu_irq_enable();

	Putstr("\r\n\n\tATMEL ATSAM3U STARTED\r\n\n");

	for(;;)
	{
		PopTask();
	}
}

const uint32_t flashSequ[]={
	50,500,50,1200,0
};

void Sablier(uint32_t sc, uint32_t i)
{
	switch(sc)
	{
	case SABLIER_NEW:
		gpio_set_pin_low(LED0_GPIO);
	case SABLIER_RUN:
		i++; if(flashSequ[i]==0) i=0;
		if(i%2==0) gpio_set_pin_high(LED0_GPIO);
		else gpio_set_pin_low(LED0_GPIO);
		PushTask(Sablier,SABLIER_RUN,i,flashSequ[i]);
		break;
	default:
		Error(ERR_SABLIER_SWITCH_BAD_SC, sc);
		break;
	}
}


void Prompt(uint32_t sc, uint32_t i)
{
	sprintf(buf,"\rTimer:%06d",i++);
	Putstr(buf);
	PushTask(Prompt,0,i,2000);
}
