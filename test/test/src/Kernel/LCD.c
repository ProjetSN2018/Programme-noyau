
#include "kernel.h"

#define LCD_PIN_FLAGS				(PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
#define LCD_PIN_ACTIVE_LEVEL		1

#define LCD_DB4						(PIO_PA0_IDX)
#define LCD_DB4_NAME				"LCD_DB4"

#define LCD_DB5						(PIO_PA1_IDX)
#define LCD_DB5_NAME				"LCD_DB5"

#define LCD_DB6						(PIO_PA2_IDX)
#define LCD_DB6_NAME				"LCD_DB5"

#define LCD_DB7						(PIO_PA3_IDX)
#define LCD_DB7_NAME				"LCD_DB7"

#define LCD_E						(PIO_PA4_IDX)
#define LCD_E_NAME					"LCD_E"

#define LCD_RWB						(PIO_PA5_IDX)
#define LCD_RWB_NAME				"LCD_RWB"

#define LCD_RS						(PIO_PA6_IDX)
#define LCD_RS_NAME					"LCD_RS"

#define LCD_BACKLIGHT				(PIO_PA7_IDX)
#define LCD_BACKLIGHT_NAME			"LCD_BACKLIGHT"

///LCD PRIVATE SERVICE CODES////////////////////////////////////////
enum{
	_LCD_WRITE_HALF = 1,
	_LCD_WRITE_INST,
	_LCD_WRITE_DATA,
	_LCD_E_STROBE,
	_LCD_SET_RAM_ADDRESS
};

#define _LcdWriteHalf(inst)			Lcd(_LCD_WRITE_HALF,(uint32_t)inst)
#define _LcdWriteInst(inst)			Lcd(_LCD_WRITE_INST,(uint32_t)inst)
#define _LcdWriteData(data)			Lcd(_LCD_WRITE_DATA,(uint32_t)data)
#define _LcdEstrobe()				Lcd(_LCD_E_STROBE)
#define _LcdSetCursor(nline,nCol)	Lcd(_LCD_SET_RAM_ADDRESS, (uint32_t)nline,(uint32_t)nCol)


const char line2addr[]={ 0x00, 0x40, 0x14, 0x54 };

uint32_t Lcd(uint32_t sc, ...)
{
	switch(sc)
	{
	case LCD_NEW:
		gpio_configure_pin(LCD_DB4,LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_DB5,LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_DB6,LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_DB7,LCD_PIN_FLAGS);

		gpio_configure_pin(LCD_E,LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_RWB,LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_RS,LCD_PIN_FLAGS);
		gpio_configure_pin(LCD_BACKLIGHT,LCD_PIN_FLAGS);
	
		gpio_set_pin_low(LCD_DB4);
		gpio_set_pin_low(LCD_DB5);
		gpio_set_pin_low(LCD_DB6);
		gpio_set_pin_low(LCD_DB7);

		gpio_set_pin_low(LCD_E);
		gpio_set_pin_low(LCD_RS);
		gpio_set_pin_low(LCD_RWB);

		delay_ms(100);
		_LcdWriteHalf(0x30);
		delay_ms(10);
		_LcdWriteHalf(0x30);
		delay_ms(5);
		_LcdWriteHalf(0x30);
		delay_ms(5);
		_LcdWriteHalf(0x20);
		delay_ms(5);
		_LcdWriteInst(0x28);	//SET FUNCTION : 4 bits interface/2 line display/5x7 dots
		_LcdWriteInst(0x08);	//DISPLAY OFF
		_LcdWriteInst(0x01);	//DISPLAY CLEAR
		_LcdWriteInst(0x06);	//ENTRY MODE SET : Cursor Increase/Display is not shift
		_LcdWriteInst(0x0C);	//DISPLAY ON/Cursor on
		LcdBackLight(true);
		break;
		
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

	case LCD_BACKLIGHT_PWR:
#define _onOff	(unsigned)pa1
		if(_onOff)
#if LCD_PIN_ACTIVE_LEVEL==1
			gpio_set_pin_high(LCD_BACKLIGHT);
#else
			gpio_set_pin_low(LCD_BACKLIGHT);
#endif
		else
#if LCD_PIN_ACTIVE_LEVEL==1
			gpio_set_pin_low(LCD_BACKLIGHT);
#else
			gpio_set_pin_high(LCD_BACKLIGHT);
#endif

#undef _onOff
		break;

	///LCD PRIVATE SERVICE IMPLEMENTATION //////////////////////////////////////////
#define _inst		pa1
	case _LCD_WRITE_HALF:
		gpio_set_pin_low(LCD_RS);
		(_inst&0x80)?gpio_set_pin_high(LCD_DB7):gpio_set_pin_low(LCD_DB7);
		(_inst&0x40)?gpio_set_pin_high(LCD_DB6):gpio_set_pin_low(LCD_DB6);
		(_inst&0x20)?gpio_set_pin_high(LCD_DB5):gpio_set_pin_low(LCD_DB5);
		(_inst&0x10)?gpio_set_pin_high(LCD_DB4):gpio_set_pin_low(LCD_DB4);
		Lcd(_LCD_E_STROBE);
		break;
	case _LCD_WRITE_INST:
		gpio_set_pin_low(LCD_RS);
		_LcdWriteHalf(_inst);
		delay_ms(1);
		_LcdWriteHalf(_inst<<4);
		break;
#undef _inst

#define _data pa1
	case _LCD_WRITE_DATA:
		gpio_set_pin_high(LCD_RS);
		(_data&0x80)?gpio_set_pin_high(LCD_DB7):gpio_set_pin_low(LCD_DB7);
		(_data&0x40)?gpio_set_pin_high(LCD_DB6):gpio_set_pin_low(LCD_DB6);
		(_data&0x20)?gpio_set_pin_high(LCD_DB5):gpio_set_pin_low(LCD_DB5);
		(_data&0x10)?gpio_set_pin_high(LCD_DB4):gpio_set_pin_low(LCD_DB4);
		Lcd(_LCD_E_STROBE);
		delay_ms(1);
		(_data&0x08)?gpio_set_pin_high(LCD_DB7):gpio_set_pin_low(LCD_DB7);
		(_data&0x04)?gpio_set_pin_high(LCD_DB6):gpio_set_pin_low(LCD_DB6);
		(_data&0x02)?gpio_set_pin_high(LCD_DB5):gpio_set_pin_low(LCD_DB5);
		(_data&0x01)?gpio_set_pin_high(LCD_DB4):gpio_set_pin_low(LCD_DB4);
		Lcd(_LCD_E_STROBE);
		delay_ms(1);
		break;
#undef _data

	case _LCD_E_STROBE:
		gpio_set_pin_high(LCD_E);
		delay_ms(1);
		gpio_set_pin_low(LCD_E);
		delay_ms(1);
		break;

		case _LCD_SET_RAM_ADDRESS:
#define _nLine	pa1
#define _nCol	pa2
		_LcdWriteInst((line2addr[_nLine&0x03]+_nCol)|0x80);
#undef _nLine
#undef _nCol
		break;

	/////// INVALID SC CODE TRAP ERROR /////////////////////////////////////////////////////////////////
	default:
		Error(ERR_LCD_SWITCH_BAD_SC,sc);
	}
	return 0;
}



























/////LCD PRIVATE SERVICES CODES ///////////////////////////////////////////
//enum{
	//_LCD_PUT_DATA=1,
	//_LCD_NYBBLE,
	//_LCD_CURSOR_HOME,
	//_LCD_COMMAND,
	//_LCD_WRITE_DATA,
	//_LCD_SET_RAM_ADDRESS
//};
//
//#define _LcdPutData(data)			Lcd(_LCD_PUT_DATA,(uint32_t)data)
//#define _LcdNybble()				Lcd(_LCD_NYBBLE)
//#define _LcdCursorHome()			Lcd(_LCD_CURSOR_HOME)
//#define _LcdCommand(cmd)			Lcd(_LCD_COMMAND,(uint32_t)cmd)
//#define _LcdWriteData(data)			Lcd(_LCD_WRITE_DATA,(uint32_t)data)
//#define _LcdSetCursor(nline,nCol)	Lcd(_LCD_SET_RAM_ADDRESS, (uint32_t)nline,(uint32_t)nCol)

/////////////////////////////////////////////////////////////////////////////////////

//const char line2addr[]={ 0x00, 0x40, 0x14, 0x54 };












//
//uint32_t Lcd(uint32_t sc, ...)
//{
	//switch (sc)
	//{
//
		//case LCD_PUTSTR:
		//#define _pStr		pa1
		//#define _line		pa2
		//#define _col		pa3
		//_LcdSetCursor(_line,_col);
		//while(*(char*)_pStr)
		//{
			//_LcdWriteData(*(char*)_pStr);
			//_pStr++;
		//}
		//#undef _pStr
		//#undef _line
		//#undef _col
		//break;
		//
		//case LCD_NEW:
		//Putstr("LCD NEW \r\n");
		//gpio_configure_pin(LCD_DATA4,		LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_DATA5,		LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_DATA6,		LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_DATA7,		LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_E,			LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_RW,			LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_RS,			LCD_PIN_FLAGS);
		//gpio_configure_pin(LCD_BACKLIGHT,   LCD_PIN_FLAGS);
//
		//gpio_set_pin_high(LCD_BACKLIGHT);
		//gpio_set_pin_low(LCD_DATA4);
		//gpio_set_pin_low(LCD_DATA5);
		//gpio_set_pin_low(LCD_DATA6);
		//gpio_set_pin_low(LCD_DATA7);
		//gpio_set_pin_low(LCD_E);
		//gpio_set_pin_low(LCD_RS);
		//gpio_set_pin_low(LCD_RW);
		//
		//
		//delay_ms(100);			// SEQUENCE DISPLAY HAVEN
//
		//_LcdCommand(LCD_FUNCTION_SET);   //Function Set
		//_LcdCommand(LCD_CURSOR_SHIFT);	 //Cursor or display shift
		//_LcdCommand(0x0E);			     //Display On/Off
		//_LcdCommand(LCD_ENTRY_MODE_SET); //Entry Mode
		//_LcdCommand(LCD_CLEAR_DISPLAY);  //Clear Display
//
		//break;
//
		////////// Private Services Implementation //////////////////////////////////////
		//case _LCD_PUT_DATA:
		//#define data ((char)pa1)
		//if(mIsBitsSet(data,LCD_DATA7_MSK)) gpio_set_pin_high(LCD_DATA7); //P1
		//else gpio_set_pin_low(LCD_DATA7);
		//if(mIsBitsSet(data,LCD_DATA6_MSK)) gpio_set_pin_high(LCD_DATA6); //P2
		//else gpio_set_pin_low(LCD_DATA6);
		//if(mIsBitsSet(data,LCD_DATA5_MSK)) gpio_set_pin_high(LCD_DATA5); //P3
		//else gpio_set_pin_low(LCD_DATA5);
		//if(mIsBitsSet(data,LCD_DATA4_MSK)) gpio_set_pin_high(LCD_DATA4); //P4
		//else gpio_set_pin_low(LCD_DATA4);
		//#undef data
		//break;
//
		//case _LCD_NYBBLE:
		//gpio_set_pin_high(LCD_E);
		//delay_ms(1);
		//gpio_set_pin_low(LCD_E);
		//break;
		//case _LCD_COMMAND:
		//#define cmd		((char)pa1)
		//gpio_set_pin_low(LCD_RS);	//RS=0 => COMMAND
		//_LcdPutData(cmd);
		//_LcdNybble();
		//_LcdPutData(cmd<<4);
		//_LcdNybble();
		//#undef cmd
		//break;
//
		//case _LCD_WRITE_DATA:
		//#define data ((char)pa1)
		//gpio_set_pin_high(LCD_RS);	//RS=1 => DATA
		//_LcdPutData(data);
		//_LcdNybble();
		//_LcdPutData(data<<4);
		//_LcdNybble();
		//#undef data
		//break;
//
		//case _LCD_CURSOR_HOME:
		//gpio_set_pin_high(LCD_DATA4);
		//gpio_set_pin_high(LCD_DATA5);
		//gpio_set_pin_high(LCD_DATA6);
		//gpio_set_pin_high(LCD_DATA7);
//
		//gpio_set_pin_low(LCD_E);
		//gpio_set_pin_low(LCD_RS);
//
		//break;
		//case LCD_CLEAR:
		//_LcdCommand(LCD_CLEAR_DISPLAY);
		//delay_ms(1000);
		//break;
//
		//case _LCD_SET_RAM_ADDRESS:
		//#define _nLine	(pa1)
		//#define _nCol	(pa2)
		//_LcdCommand((line2addr[_nLine&0x03]+_nCol)|0x80);
		//#undef _nLine
		//#undef _nCol
		//break;
//
		//default:
		//Error(ERR_LCD_SWITCH_BAD_SC, sc);
	//}
	//return 0;
//}