/*
 * taskman.c
 *
 * Created: 31/01/2018 17:42:26
 *  Author: eleve
 */ 

 #include "appli.h"

 //D�claration de la liste des t�ches � ex�cuter
 t_task tasks[TASKMAN_TASKS_LIST_LEN];

 //D�claration de la liste des t�ches diff�r�es � ex�cuter
 t_task delayedTasks[TASKMAN_DELAYED_TASKS_LIST_LEN];

 //D�fintion de l'objet Taskman
 typedef struct tt_taskman{
	 t_task*pPush;
	 t_task*pPop;
 }t_taskman;


 //D�claration de l'unique objet Taskman
 t_taskman taskman;

 uint32_t Taskman(uint32_t sc, ...)
 {
	uint8_t criticalStatus;
	
	switch(sc)
	{
	case TASKMAN_NEW:
		taskman.pPop = taskman.pPush = tasks;

#define i sc
		for (i = 0; i <TASKMAN_DELAYED_TASKS_LIST_LEN; i++)
			delayedTasks[i].delay = 0;
#undef i
		break;

	case TASKMAN_PUSH_TASK:
#define pFunc_param     ((t_ptf)pa1)
#define sc_param        pa2
#define pa_param        ((void*)pa3)
#define delay_param     pa4

		//
	}
 }