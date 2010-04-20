/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskCapteurs.h
*********************************************************************************************************
*/

#ifndef TASKCAPTEURS_H
#define TASKCAPTEURS_H

#include <AppIncludes.h>

void TaskCapteurs_Main(void *p_arg);
	// Fonction principal du process de gestion des capteurs
	// void *p_arg		: Arg for this task

BOOLEAN TaskCapteurs_IsStartButtonPressed();
	// Function to check StartButton stat
	// Param : None
	// Returned value :
	//	- TRUE : StartButton has been pressed
	//	- FALSE : StartButton has not been pressed yet

void TaskCapteurs_CheckBumpers();
	// Check for bumpers status.
	// In case of collision, this function posts FLAGS to tell main task we are bumping

#endif // TASKCAPTEURS_H
