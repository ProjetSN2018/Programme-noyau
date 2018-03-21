/*
 * menu.h
 *
 * Created: 16/02/2018 14:29:26
 *  Author: eleve
 */ 
 #define MENU_NEW				100
 #define MENU_SWITCH_BUTTON		101
 #define MENU_SELECT_BUTTON		102
 #define MENU_CLEAR_BUTTON		103
 #define MENU_SELECTED			104
 #define MENU_PROMPT			105
 #define MENU_LANGUAGE			106


 /////////PIN BUTTON/////////////////////////
 #define PIN_BUTTON_SWITCH		PIO_PA8
 #define PIN_BUTTON_SELECT		PIO_PA9
 #define PIN_BUTTON_CLEAR		PIO_PA10
 typedef struct tt_menu {
	 char*				pMenuStr;
	 struct tt_menu*	pSubMenu;
	 t_ptf				pMenuFunc;
 }t_menu;

 int Menu(int sc, ...);