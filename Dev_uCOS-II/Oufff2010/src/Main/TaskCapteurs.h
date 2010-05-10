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

BOOLEAN TaskCapteurs_IsStartButtonPressed();
	// Function to check StartButton stat
	// Param : None
	// Returned value :
	//	- TRUE : StartButton is beeing pressed
	//	- FALSE : StartButton is not beeing pressed yet

void TaskCapteurs_CheckBumpers();
	// Check for bumpers status.
	// In case of collision, this function posts FLAGS to tell main task we are bumping

void TaskCapteurs_CheckClicClic();
	// Check for ClicClic status.

void TaskCapteurs_ReadColor();
	// Read current color and share it with other tasks

void TaskCapteurs_Main(void *p_arg);
	// Fonction principal du process de gestion des capteurs
	// void *p_arg		: Arg for this task

#endif // TASKCAPTEURS_H
