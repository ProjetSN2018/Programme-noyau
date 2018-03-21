/*
 * sas.c
 *
 * Created: 19/03/2018 15:06:35
 *  Author: eleve
 */ 
#include "./Headers/appli.h"

int Sas(int sc, ...)
{
	switch(sc)
	{
	case SAS_FERMER_SAS:
		sprintf(buf, "Fermeture SAS");
		Putstr(buf);
		break;
	case SAS_FERMER_PORTE1:
		sprintf(buf, "Fermeture Porte 1");
		Putstr(buf);
		break;
	case SAS_FERMER_PORTE2:
		sprintf(buf, "Fermeture Porte 2");
		Putstr(buf);
		break;
	default:
		Error(ERR_SAS_SWITCH_BAD_SC, sc);
		break;
	}

}
