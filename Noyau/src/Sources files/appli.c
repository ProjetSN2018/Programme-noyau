/*
 * appli.c
 *
 * Created: 12/02/2018 16:40:22
 *  Author: eleve
 */ 

 #include "./Headers/appli.h"
 const uint32_t flashSequApp[]={
	 100,500,100,500,100,2200,0
 };


uint32_t Appli(uint32_t sc,...)
{
	switch(sc)
	{
	case APPLI_NEW:
		gpio_configure_pin(PIO_PC1_IDX, (PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT));
		Lcd(LCD_NEW);
		PushTask(Appli, APPLI_RUN, 0, 800);
		break;
	case APPLI_RUN:
#define k	pa1
		k++; if(flashSequApp[k]==0) k=0;
		if(k%2==0) gpio_set_pin_high(PIO_PC1_IDX);
		else gpio_set_pin_low(PIO_PC1_IDX);
		PushTask(Appli,APPLI_RUN,k,flashSequApp[k]);

#undef k
		break;

	default:
		Error(ERR_APPLI_SWITHC_BAD_SC, sc);
		break;
	}
}