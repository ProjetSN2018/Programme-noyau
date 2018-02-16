/*
 * appli.h
 *
 * Created: 29/01/2018 17:08:30
 *  Author: eleve
 */ 

#include "./asf.h"
#include <stdint.h>
//FICHIER H NOYAU//////////////////////////////////////////////////


#include "./Kernel/kernel.h"
#include "menu.h"


extern char buf[];

uint32_t Appli(uint32_t sc,...);

#define APPLI_NEW		100
#define APPLI_RUN		102
