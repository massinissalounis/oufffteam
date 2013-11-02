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

#include "AppIncludes.h"

// Functions --------------------------------------------------------------------------------------
void TaskMain_SendSetpointToTaskMvt(StructCmd *NextCmd);
	// Function for sending new command to TaskMvt
	// NextCmd			: Cmd to send

void TaskMain_Main(void *p_arg);
	// Fonction principale
	// void *p_arg		: Arg for this task


#endif // TASKMAIN_H
