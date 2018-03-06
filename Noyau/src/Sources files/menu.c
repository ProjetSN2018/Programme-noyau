/*
 * menu.c
 *
 * Created: 16/02/2018 14:29:06
 *  Author: eleve
 */ 
#include "./Headers/appli.h"
/////////////////////////////////INTERRUPT TEST//////////////
void ButtonSwitch_ISR_Handler(void);
void ButtonSelect_ISR_Handler(void);
const char* tabl[4][4];




struct { 
	int iIndexX;
	int iIndexY;
}menuParam;
 

int Menu(int sc, ...)
{

	switch(sc)
	{
	case MENU_NEW:
		tabl[0][0] = "Bonjour,\r";
		tabl[0][1] = "Comment\r";
		tabl[0][2] = "aller\r";
		tabl[0][3] = "vous?\r";
		tabl[1][0] = "Bionjourno,\r";
		tabl[1][1] = "Beve\r";
		tabl[1][2] = "la\r";
		tabl[1][3] = "aqua!!!!\r";
		tabl[2][0] = "Hello,\r";
		tabl[2][1] = "How\r";
		tabl[2][2] = "are\r";
		tabl[2][3] = "you??\r";
		tabl[3][0] = "Konichiwa,\r";
		tabl[3][1] = "Mitsubishi\r";
		tabl[3][2] = "sushi\r";
		tabl[3][3] = "Nagasaki\r";


		menuParam.iIndexX = 0;
		menuParam.iIndexY = 0;
		//////////////////////////////////////INTERRUPT PIN/////////////////////////////
		pmc_enable_periph_clk(ID_PIOA);
		pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE);
		
		
		
		pio_set_input(PIOA, PIO_PA24, PIO_PULLUP);
		pio_handler_set(PIOA, ID_PIOA, PIO_PA24, PIO_IT_FALL_EDGE, ButtonSelect_ISR_Handler);
		pio_enable_interrupt(PIOA, PIO_PA24);
		
		pio_set_input(PIOA, PIO_PA16, PIO_PULLUP);
		pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_FALL_EDGE, ButtonSwitch_ISR_Handler);
		pio_enable_interrupt(PIOA, PIO_PA16);
		
		
		NVIC_EnableIRQ(PIOA_IRQn);
	
		////////////////////////////////////////////////////////////////////////////////
		break;
	case MENU_SWITCH_BUTTON:
		pio_toggle_pin(PIO_PA23_IDX);
		menuParam.iIndexY = 0;
		menuParam.iIndexX++;
		
		if(menuParam.iIndexX >=4) menuParam.iIndexX = 0;
		break;
	case MENU_SELECT_BUTTON:
		menuParam.iIndexY++;

		break;
	case MENU_PROMPT:
		sprintf(buf, tabl[menuParam.iIndexX][menuParam.iIndexY]);
		Putstr(buf);
		break;
	default:
		Error(ERR_MENU_SWITCH_BAD_SC, sc);
	}
	return 0;
}

void ButtonSwitch_ISR_Handler()
{
	PushTask(Menu,MENU_SWITCH_BUTTON,0,0);
}

void ButtonSelect_ISR_Handler()
{
	PushTask(Menu, MENU_SELECT_BUTTON,0,0);
}