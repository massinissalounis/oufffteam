/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskDetection.c
*
* Suivi de version :
* 2014-06-05 | PBE | Creation de la version de base pour la coupe 2014
*********************************************************************************************************
*/

#include "TaskDetection.h"
#include "AppGlobalVars.h"

// ------------------------------------------------------------------------------------------------
void TaskDetection_Main(void *p_arg)
{
	OSTimeDlyHMSM(0, 0, 1, 0);
	AppDebugMsg("OUFFF TEAM 2014 : Detection online\n");
	
	// Main Loop
	while(OS_TRUE)
	{

		// Proc Release
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}
