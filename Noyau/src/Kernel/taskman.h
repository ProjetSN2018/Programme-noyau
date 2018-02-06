/*
 * taskman.h
 *
 * Created: 31/01/2018 17:42:40
 *  Author: eleve
 */ 


#ifndef TASKMAN_H_
#define TASKMAN_H_

#define TASKMAN_NEW                     100
//#define TASKMAN_DEL                   101 //Non utilis� car Environnement Temps R�el!!!
#define TASKMAN_PUSH_TASK               102
#define TASKMAN_POP_TASK                103
#define TASKMAN_DELAYED_TASK_PROCESS    104


//Constantes de Param�trage de taskman
//Longeur du buffer des t�ches imm�diates
#define TASKMAN_TASKS_LIST_LEN          10
//Longeur du buffer des t�ches diff�r�es
#define TASKMAN_DELAYED_TASKS_LIST_LEN  10

//type pointeur sur fonction pour les t�ches de l'application
typedef void (*t_ptf)(uint32_t, void*);


//D�fintion structure pour une t�che
typedef struct tt_task{
	t_ptf		pFunc;
	uint32_t	sc;
	void*		pParam;
	uint32_t	delay;
}t_task;

//Prototype de la fonction concern�e
uint32_t Taskman(uint32_t sc,...);

#define PushTask(pFunc,sc,param,delay)			Taskman(TASKMAN_PUSH_TASK,(uint32_t)pFunc,(uint32_t)sc,(uint32_t)param,(uint32_t)delay)
#define PopTask()								Taskman(TASKMAN_POP_TASK)

#endif /* TASKMAN_H_ */