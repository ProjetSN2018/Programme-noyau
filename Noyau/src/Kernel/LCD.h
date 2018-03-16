//LCD I/O MAPPING ////////////////////////////////////////////////
#define LCD_DATA4			(PIO_PC25_IDX)
#define LCD_DATA5			(PIO_PC26_IDX)
#define LCD_DATA6			(PIO_PC28_IDX)
#define LCD_DATA7			(PIO_PB25_IDX)

#define LCD_E				(PIO_PD7_IDX)
#define LCD_RS				(PIO_PD8_IDX)

#define LCD_DATA4_MSK		0x10
#define LCD_DATA5_MSK		0x20
#define LCD_DATA6_MSK		0x40
#define LCD_DATA7_MSK		0x80
//////////////////////////////////////////////////////////////////
#define LCD_PIN_FLAGS		(PIO_TYPE_PIO_OUTPUT_1 | PIO_DEFAULT)
#define LCD_DATA4_FLAGS		LCD_PIN_FLAGS
#define LCD_DATA5_FLAGS		LCD_PIN_FLAGS
#define LCD_DATA6_FLAGS		LCD_PIN_FLAGS
#define LCD_DATA7_FLAGS		LCD_PIN_FLAGS
#define LCD_E_FLAGS			LCD_PIN_FLAGS
#define LCD_RS_FLAGS		LCD_PIN_FLAGS
//////////////////////////////////////////////////////////////////
// Commands //////////////////////////////////////////////////////
#define LCD_CLEAR_DISPLAY	0x01
#define LCD_RETURN_HOME		0x02
#define LCD_ENTRY_MODE_SET	0x04
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CURSOR_SHIFT	0x10
#define LCD_FUNCTION_SET	0x20
#define LCD_SET_CGRAM_ADDR  0x40
#define LCD_SET_DDRAM_ADDR  0x80
/////////////////////////////////////////////////////////////////
// Flags for display on/off control /////////////////////////////
#define LCD_DISPLAYON		0x04
#define LCD_DISPLAYOFF		0x00
#define LCD_CURSORON		0x02
#define LCD_CURSOROFF		0x00
#define LCD_BLINKON			0x01
#define LCD_BLINKOFF		0x00
//////////////////////////////////////////////////////////////////
uint32_t Lcd(uint32_t sc, ...);
 
#define LCD_NEW				100
#define LCD_PUTSTRING		102
#define LCD_CLEAR			103

#define LcdPutstr(str,line,row)		Lcd(LCD_PUTSTRING,(uint32_t)str,(uint32_t)line,(uint32_t)row)
#define LcdClear()					Lcd(LCD_CLEAR)