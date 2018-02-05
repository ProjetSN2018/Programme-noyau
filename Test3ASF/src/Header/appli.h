/*
 * appli.h
 *
 * Created: 29/01/2018 17:08:30
 *  Author: eleve
 */ 


#ifndef APPLI_H_
#define APPLI_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef uint32_t(*t_ptf32) (uint32_t, ...);
#include "../asf.h"
#include "error.h"
#include "taskman.h"
#include "config_uart.h"



//Accès aux contenus des paramètres optionnels des fonctions
#define pa1         (*(&sc+1))
#define pa2         (*(&sc+2))
#define pa3         (*(&sc+3))
#define pa4         (*(&sc+4))
#define pa5         (*(&sc+5))

//Accès aux adresses des paramètres optionnels des fonctions
#define pPa1         (&sc+1)
#define pPa2         (&sc+2)
#define pPa3         (&sc+3)
#define pPa4         (&sc+4)
#define pPa5         (&sc+5)


#define mBitsSet(flags,mask)     (flags|=(mask))
#define mBitsClr(flags,mask)     (flags&=~(mask))
#define mBitsTgl(flags,mask)     (flags^=(mask))
#define mBitsMsk(flags,mask)     (flags&(mask))

#define mIsBitsSet(flags,mask)   (( (flags&(mask)))==(mask))
#define mIsBitsClr(flags,mask)   ((~flags&(mask)))==(mask))

#endif /* APPLI_H_ */