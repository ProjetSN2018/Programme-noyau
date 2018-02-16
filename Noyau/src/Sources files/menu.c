/*
 * menu.c
 *
 * Created: 16/02/2018 14:29:06
 *  Author: eleve
 */ 
 #include "./Headers/appli.h"
  /////////////////////////////////INTERRUPT TEST//////////////
  void pin_edge_handler(void);
  const char* tabl[] = {
	  ("\r\nBONJOUR,\r\n"),
	  ("\r\ncomment\r\n"),
	  ("\r\naller\r\n"),
	  ("\r\nvous?\r\n")
  };
  int i = 0;

  int Menu(int sc, ...)
  {
	switch(sc)
	{
	case MENU_NEW:
		
		//////////////////////////////////////INTERRUPT PIN/////////////////////////////
		pmc_enable_periph_clk(ID_PIOA);
		pio_set_output(PIOA, PIO_PA23, LOW, DISABLE, ENABLE);
		pio_set_output(PIOA, PIO_PA24, LOW, DISABLE, ENABLE);
		pio_set_input(PIOA, PIO_PA16, PIO_PULLUP);
		pio_handler_set(PIOA, ID_PIOA, PIO_PA16, PIO_IT_FALL_EDGE, pin_edge_handler);
		pio_enable_interrupt(PIOA, PIO_PA16);
		NVIC_EnableIRQ(PIOA_IRQn);
	
		////////////////////////////////////////////////////////////////////////////////
		break;
	case MENU_BUTTON:
		 pio_toggle_pin(PIO_PA23_IDX);
		 
		 sprintf(buf, tabl[i]);
		 Putstr(buf);
		 i++;
		 if(i >=4) i =0;
		break;

	case MENU_SELECTED:
		
		break;
	default:
		Error(ERR_MENU_SWITCH_BAD_SC, sc);
	}
  }

   void pin_edge_handler()
   {
	   PushTask(Menu,MENU_BUTTON,0,0);
   }
