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

// ARMS functions _________________________________________________________________________________
void TaskSensors_ArmsClearStatus();
	// Function for clearing all arms state flags

void TaskSensors_ArmsInit();
	// Send the init command for each arms from selected colors

void TaskSensors_ArmsDeployment();
	// Send command for deploying arms

void TaskSensors_Main(void *p_arg);
	// Fonction principal du process de gestion des Sensors
	// void *p_arg		: Arg for this task

#endif // TASKSENSORS_H
