/*
 * menu.h
 *
 * Created: 16/02/2018 14:29:26
 *  Author: eleve
 */ 

 /////////////ID PINS///////////////////////////////////////////////
 #define PIN_LED				PIO_PA23
 #define PIN_LED_IDX			PIO_PA23_IDX
 #define PIN_BUTTON_SWITCH		PIO_PA24
 #define PIN_BUTTON_SELECT		PIO_PA16
 
 /////////////MENU SERVICE CODE//////////////////////////////////////
 #define MENU_NEW				100
 #define MENU_SWITCH_BUTTON		101
 #define MENU_SELECT_BUTTON		102
<<<<<<< Updated upstream
 #define MENU_SELECTED			103
 #define MENU_PROMPT			104

 /////////////LIMITES DES ATTRIBUT DES TABLEAUX/////////////////////
 #define INT_MENU_MAX			4
 #define INT_SUB_MENU_MAX		4
 #define INDEX_MENU				2


 
=======
 #define MENU_CLEAR_BUTTON		103
 #define MENU_SELECTED			104
 #define MENU_PROMPT			105
 #define MENU_LANGUAGE			106

 typedef struct tt_menuEntry {
	 char*				pStrTable;
	 const char*		pTable;
 }t_menuEntry;
>>>>>>> Stashed changes

 int Menu(int sc, ...);