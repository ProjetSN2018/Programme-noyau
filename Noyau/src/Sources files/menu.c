#include <string.h>
#include "./Headers/appli.h"
/////////////////////////////////INTERRUPT TEST//////////////
void ButtonSwitch_ISR_Handler(void);	//pas sûr
void ButtonSelect_ISR_Handler(void);
<<<<<<< Updated upstream
const char* tabl[INT_MENU_MAX][INT_SUB_MENU_MAX];
=======
void ButtonClear_ISR_Handler(void);
const char* tab1[4][5];
>>>>>>> Stashed changes

struct {
	int iIndexX;
	int iIndexY;
	int IndexMenu;
}menuParam;

const t_menuEntry _menuEntries[] ={
	{ "tab1",		tab1		},		//set

	//////////////////LIST TERMINATOR ////////////////////////////
	{	0,	NULL			}
};

void* test[3][3];

int Menu(int sc, ...)
{
	switch(sc)
	{
		case MENU_NEW:
		Putstr("MENU_NEW\r");
		/////////Menu Principal//////////////
		tab1[0][0] = "Langue\r\n";
		tab1[0][1] = "Carte\r\n";
		tab1[0][2] = "Classe\r\n";
		tab1[0][3] = NULL;
		/////////Sous-Menu Langue//////////////
		tab1[1][0] = "Français\r\n";
		tab1[1][1] = "Italiano\r\n";
		tab1[1][2] = "English\r\n";
		tab1[1][3] = "Nederlands\r\n";
		tab1[1][4] = NULL;
		/////////Sous-Menu Carte//////////////
		tab1[2][0] = "Arduino\r\n";
		tab1[2][1] = "Raspberry\r\n";
		tab1[2][2] = NULL;
		/////////Sous-Menu Classe//////////////
		tab1[3][0] = "921\r";
		tab1[3][1] = "821\r";
		tab1[3][2] = "721\r";
		tab1[3][3] = NULL;
		///////////Sous-Sous-Menu Langue-Francais//////////////
		//tab1[0][4] = "Bonjour,\r";
		//tab1[1][4] = "Comment\r";
		//tab1[2][4] = "Allez\r";
		//tab1[3][4] = "Vous?\r";
		///////////Sous-Sous-Menu Langue-Italiano//////////////
		//tab1[0][5] = "Bionjourno,\r";
		//tab1[1][5] = "Beve\r";
		//tab1[2][5] = "la\r";
		//tab1[3][5] = "aqua\r";
		///////////Sous-Sous-Menu Langue-English//////////////
		//tab1[0][6] = "Hello,\r";
		//tab1[1][6] = "How\r";
		//tab1[2][6] = "are\r";
		//tab1[3][6] = "you?\r";
		///////////Sous-Sous-Menu Langue-Nederlands//////////////
		//tab1[0][7] = "Hallo,\r";
		//tab1[1][7] = "Hoe\r";
		//tab1[2][7] = "Gaat\r";
		//tab1[3][7] = "Het?\r";
		//
		menuParam.iIndexX = 0;
		menuParam.iIndexY = 0;
		//////////////////////////////////////INTERRUPT PIN/////////////////////////////
<<<<<<< Updated upstream
		pmc_enable_periph_clk(ID_PIOA);
		pio_set_output(PIOA, PIN_LED, LOW, DISABLE, ENABLE);
		
		
		pio_set_input(PIOA, PIN_BUTTON_SELECT, PIO_PULLUP);
		pio_handler_set(PIOA, ID_PIOA, PIN_BUTTON_SELECT, PIO_IT_FALL_EDGE, ButtonSelect_ISR_Handler);
		pio_enable_interrupt(PIOA, PIN_BUTTON_SELECT);
		
		pio_set_input(PIOA, PIN_BUTTON_SWITCH, PIO_PULLUP);
		pio_handler_set(PIOA, ID_PIOA, PIN_BUTTON_SWITCH, PIO_IT_FALL_EDGE, ButtonSwitch_ISR_Handler);
		pio_enable_interrupt(PIOA, PIN_BUTTON_SWITCH);
		
=======
		//Init ButtonSwitch
		pio_set_input(PIOA, PIO_PA16, PIO_PULLUP); //A0 (Bouton Gauche)
		pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_FALL_EDGE, ButtonSwitch_ISR_Handler);
		pio_enable_interrupt(PIOA, PIO_PA16);
		//Init ButtonSelect
		pio_set_input(PIOA, PIO_PA24, PIO_PULLUP); //A1 (Bouton Milieu)
		pio_handler_set(PIOA, ID_PIOA, PIO_PA24, PIO_IT_FALL_EDGE, ButtonSelect_ISR_Handler);
		pio_enable_interrupt(PIOA, PIO_PA24);
		//Init ButtonClear
		pio_set_input(PIOA, PIO_PA23, PIO_PULLUP); //A1 (Bouton Droite)
		pio_handler_set(PIOA, ID_PIOA, PIO_PA23, PIO_IT_FALL_EDGE, ButtonClear_ISR_Handler);
		pio_enable_interrupt(PIOA, PIO_PA23);
>>>>>>> Stashed changes
		
		NVIC_EnableIRQ(PIOA_IRQn);
		////////////////////////////////////////////////////////////////////////////////
		ShellSetState(SWITCH);
		PushTask(Menu, MENU_PROMPT,0,0);
		
		break;
<<<<<<< Updated upstream
	case MENU_SWITCH_BUTTON:
		pio_toggle_pin(PIN_LED_IDX);
		menuParam.iIndexX++;
		
		if(menuParam.iIndexX >=INT_MENU_MAX) menuParam.iIndexX = 0;
		if(menuParam.iIndexY >=INDEX_MENU) menuParam.iIndexY = 0;
=======
		case MENU_SWITCH_BUTTON:			//Quand press bouton Gauche
		pio_toggle_pin(PIO_PA23_IDX);
		if(tab1[menuParam.iIndexX][menuParam.iIndexY] != NULL) menuParam.iIndexY++;
		sprintf(buf, tab1[menuParam.iIndexX][menuParam.iIndexY]);
		
		Putstr(buf);
		PushTask(Menu, MENU_PROMPT,0,0);
>>>>>>> Stashed changes
		break;
		case MENU_SELECT_BUTTON:			//Quand press bouton Milieu
		menuParam.iIndexX = menuParam.iIndexY + 1;
		menuParam.iIndexY = 0;
		PushTask(Menu, MENU_PROMPT,0,0);
		break;
		case MENU_CLEAR_BUTTON:				//Quand press bouton Droite
		Lcd(LCD_CLEAR);
		PushTask(Menu, MENU_PROMPT,0,0);
		break;
		case MENU_PROMPT:					//Disp a faire
		sprintf(buf, tab1[menuParam.iIndexX][menuParam.iIndexY]);
		
		Putstr(buf);
		Lcd(LCD_CLEAR);
		LcdPutstr(buf, 3,0);
		break;

		default:
		Error(ERR_MENU_SWITCH_BAD_SC, sc);
	}
	return 0;
}

void ButtonSwitch_ISR_Handler()
{
	PushTask(Menu, MENU_SWITCH_BUTTON,0,0);
	if(ShellGetState() == IDLE) ShellSetState(SWITCH);
}

void ButtonSelect_ISR_Handler()
{
	PushTask(Menu, MENU_SELECT_BUTTON,0,0);
	if(ShellGetState() == IDLE) ShellSetState(SWITCH);
}

void ButtonClear_ISR_Handler()
{
	PushTask(Menu, MENU_CLEAR_BUTTON,0,0);
}