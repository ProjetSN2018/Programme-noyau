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


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	cpu_irq_disable();
	sysclk_init();
	board_init();

	delay_init(sysclk_get_cpu_hz());

	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	/* Insert application code here, after the board has been initialized. */

	t_param k;

	Sablier(SABLIER_NEW, k);

	
}


void Sablier(uint32_t sc, t_param i)
{
		const uint32_t beat[] = {
		60,400,60,1000,0
		};

		switch(sc)
		{
		case SABLIER_NEW:
			gpio_set_pin_high(LED0_GPIO);
			i.k=1;
			
		case SABLIER_RUN:
			gpio_toggle_pin(LED0_GPIO);
			if(!beat[++i.k]) i.k=0;

			break;
		default:
			Error(ERR_SABLIER_SWITCH_BAD_SC, sc);
			break;

		}


}
