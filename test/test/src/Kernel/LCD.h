////LCD I/O MAPPING ////////////////////////////////////////////////
//#define LCD_DATA4			(PIO_PA0_IDX)
//#define LCD_DATA5			(PIO_PA1_IDX)
//#define LCD_DATA6			(PIO_PA2_IDX)
//#define LCD_DATA7			(PIO_PA3_IDX)
//
//#define LCD_E				(PIO_PA4_IDX)
//#define LCD_RW				(PIO_PA5_IDX)
//#define LCD_RS				(PIO_PA6_IDX)
//#define LCD_BACKLIGHT		(PIO_PA7_IDX)
//
//#define LCD_DATA4_MSK		0x10
//#define LCD_DATA5_MSK		0x20
//#define LCD_DATA6_MSK		0x40
//#define LCD_DATA7_MSK		0x80
////////////////////////////////////////////////////////////////////
//#define LCD_PIN_FLAGS		(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
//#define LCD_DATA4_FLAGS		LCD_PIN_FLAGS
//#define LCD_DATA5_FLAGS		LCD_PIN_FLAGS
//#define LCD_DATA6_FLAGS		LCD_PIN_FLAGS
//#define LCD_DATA7_FLAGS		LCD_PIN_FLAGS
//#define LCD_E_FLAGS			LCD_PIN_FLAGS
//#define LCD_RS_FLAGS		LCD_PIN_FLAGS
////////////////////////////////////////////////////////////////////
//// Commands //////////////////////////////////////////////////////
//#define LCD_CLEAR_DISPLAY	0x01
//#define LCD_RETURN_HOME		0x02
//#define LCD_ENTRY_MODE_SET	0x04
//#define LCD_DISPLAY_CONTROL 0x08
//#define LCD_CURSOR_SHIFT	0x10
//#define LCD_FUNCTION_SET	0x20
//#define LCD_SET_CGRAM_ADDR  0x40
//#define LCD_SET_DDRAM_ADDR  0x80
///////////////////////////////////////////////////////////////////
//// Flags for display on/off control /////////////////////////////
//#define LCD_DISPLAYON		0x04
//#define LCD_DISPLAYOFF		0x00
//#define LCD_CURSORON		0x02
//#define LCD_CURSOROFF		0x00
//#define LCD_BLINKON			0x01
//#define LCD_BLINKOFF		0x00
////////////////////////////////////////////////////////////////////


uint32_t Lcd(uint32_t sc, ...);

#define LCD_NEW				100
#define LCD_BACKLIGHT_PWR	102
#define LCD_PUTSTRING		103
#define LCD_CLEAR			104


#define LcdPutstr(str,line,col)			Lcd(LCD_PUTSTRING,(uint32_t)str,(uint32_t)line,(uint32_t)col)
#define LcdClear()						Lcd(LCD_CLEAR)
#define LcdBackLight(onOff)				Lcd(LCD_BACKLIGHT_PWR,(uint32_t)onOff)