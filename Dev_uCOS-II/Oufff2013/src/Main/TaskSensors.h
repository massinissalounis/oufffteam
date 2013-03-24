/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskSensors.h
*********************************************************************************************************
*/

#ifndef TASKSENSORS_H
#define TASKSENSORS_H

#include "AppIncludes.h"

BOOLEAN TaskSensors_IsStartButtonPressed();
	// Function to check StartButton stat
	// Param : None
	// Returned value :
	//	- TRUE : StartButton is beeing pressed
	//	- FALSE : StartButton is not beeing pressed yet

void TaskSensors_ReadColor();
	// Read current color and share it with other tasks

void TaskSensors_CheckBumpers();
	// Check for bumpers status.
	// In case of collision, this function posts FLAGS to indicate we are bumping something

void TaskSensors_GenerateStrategyFlags();
	// Generate all Strategy Flags associated to the TaskSensors task

void TaskSensors_Main(void *p_arg);
	// Fonction principal du process de gestion des Sensors
	// void *p_arg		: Arg for this task

#endif // TASKSENSORS_H
