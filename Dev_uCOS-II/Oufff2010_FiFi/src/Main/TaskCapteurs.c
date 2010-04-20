/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskCapteurs.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
*********************************************************************************************************
*/

#include "TaskCapteurs.h"
#include "AppGlobalVars.h"

// ------------------------------------------------------------------------------------------------
BOOLEAN TaskCapteurs_IsStartButtonPressed()
{
	return OS_TRUE;
}

// ------------------------------------------------------------------------------------------------
void TaskCapteurs_CheckBumpers()
{
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskCapteurs_ReadColor()
{
	#ifdef _TARGET_STARTER_KIT
		AppCurrentColor = c_Blue;	
	#else
		// Read current color
		// ToDo : Read color
	#endif

	return;
}

// ------------------------------------------------------------------------------------------------
// TaskCapteurs_Main()
// ------------------------------------------------------------------------------------------------
void TaskCapteurs_Main(void *p_arg)
{
	INT8U	Err = 0;				/* Var to get error status								*/

	#ifdef _TARGET_STARTER_KIT
		OSTimeDlyHMSM(0, 0, 0, 500);	LED_Off(1);	
		OSTimeDlyHMSM(0, 0, 0, 500);	LED_Off(2);	
		OSTimeDlyHMSM(0, 0, 0, 500);	LED_Off(3);
	#else
		// We're waiting for Start button release
		while(OS_TRUE == TaskCapteurs_IsStartButtonPressed())
			OSTimeDly(1);	// Release proc

		// We're waiting for start button activation
		while(OS_FALSE == TaskCapteurs_IsStartButtonPressed())
			OSTimeDly(1);	// Release proc
	#endif

	// StartButton has been pressed
	// We set the current color
	TaskCapteurs_ReadColor();
	
	OSFlagPost(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_SET, &Err); 

	while(OS_TRUE)	// Main task: we check all other sensors
	{
		TaskCapteurs_CheckBumpers();			// Check for bumpers status
		OSTimeDly(100);
	}
}
