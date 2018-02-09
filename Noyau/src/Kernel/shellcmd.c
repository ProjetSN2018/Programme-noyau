/*
 * shellcmd.c
 *
 * Created: 07/02/2018 17:29:14
 *  Author: Mod_loc
 */ 

#include "./Headers/appli.h"
#include "shellcmd.h"

#define	PORT	IOPORT_PIOD


const t_cmdEntry _cmdEntries[] ={
	{ 0x6CAB, _cmd_set		},
	{ 0xAAF6, _cmd_show		},	

	//////////////////LIST TERMINATOR ////////////////////////////
	{	0,	NULL			}	
};

void _cmd_set(uint32_t sc, void* pParam)
{
	//Putstr(buf);
	ioport_init();
	ioport_set_pin_dir(PORT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PORT, (int)pParam);
	Putstr(pParam);
	ioport_get_pin_level(PORT);
	sprintf(buf, "\r\nLe pin est a l'etat: %d\r\n", ioport_get_pin_level(PORT));
	Putstr(buf);
}

void _cmd_show(uint32_t sc, void* pParam)
 {
	if(ioport_get_pin_level(PORT))
	{
		sprintf(buf, "L'etat de la broche etait haut \r\n");
		ioport_set_pin_level(PORT,0);
		Putstr(buf);
	}
	else
	{
	sprintf(buf, "L'etat de la broche etait bas \r\n");
	ioport_set_pin_level(PORT,1);
	Putstr(buf);

	}
	//sprintf(buf, "Hello!!! \r\n");
	//Putstr(buf);
 }