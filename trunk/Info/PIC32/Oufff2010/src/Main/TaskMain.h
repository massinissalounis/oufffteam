/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskMain.h
*********************************************************************************************************
*/

#ifndef TASKMAIN_H
#define TASKMAIN_H

#include <AppIncludes.h>

// Vars -------------------------------------------------------------------------------------------
StructPos TaskMain_CurrentPos;							// Local var to read current pos

// Functions --------------------------------------------------------------------------------------
void TaskMain_Main(void *p_arg);
	// Fonction principale
	// void *p_arg		: Arg for this task

void TaskMain_Init();
	// Init function

void TaskMain_CheckForBumpers();
	// Read bumpers flags to check for collision
	// In case of collision, this function create a new crossing point
	//	- For front bumps : We go back
	//  - For other bumps : We stop moving 

void TaskMain_GetCurrentPos();
	// Function to read current position
	// Value are stored into local var

void TaskMain_StopMvt();
	// Function to stop mvt to current position

#endif // TASKMAIN_H
