/*
 * error.c
 *
 * Created: 29/01/2018 17:31:09
 *  Author: eleve
 */ 

 #include "../Header/appli.h"

 t_ptf32 pErrorFunc = ErrorLed;

 uint32_t ErrorLed(uint32_t err, ...)
 {
	 uint32_t i;
	 
	 for(;;)
	 {
	 
		gpio_set_pin_high(LED0_GPIO);
		delay_s(2);
		gpio_set_pin_low(LED0_GPIO);
		delay_ms(500);

		//Display tens of error code
		for(i=0; i<err/10; i++)
		{
			
		}
		delay_ms(400);

		//Display units of error code
		for(i=0; i<err%10; i++)
		{

			gpio_set_pin_high(LED0_GPIO);
			delay_s(2);
			gpio_set_pin_low(LED0_GPIO);
			delay_ms(500);
		}
		delay_s(2);
	 }
	 return 0;
 }

 const char* errorMsg[] = {
	"ERR_TASKMAN_SWITCH_BAD_SC",                  //11	//0
	"ERR_SABLIER_SWITCH_BAD_SC"                   //12	//1

 };

 uint32_t ErrorUART(uint32_t err, ...)
 {
	
	err-=11;
	if(err>3)
	{
		if(err<=8) err -= 3;
		else if(err<=13) err -= 4;
		else err -= 10;
	}
	//
	//
	if((err<=5) || (err==10))
	{
#define sc err
		//
		//
#undef sc
	}
	//

	delay_s(5);
	//
	return 0;
 }