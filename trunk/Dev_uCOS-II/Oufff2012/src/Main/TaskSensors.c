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
	if(COLOR_Read() != 0)
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

	static INT8U voting_logic_idx=0;

#ifdef _TARGET_440H

#else
	//GP2 Front ****************************************************
	GP2Data  = ADC_GetVal (GP2_FRONT);
	error_debug_1 = GP2Data;

	if(GP2Data > APP_GP2D2_LIMIT_FRONT)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_CLR, &Err); 

	//GP2 Back ******************************************************
	GP2Data  = ADC_GetVal (GP2_REAR);
	error_debug_2 = GP2Data;

	if(GP2Data > APP_GP2D2_LIMIT_BACK)
	{
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_BACK, OS_FLAG_SET, &Err); 
	}
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_BACK, OS_FLAG_CLR, &Err); 

#endif
}

// Grab Functions #################################################################################
// ------------------------------------------------------------------------------------------------
void TaskSensors_GrabIngotOnFloor()
{
	if(ADC_GetVal (GP2_HOLDER) > 600)
	{
		PUMP_Right_Suck();
		PUMP_Left_Suck();

		ARM_Left_GrabIngotOnFloor();
		ARM_Right_GrabIngotOnFloor();

		OSTimeDlyHMSM(0, 0, 0, 500);
		ELEVATOR_Level_Ingot();
		OSTimeDlyHMSM(0, 0, 0, 500);

		ELEVATOR_Level_High();
	}
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_GrabIngotOnTotem()
{
	ARM_Left_GrabIngotOnTotem();
	ARM_Right_GrabIngotOnTotem();

	WRIST_Left_Middle();
	WRIST_Right_Middle();

	PUMP_Left_Suck();
	PUMP_Right_Suck();

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_GrabCD()
{
	ARM_Left_GrabCD();
	ARM_Right_GrabCD();

	WRIST_Left_Down();
	WRIST_Right_Down();

	PUMP_Left_Suck();
	PUMP_Right_Suck();

	OSTimeDlyHMSM(0, 0, 0, 500);
	ELEVATOR_Level_CD();

	// TODO : Check if Low Level CD is required
	// if dist to CD, go to ELEVATOR_Level_Low

	OSTimeDlyHMSM(0, 0, 0, 500);

	ELEVATOR_Level_High();
	// TODO : Check if CD is grabbed

	return;
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


	// Debug ----------------
	CPU_INT16U  GP2Data;
	CPU_INT08U	SW_State;
	char		uart_buffer[8];
	char		*buffer_ptr;
	// ----------------------

	// Init
	Err = 0;
	CurrentState = 0;
	NextState = 0;
	pCurrentMsg = NULL;

	AppDebugMsg("OUFFF TEAM 2012 : Sensors online\r\n");
	
#ifdef	APP_INIT_EXEC_STARTUP_SEQ
	OSTimeDlyHMSM(0, 0, 2, 0);
	ARMS_Init();
#endif

#ifdef SENSORS_CALIBRATION
	OSTimeDlyHMSM(0, 0, 5, 0);
	
	while(OS_TRUE)
	{
		// Tirette + Color
/*		error_debug_1 = START_State();
		error_debug_2 = COLOR_Read();
		error_debug_3 = 0;
		error_debug_4 = 0;
		error_debug_5 = 0;
*/

		// SW Tests : 
/*		error_debug_1 = CLIC_state(CLIC_1);
		error_debug_2 = CLIC_state(CLIC_2);
		error_debug_3 = CLIC_state(CLIC_3);
		error_debug_4 = CLIC_state(CLIC_4);
		error_debug_5 = 0;
*/
		// GP2 tests (Serie 1) : 
/*		error_debug_1 = ADC_GetVal(GP2_1);
		error_debug_2 = ADC_GetVal(GP2_2);
		error_debug_3 = ADC_GetVal(GP2_3);
		error_debug_4 = ADC_GetVal(GP2_4);
		error_debug_5 = ADC_GetVal(GP2_5);
*/		
		// GP2 tests (Serie 1) : 
/*		error_debug_1 = ADC_GetVal(GP2_6);
		error_debug_2 = ADC_GetVal(GP2_7);
		error_debug_3 = ADC_GetVal(GP2_8);
		error_debug_4 = ADC_GetVal(GP2_9);
		error_debug_5 = ADC_GetVal(GP2_10);
*/		
		// Proc release
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
#endif


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
/*				case Sensors_GrabObject: // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
*/
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
