/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskDebug.c
*
* Suivi de version :
* 2013-03-07 | PBE | Creation de la version de base pour la coupe 2013
*********************************************************************************************************
*/

#include "TaskTest.h"
#include "AppGlobalVars.h"
#include "TaskSensors.h"

// ------------------------------------------------------------------------------------------------
void TaskTest_Main(void *p_arg)
{

#ifdef APP_TASK_TEST_ENABLED
	OSTimeDlyHMSM(0, 0, 1, 0);
	AppDebugMsg("OUFFF TEAM 2013 : Test online <<<<<<<<<< WARNING !!! >>>>>>>>>>>\n");
	
	// Main Loop
	while(OS_TRUE)
	{
		// Test Code : Begin ______________________________________________________________________

		// Test Code : End ________________________________________________________________________

		OSTimeDlyHMSM(0, 0, 0, 250);
	}
#else
	// Attente infinie	
	OSTimeDlyHMSM(1, 0, 0, 0);
#endif

}
