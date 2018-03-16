//Application's error codes
#define ERR_TASKMAN_SWITCH_BAD_SC                   11
#define ERR_SABLIER_SWITCH_BAD_SC                   12
#define ERR_SHELLCOM_SWITCH_BAD_SC					13
#define ERR_SHELL_SWITCH_BAD_SC						14
#define ERR_APPLI_SWITCH_BAD_SC						15
#define ERR_MENU_SWITCH_BAD_SC						16
#define ERR_MENU_SELECT_BUTTON_SWITCH_BAD_SC		17
#define ERR_SAS_SWITCH_BAD_SC						18
#define ERR_SHELL_CMD_MENU_SWITCH_BAD_SC			19
#define ERR_LCD_SWITCH_BAD_SC						20


#define ERR_TASKMAN_TASKLIST_FULL			        21
#define ERR_TASKMAN_DELAYED_TASKLIST_FULL			22
#define ERR_SHELLCOM_TX_BUFFER_FULL					23

#define ERR_SHELLCOM_UART_INIT_FAILED				31

//Concerned function prototype
uint32_t ErrorLed(uint32_t err, ...);
uint32_t ErrorUART(uint32_t err, ...);


extern t_ptf32 pErrorFunc;

#define Error(errc, sc)		pErrorFunc(errc, sc)
