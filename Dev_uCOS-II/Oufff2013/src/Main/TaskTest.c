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

// ------------------------------------------------------------------------------------------------
void TaskTest_Main(void *p_arg)
{

#ifdef APP_TASK_TEST_ENABLED
	AppDebugMsg("OUFFF TEAM 2013 : Test online <<<<<<<<<< WARNING !!! >>>>>>>>>>>\n");
	
	//TaskDebug_RegisterNewData(TASKDEBUG_ID_TEST, "Test");

	// Main Loop
	while(OS_TRUE)
	{
		// Test Code : Begin ______________________________________________________________________

		// Test Code : End ________________________________________________________________________

		// Attente avant le prochain message de debug	
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
#else
	// Attente infinie	
	OSTimeDlyHMSM(1, 0, 0, 0);
#endif

}
