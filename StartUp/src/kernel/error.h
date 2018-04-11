/*
 * error.h
 *
 * Created: 10/03/2018 07:26:29
 *  Author: Thierry
 */
void Error(uint32_t er, ...);

#define ERROR_TASKMAN_SWITCH_BAD_SC						11
#define ERROR_SHELLCOM_SWITCH_BAD_SC					12
#define ERROR_SHELL_SWITCH_BAD_SC						13
#define ERROR_KRTC_SWITCH_BAD_SC						14
#define ERROR_LCD_SWITCH_BAD_SC							15
#define ERROR_APPLI_SWITCH_BAD_SC						16
#define ERROR_MENU_SWITCH_BAD_SC						17
#define ERROR_MODBUS_PROCESS_ACK_FRAME_SWITCH_BAD_SC	18
#define ERROR_SAS_SWITCH_BAD_SC							19
#define ERROR_SHELL_CMD_MENU_SWITCH_BAD_SC				20

#define ERROR_TASKMAN_TASKLIST_FULL						21
#define ERROR_TASKMAN_DELAYED_TASKLIST_FULL				22
#define ERROR_SHELLCOM_TX_BUFFER_FULL					23
#define ERROR_SHELLCOM_UART_INIT_FAILED					24
#define ERROR_SHELL_COM_UART_TX_FAILED					25
#define ERROR_STACK_PUSH_STACK_NOT_INITIALIZED			26
#define ERROR_STACK_POP_STACK_NOT_INITIALIZED			27
#define ERROR_STACK_PUSH_OVERFLOW						28
#define ERROR_STACK_POP_UNDERFLOW						29

#define ERROR_STACK_SWITCH_BAD_SC						31	
#define ERROR_COMRS485_SWITCH_BAD_SC					32
#define ERROR_MODBUS_SWITCH_BAD_SC						33
#define ERROR_COMRS485_TX_BUFFER_FULL					34
#define ERROR_COMRS485_RX_BUFFER_FULL					35

#define ERROR_SHELL_TIMER_ESC_BAD_SATE					41

#define ERROR_STACK_NOT_INIT							51
#define ERROR_STACK_PUSH_FULL							52
#define ERROR_STACK_UNDERFLOW							53