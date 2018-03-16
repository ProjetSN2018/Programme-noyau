#include "./Headers/appli.h"

/////LCD PRIVATE SERVICES CODES ///////////////////////////////////////////
enum{
	_LCD_PUT_DATA=1,
	_LCD_NYBBLE,
	_LCD_CURSOR_HOME,
	_LCD_COMMAND,
	_LCD_WRITE_DATA,
	_LCD_SET_RAM_ADDRESS
};

#define _LcdPutData(data)			Lcd(_LCD_PUT_DATA,(uint32_t)data)
#define _LcdNybble()				Lcd(_LCD_NYBBLE)
#define _LcdCursorHome()			Lcd(_LCD_CURSOR_HOME)	
#define _LcdCommand(cmd)			Lcd(_LCD_COMMAND,(uint32_t)cmd)
#define _LcdWriteData(data)			Lcd(_LCD_WRITE_DATA,(uint32_t)data)
#define _LcdSetCursor(nline,nCol)	Lcd(_LCD_SET_RAM_ADDRESS, (uint32_t)nline,(uint32_t)nCol)

/////////////////////////////////////////////////////////////////////////////////////

const char line2addr[]={ 0x00, 0x40, 0x14, 0x54 };

 uint32_t Lcd(uint32_t sc, ...)
 {
	switch (sc)
	{

	case LCD_PUTSTRING:
#define _pStr		pa1
#define _line		pa2
#define _col		pa3
		_LcdSetCursor(_line,_col);
		while(*(char*)_pStr)
		{
			_LcdWriteData(*(char*)_pStr);
			_pStr++;
		}
#undef _pStr
#undef _line
#undef _col
		break;
	
	case LCD_NEW:
		Putstr("LCD NEW \r\n");
		gpio_configure_pin(LCD_DATA4, LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_DATA5, LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_DATA6, LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_DATA7, LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_E,	  LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_RS,    LCD_PIN_FLAGS);
		
		gpio_set_pin_low(LCD_DATA4);
		gpio_set_pin_low(LCD_DATA5);
		gpio_set_pin_low(LCD_DATA6);
		gpio_set_pin_low(LCD_DATA7);
		gpio_set_pin_low(LCD_RS);
		gpio_set_pin_low(LCD_E);
		
		delay_ms(100);			// SEQUENCE DISPLAY HAVEN
		//_LcdPutData(0x20);		//pas la valeur 0x30 !!!!!
		//_LcdNybble();
		//delay_ms(10);
		//_LcdNybble();
		//delay_ms(10);
		//_LcdNybble();
		//delay_ms(10);
		//_LcdPutData(0x20);
		//_LcdNybble();
		_LcdCommand(LCD_FUNCTION_SET);   //Function Set
		_LcdCommand(LCD_CURSOR_SHIFT);	 //Cursor or display shift
		_LcdCommand(0x0E);			     //Display On/Off
		_LcdCommand(LCD_ENTRY_MODE_SET); //Entry Mode
		_LcdCommand(LCD_CLEAR_DISPLAY);  //Clear Display

		break;

	//////// Private Services Implementation //////////////////////////////////////
	case _LCD_PUT_DATA:
#define data ((char)pa1)
		if(mIsBitsSet(data,LCD_DATA7_MSK)) gpio_set_pin_high(LCD_DATA7); //P1
		else gpio_set_pin_low(LCD_DATA7);
		if(mIsBitsSet(data,LCD_DATA6_MSK)) gpio_set_pin_high(LCD_DATA6); //P2
		else gpio_set_pin_low(LCD_DATA6);
		if(mIsBitsSet(data,LCD_DATA5_MSK)) gpio_set_pin_high(LCD_DATA5); //P3
		else gpio_set_pin_low(LCD_DATA5);
		if(mIsBitsSet(data,LCD_DATA4_MSK)) gpio_set_pin_high(LCD_DATA4); //P4
		else gpio_set_pin_low(LCD_DATA4);
#undef data
		break;

	case _LCD_NYBBLE:
		gpio_set_pin_high(LCD_E);
		delay_ms(1);
		gpio_set_pin_low(LCD_E);
		break;
	case _LCD_COMMAND:
#define cmd		((char)pa1)
		gpio_set_pin_low(LCD_RS);	//RS=0 => COMMAND
		_LcdPutData(cmd);
		_LcdNybble();
		_LcdPutData(cmd<<4);
		_LcdNybble();
#undef cmd
		break;

	case _LCD_WRITE_DATA:
#define data ((char)pa1)
		gpio_set_pin_high(LCD_RS);	//RS=1 => DATA
		_LcdPutData(data);
		_LcdNybble();
		_LcdPutData(data<<4);
		_LcdNybble();
#undef data
		break;

	case _LCD_CURSOR_HOME:
		gpio_set_pin_high(LCD_DATA4);
		gpio_set_pin_high(LCD_DATA5);
		gpio_set_pin_high(LCD_DATA6);
		gpio_set_pin_high(LCD_DATA7);

		gpio_set_pin_low(LCD_E);
		gpio_set_pin_low(LCD_RS);

		break;
	case LCD_CLEAR:
		_LcdCommand(LCD_CLEAR_DISPLAY);
		delay_ms(1000);
		break;

	case _LCD_SET_RAM_ADDRESS:
#define _nLine	(pa1)
#define _nCol	(pa2)
		_LcdCommand((line2addr[_nLine&0x03]+_nCol)|0x80);
#undef _nLine
#undef _nCol
		break;

	default:
		Error(ERR_LCD_SWITCH_BAD_SC, sc);
	}
	return 0;
 }