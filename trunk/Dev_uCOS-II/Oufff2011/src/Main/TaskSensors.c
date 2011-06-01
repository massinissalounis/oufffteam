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

extern float error_debug_5;
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
	CPU_INT16U  GP2Data_1;
	CPU_INT16U  GP2Data_2;

#ifdef _TARGET_440H

#else
	//GP2 Front Left ************************************************
	GP2Data_1  = ADC_GetVal (GP2_FRONT_LEFT);
	if(GP2Data_1 > APP_GP2D2_LIMIT_FRONT_LEFT)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_LEFT, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_LEFT, OS_FLAG_CLR, &Err); 

	//GP2 Front Right ***********************************************
	GP2Data_2  = ADC_GetVal (GP2_FRONT_RIGHT);
	if(GP2Data_2 > APP_GP2D2_LIMIT_FRONT_RIGHT)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT, OS_FLAG_CLR, &Err); 

	//GP2 Front (Right + Left) **************************************
	if((GP2Data_1 + GP2Data_2) > 2*APP_GP2D2_LIMIT_FRONT)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_CLR, &Err); 

	//GP2 Back ******************************************************
	GP2Data_1  = ADC_GetVal (GP2_REAR);
	if(GP2Data_1 > APP_GP2D2_LIMIT_BACK)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_BACK, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_BACK, OS_FLAG_CLR, &Err); 

	
#endif
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_GrabObject()
{
	CPU_INT16U  GP2Data;

	HOLDER_Hold();
	OSTimeDlyHMSM(0,0,0,500);

	GP2Data  = ADC_GetVal (GP2_HOLDER);
	if(GP2Data < APP_GP2D2_LIMIT_HOLDER_IN)
	{
		HOLDER_Open();
	}	

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ControlHolder(CPU_INT08U control)
{
	switch(control)
	{
		case 0: 
			HOLDER_Close();
			break;

		case 1:
			HOLDER_Open_Left_Only();
			break;

		case 2:
			HOLDER_Open_Right_Only();
			break;
			
		case 3:
			HOLDER_Open();
			break;

		case 4:
			TaskSensors_GrabObject();

		default:
			HOLDER_Close();
	}
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_CheckObject()
{
	INT8U	Err = 0;						// Var to get error status
	CPU_INT16U  GP2Data;

	GP2Data  = ADC_GetVal (GP2_HOLDER);

	if(GP2Data < APP_GP2D2_LIMIT_HOLDER_IN)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_CLR, &Err); 	
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
	OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err); 

	HOLDER_Init();

	CPU_INT16U  GP2Data;
	do
	{
		OSTimeDlyHMSM(0, 0, 0, 10);	

		// First step, we check all external sensors
		TaskSensors_CheckBumpers();
		TaskSensors_CheckObject();

		// Then, we use the state machine
		CurrentState = NextState;
		switch(CurrentState)
		{
		// CASE 0 : We are waiting for an incomming msg -------------------------------------------
		case 0:
			// Check if a msg is currently in use
			if(NULL != pCurrentMsg)
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
				switch(pCurrentMsg->Cmd)
				{
				case Sensors_GrabObject: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					TaskSensors_GrabObject();
					OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				default: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					NextState = 0;
					break;
				}
			}
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
