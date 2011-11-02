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
	// In case of collision, this function posts FLAGS to tell main task we are bumping

void TaskSensors_GrabObject();
	// Function for grabbing an object.

void TaskSensors_ControlHolder(CPU_INT08U control);

void TaskSensors_SetHolderLevel(INT8U Level);
	// Function for setting the Holder level.
	// Level can be set to the following values :
	// Level = 	HOLDER_LEVEL_LOW, HOLDER_LEVEL_MIDDLE, HOLDER_LEVEL_HIGH

void TaskSensors_Main(void *p_arg);
	// Fonction principal du process de gestion des Sensors
	// void *p_arg		: Arg for this task

#endif // TASKSENSORS_H
