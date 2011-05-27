/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskSensors.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************
*/

#include "TaskSensors.h"

// ------------------------------------------------------------------------------------------------
BOOLEAN TaskSensors_IsStartButtonPressed()
{
	if(START_State()==0) 
		return OS_TRUE;
	else 
		return OS_FALSE;
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ReadColor()
{
	// Read current color
	if(COLOR_Read() == 0)
		AppCurrentColor = c_ColorA;
	else	
		AppCurrentColor = c_ColorB;

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_CheckBumpers()
{
	INT8U	Err = 0;						// Var to get error status

#ifdef _TARGET_440H

#else

#endif
}

// ------------------------------------------------------------------------------------------------
// TaskSensors_Main()
// ------------------------------------------------------------------------------------------------
void TaskSensors_Main(void *p_arg)
{
	INT8U		Err;				// Var to get error status
	INT8U		CurrentState;		// Used into state machine
	INT8U		NextState;			// Used into state machine
	StructMsg	*pCurrentMsg;		// For retreiving data from TaskMain

	// Init
	Err = 0;
	CurrentState = 0;
	NextState = 0;
	pCurrentMsg = NULL;


	AppDebugMsg("OUFFF TEAM 2011 : Sensors online\n");

	if(APP_INIT_USE_START_BUTTON == OS_TRUE)
	{
		// We're waiting for Start button release
		while(OS_FALSE == TaskSensors_IsStartButtonPressed())
		{
			TaskSensors_ReadColor();
			OSTimeDly(1);	// Release proc
		}

		// We're waiting for start button activation
		while(OS_TRUE == TaskSensors_IsStartButtonPressed())
		{
			TaskSensors_ReadColor();
			OSTimeDly(1);	// Release proc
		}
	}

	TaskSensors_ReadColor();

	// StartButton has been pressed
	OSFlagPost(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_SET, &Err); 

	do
	{
		OSTimeDlyHMSM(0, 0, 0, 10);	

		// First step, we check all external sensors
		TaskSensors_CheckBumpers();

		// Then, we use the state machine
		CurrentState = NextState;
		switch(CurrentState)
		{
		// CASE 0 : We are waiting for an incomming msg -------------------------------------------
		case 0:
			// Check if a msg is currently in use
			if(NULL == pCurrentMsg)
			{
				// Unlock msg
				pCurrentMsg->IsRead = OS_TRUE;
				pCurrentMsg = NULL;
			}

			// Try to read another msg
			pCurrentMsg = (StructMsg*)OSQAccept(AppQueueSensors, &Err);
			if(NULL == pCurrentMsg)
			{
				// No msg is available
				NextState = 0;
			}
			else
			{
				// Select Action from Cmd
				switch(pCurrentMsg->CmdType)
				{
				case Sensors_OpenClamp: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					NextState = 1;
					break;

				default: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					NextState = 0;
					break;
				}
			}
			break;

		// CASE 10 : Action 1 = Open Clamp --------------------------------------------------------
		case 10:
			// Todo : Send order
			if(CmdType_Blocking == pCurrentMsg->CmdType)
				NextState = 11;			// We want to wait the end of this action
			else
				NextState = 0;			// We don't want to wait the end of this action 
			break;

		// CASE 11 : Action 1 = Wait for complete openning ----------------------------------------
		case 11:
			// Todo : Faire le check du flag
			NextState = 0;
			break;

		// CASE 255 : Final state -----------------------------------------------------------------
		case 255:
			NextState = 255;

			break;

		// DEFAULT --------------------------------------------------------------------------------
		default:
			NextState = 0;
			break;
		}
	}while(CurrentState != 255);	

	// End of task
	while(OS_TRUE)
	{
		OSTimeDlyHMSM(0, 0, 30, 0);	
	}
}
