/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskMvt.h
*********************************************************************************************************
*/

#ifndef TASKMVT_H
#define TASKMVT_H

#include "AppIncludes.h"
#include "LibMoving.h"

void TaskMvt_SendSetpointToTaskAsser(StructCmd *Setpoint);
	// Function for sending new command to TaskAsser
	// Setpoint			: Expected Setpoint

void TaskMvt_Main(void *p_arg);
	// Fonction principal du process de deplacement
	// void *p_arg		: No Arg



#endif // TASKMVT_H
