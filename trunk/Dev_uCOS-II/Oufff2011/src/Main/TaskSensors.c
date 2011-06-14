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

extern float error_debug_1;
extern float error_debug_2;
extern float error_debug_3;
extern float error_debug_4;
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
	CPU_INT16U  GP2Data;
	static CPU_INT16U GP2DataOld1=0;
	static CPU_INT16U GP2DataOld2=0;

	CPU_INT16U GP2DataAvg;
	CPU_INT16S GP2DataDiff1=0;
	CPU_INT16S GP2DataDiff2=0;

	static INT8U voting_logic_idx=0;

#ifdef _TARGET_440H

#else
	//GP2 Front ****************************************************
	GP2Data  = ADC_GetVal (GP2_FRONT);

	GP2DataDiff1 = GP2Data-GP2DataOld1;
	GP2DataDiff2 = GP2Data-GP2DataOld2;

	if(abs(GP2DataDiff1)<abs(GP2DataDiff2)) 
		GP2DataAvg = (GP2Data+GP2DataOld1)/2;
	else 
		GP2DataAvg = (GP2Data+GP2DataOld2)/2;	
	
	if(voting_logic_idx==0)
	{
		GP2DataOld1 = GP2Data;
		voting_logic_idx=1;
	}
	else
	{
		if (voting_logic_idx==1)
		{
			GP2DataOld2 = GP2Data;
			voting_logic_idx=0;
		}
	}

	if(GP2DataAvg > APP_GP2D2_LIMIT_FRONT)
	//if(error_debug_4 > APP_GP2D2_LIMIT_FRONT)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_CLR, &Err); 

//	error_debug_4 = GP2DataAvg;
//	error_debug_5 = GP2DataAvg;

	if(error_debug_5 < error_debug_4)
		error_debug_5 = error_debug_4;

	//GP2 Back ******************************************************
	GP2Data  = ADC_GetVal (GP2_REAR);
	if(GP2Data > APP_GP2D2_LIMIT_BACK)
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
		case HOLDER_CLOSE: 
			HOLDER_Close();
			break;

		case HOLDER_OPEN_LEFT_ONLY:
			HOLDER_Open_Left_Only();
			break;

		case HOLDER_OPEN_RIGHT_ONLY:
			HOLDER_Open_Right_Only();
			break;
			
		case HOLDER_OPEN:
			HOLDER_Open();
			break;

		case HOLDER_GRAB:
			TaskSensors_GrabObject();
			break;

		case HOLDER_GRIP:
			HOLDER_Grip();
			break;

		default:
			HOLDER_Close();
			break;
	}

	return;	
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_SetHolderLevel(INT8U Level)
{
	switch(Level)
	{
		case HOLDER_LEVEL_MIDDLE:
			HOLDER_Level_Middle();
			break;

		case HOLDER_LEVEL_HIGH:
			HOLDER_Level_High();
			break;
			
		case HOLDER_LEVEL_LOW: 
		default:
			HOLDER_Level_Low();
			break;
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_CheckObject()
{
	INT8U	Err = 0;						// Var to get error status
	CPU_INT16U  GP2Data;

	GP2Data  = ADC_GetVal (GP2_HOLDER);

	if(GP2Data > APP_GP2D2_LIMIT_HOLDER_IN)
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
	error_debug_5 = 0;

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

	LED_On(4);

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
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				case Sensors_SetHolderStatus: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					TaskSensors_ControlHolder(pCurrentMsg->Param1);
					if(CmdType_Blocking == pCurrentMsg->CmdType)
					{
						OSTimeDlyHMSM(0,0,0,50);
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					}
					NextState = 1;
					break;

				case Sensors_SetHolderLevel: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					TaskSensors_SetHolderLevel(pCurrentMsg->Param1);
					if(CmdType_Blocking == pCurrentMsg->CmdType)
					{
						OSTimeDlyHMSM(0,0,1,200);
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					}
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
