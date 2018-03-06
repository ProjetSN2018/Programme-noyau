/*
 * sas.c
 *
 * Created: 05/03/2018 17:15:00
 *  Author: eleve
 */ 
#include "./Headers/appli.h"

int Sas(int sc, ...)
{
	
	switch(sc)
	{
	case 0:
		sprintf(buf, "\r\nHello,\r\n");
		Putstr(buf);
		break;
	case 1:
		sprintf(buf, "\r\nHow\r\n");
		Putstr(buf);
		break;
	case 2:
		sprintf(buf, "\r\nyou\r\n");
		Putstr(buf);
		break;
	case 3:
		sprintf(buf, "\r\ndoing\r\n");
		Putstr(buf);
		break;
	case 4:
		sprintf(buf, "\r\n!!!\r\n");
		Putstr(buf);
		break;
	default:
		Error(ERR_SAS_SWITCH_BAD_SC, sc);
	}
}
