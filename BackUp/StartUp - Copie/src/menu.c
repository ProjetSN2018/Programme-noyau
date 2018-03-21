#include <string.h>

#include "./kernel/kernel.h"


/////////////////////////////////INTERRUPT TEST//////////////
void ButtonSwitch_ISR_Handler(void);	//pas sûr
void ButtonSelect_ISR_Handler(void);
void ButtonClear_ISR_Handler(void);

struct {
	int iIndexX;
	int iIndexMenu;
}menuParam;




int Menu(int sc, ...)
{
	switch(sc)
	{
		case MENU_NEW:
			Putstr("MENU_NEW\r");

			//Init ButtonSwitch
			pio_set_input(PIOA, PIN_BUTTON_SWITCH, PIO_PULLUP); //A0 (Bouton Gauche)
			pio_handler_set(PIOA, ID_PIOA, PIN_BUTTON_SWITCH, PIO_IT_FALL_EDGE, ButtonSwitch_ISR_Handler);
			pio_enable_interrupt(PIOA, PIN_BUTTON_SWITCH);
			//Init ButtonSelect
			pio_set_input(PIOA, PIN_BUTTON_SELECT, PIO_PULLUP); //A1 (Bouton Milieu)
			pio_handler_set(PIOA, ID_PIOA, PIN_BUTTON_SELECT, PIO_IT_FALL_EDGE, ButtonSelect_ISR_Handler);
			pio_enable_interrupt(PIOA, PIN_BUTTON_SELECT);
			//Init ButtonClear
			pio_set_input(PIOA, PIN_BUTTON_CLEAR, PIO_PULLUP); //A1 (Bouton Droite)
			pio_handler_set(PIOA, ID_PIOA, PIN_BUTTON_CLEAR, PIO_IT_FALL_EDGE, ButtonClear_ISR_Handler);
			pio_enable_interrupt(PIOA, PIN_BUTTON_CLEAR);
		
			NVIC_EnableIRQ(PIOA_IRQn);
		

			///////////////////////////////ON CREE LE MENU!!!//////////////////////////////////////////
			t_menu _menuOptionSas[] = {
				{ "Fermer portes 1", NULL, PushTask(Sas,SAS_FERMER_PORTE1,0 ,0)},
				{ "Fermer portes 2", NULL, PushTask(Sas,SAS_FERMER_PORTE2,0 ,0) },

				////////////////////LIST TERMINATOR//////////////////////////
				{ NULL, NULL, NULL}
			
			};

			t_menu _menu[] = {
				{ "Option portes",	&_menuOptionSas,	NULL},		//set
				{ "Option SAS",	NULL,	PushTask(Sas,SAS_FERMER_SAS,0 ,0)},

			
				//////////////////LIST TERMINATOR ////////////////////////////
				{NULL,	NULL,	NULL}
			};
			menuParam.iIndexX = 0;
			//t_menu listMenu[] = {_menu }, { _menuOptionSas} , NULL};
			break;
		case MENU_SWITCH_BUTTON:			//Quand press bouton Gauche
			gpio_toggle_pin(POWER_LED);
			if(_menu[menuParam.iIndexX++].pMenuStr == NULL) menuParam.iIndexX = 0;
			sprintf(buf, *_menu[menuParam.iIndexX].pMenuStr);
			Putstr(buf);
			LcdPutstr(buf, 3, 3);
			break;
		case MENU_SELECT_BUTTON:			//Quand press bouton Milieu
			gpio_toggle_pin(POWER_LED);
			if(_menu[menuParam.iIndexX].pSubMenu == NULL) _menu[menuParam.iIndexX].pMenuFunc;
			else
			{
				menuParam.iIndexX = 0;

			}
			break;
		case MENU_CLEAR_BUTTON:			//Quand press bouton Droite
			gpio_toggle_pin(POWER_LED);
			PushTask(Menu, MENU_PROMPT,0,0);
			break;
		case MENU_PROMPT:
			
			break;

		default:
			Error(ERROR_MENU_SWITCH_BAD_SC, sc);
	}
	return 0;
}

void ButtonSwitch_ISR_Handler()
{
	PushTask(Menu, MENU_SWITCH_BUTTON,0,0);
	

	// if(ShellGetState() == IDLE) ShellSetState(SWITCH);
}

void ButtonSelect_ISR_Handler()
{

	PushTask(Menu, MENU_SELECT_BUTTON,0,0);

	//f(ShellGetState() == SWITCH) ShellSetState(IDLE);
}

void ButtonClear_ISR_Handler()
{
	PushTask(Menu, MENU_CLEAR_BUTTON,0,0);
}