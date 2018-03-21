#include <string.h>

#include "./kernel/kernel.h"


///////////////////////////////ON CREE LE MENU!!!//////////////////////////////////////////
const t_menu _menuOptionSas[] = {
	{ "Fermer portes 1", NULL, NULL /*Sas(SAS_FERMER_PORTE1)*/},
	{ "Fermer portes 2", NULL,NULL /*Sas(SAS_FERMER_PORTE2) */},

	////////////////////LIST TERMINATOR//////////////////////////
	{ NULL, NULL, NULL}
	
};

const t_menu _menu[] = {
	{ "Option portes",	&_menuOptionSas,	NULL},		//set
	{ "Option SAS",	NULL,	NULL/*Sas(SAS_FERMER_SAS)*/},

	
	//////////////////LIST TERMINATOR ////////////////////////////
	{NULL,	NULL,	NULL}
};

t_menu _listMenu[NB_MENU][NB_SUB_MENU];

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
			
			
			_listMenu[0][0].pMenuStr = "Option portes";
			_listMenu[0][0].pSubMenu = 1;
			_listMenu[0][0].pMenuFunc = NULL;

			_listMenu[0][1].pMenuStr = "Option sas";
			_listMenu[0][1].pSubMenu = 0;
			_listMenu[0][1].pMenuFunc = PushTask(Sas,SAS_FERMER_PORTE1,0,0);

			_listMenu[0][2].pMenuStr = NULL;
			_listMenu[0][2].pSubMenu = NULL;
			_listMenu[0][2].pMenuFunc = NULL;

			_listMenu[1][0].pMenuStr = "Fermer portes 1";
			_listMenu[1][0].pSubMenu = NULL;
			_listMenu[1][0].pMenuFunc = PushTask(Sas,SAS_FERMER_PORTE1,0,0);

			_listMenu[1][1].pMenuStr = "Fermer portes 2";
			_listMenu[1][1].pSubMenu = NULL;
			_listMenu[1][1].pMenuFunc = Sas(SAS_FERMER_PORTE2);

			_listMenu[1][2].pMenuStr = NULL;
			_listMenu[1][2].pSubMenu = NULL;
			_listMenu[1][2].pMenuFunc = NULL;

			sprintf(buf, "MENU NEW FINISHED \r\n");
			Putstr(buf);
			menuParam.iIndexX = 0;
			menuParam.iIndexMenu = 0;
			//t_menu listMenu[] = {_menu }, { _menuOptionSas} , NULL};
			break;
		case MENU_SWITCH_BUTTON:			//Quand press bouton Gauche
			menuParam.iIndexX++;
			if(_listMenu[menuParam.iIndexMenu][menuParam.iIndexX].pMenuStr == NULL) menuParam.iIndexX = 0;
			Menu(MENU_PROMPT);
			break;
		case MENU_SELECT_BUTTON:			//Quand press bouton Milieu
			if(_listMenu[menuParam.iIndexMenu][menuParam.iIndexX].pSubMenu != 0)
			{
				menuParam.iIndexMenu++;
				menuParam.iIndexX = 0;
				Menu(MENU_PROMPT);
			} 
			else 
			{
				_listMenu[menuParam.iIndexMenu][menuParam.iIndexX].pMenuFunc;
				menuParam.iIndexX = 0;
				menuParam.iIndexMenu = 0;
				Menu(MENU_PROMPT);
			}
			break;
		case MENU_CLEAR_BUTTON:			//Quand press bouton Droite
			if(menuParam.iIndexMenu != 0)
			{
				menuParam.iIndexMenu--;
				menuParam.iIndexX = 0;
				Menu(MENU_PROMPT);
			}
			
			break;
		case MENU_PROMPT:
			LcdPutstr("                   ", 2, 0);
			sprintf(buf, "%s", _listMenu[menuParam.iIndexMenu][menuParam.iIndexX].pMenuStr);
			Putstr(buf);
			LcdPutstr(buf, 2, LcdFindHalf(strlen(buf)));
			sprintf(buf, "%d\r\n", _listMenu[menuParam.iIndexMenu][menuParam.iIndexX].pSubMenu);
			Putstr(buf);
			break;
		case MENU_INIT:
		
			menuParam.iIndexX = 0;
			sprintf(buf, "\r\n");
			Putstr(buf);
			sprintf(buf,"Index: %d\r\n", menuParam.iIndexX);
			Putstr(buf);
			sprintf(buf, "%s \r\n", _listMenu[menuParam.iIndexX]);
			Putstr(buf);
			gpio_toggle_pin(POWER_LED);
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

