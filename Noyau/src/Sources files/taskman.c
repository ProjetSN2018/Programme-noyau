/*
 * taskman.c
 *
 * Created: 31/01/2018 17:42:26
 *  Author: eleve
 */ 

 #include "../Headers/appli.h"

 //Déclaration de la liste des tâches à exécuter
 t_task tasks[TASKMAN_TASKS_LIST_LEN];

 //Déclaration de la liste des tâches différées à exécuter
 t_task delayedTasks[TASKMAN_DELAYED_TASKS_LIST_LEN];

 //Défintion de l'objet Taskman
 typedef struct tt_taskman{
	 t_task*pPush;
	 t_task*pPop;
 }t_taskman;


 //Déclaration de l'unique objet Taskman
 t_taskman taskman;

 uint32_t Taskman(uint32_t sc, ...)
 {
//	uint8_t criticalStatus;
	
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
		if(delay_param == 0)
		{
			taskman.pPush->pFunc = pFunc_param;
			taskman.pPush->sc = sc_param;
			taskman.pPush->param = pa_param;
			taskman.pPush++;
			//On rend le buffer circulaire => Implementation de la circularite du buffer de taches
			if(taskman.pPush>=tasks+TASKMAN_TASKS_LIST_LEN) taskman.pPush = tasks;
			//On test le debordement du buffer des teaches
			if(taskman.pPush == taskman.pPop) Error(ERR_TASKMAN_TASK_PUSH_BUFFER_FULL, 0);
		}
		break;

	case TASKMAN_POP_TASK:
		//Task buffer empty?
		if(taskman.pPop == taskman.pPush) return 0; //Buffer empty
		//Task buffer not empty?
		taskman.pPop->pFunc(taskman.pPop->sc, taskman.pPop->param);
		//Buffer circulaire
		taskman.pPop++;
		if(taskman.pPop>=tasks+TASKMAN_TASKS_LIST_LEN) taskman.pPop = tasks;
		break;

	default:
		Error(ERR_TASKMAN_SWITCH_BAD_SC, sc);
	}
	return 0;
 }