/*
 * error.h
 *
 * Created: 29/01/2018 17:26:45
 *  Author: eleve
 */ 


#ifndef ERROR_H_
#define ERROR_H_

//Codes d'erreur de l'application
#define ERR_TASKMAN_SWITCH_BAD_SC                   11
#define ERR_SABLIER_SWITCH_BAD_SC                   12

#define ERR_TASKMAN_TASK_PUSH_BUFFER_FULL           21


//Prototype de la fonction concernée
uint32_t ErrorLed(uint32_t err, ...);
uint32_t ErrorUART(uint32_t err, ...);


extern t_ptf32 pErrorFunc;

#define Error(errc, sc)		pErrorFunc(errc, sc)

#endif /* ERROR_H_ */