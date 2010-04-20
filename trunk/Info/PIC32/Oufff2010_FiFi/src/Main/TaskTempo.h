/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskTempo.h
*********************************************************************************************************
*/

#ifndef TASKTEMPO_H
#define TASKTEMPO_H

#include <AppIncludes.h>

void TaskTempo_Main(void *p_arg);
	// Fonction principal du process de temporisation
	// This task sleeps during 90sec, then it posts ending msg
	// void *p_arg		: Arg for this task (pointer to int that contains sleeping time in sec)



#endif // TASKTEMPO_H
