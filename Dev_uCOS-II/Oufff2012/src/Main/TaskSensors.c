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

#ifdef _TARGET_440H

#else
	//GP2_REAR_CENTER ***********************************************
	GP2Data  = ADC_GetVal (GP2_REAR_CENTER);

	if(GP2Data > APP_GP2_LIMIT_REAR_CENTER)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_CENTER, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_CENTER, OS_FLAG_CLR, &Err); 

	//GP2_FRONT_CENTER **********************************************
	GP2Data  = ADC_GetVal (GP2_FRONT_CENTER);

	if(GP2Data > APP_GP2_LIMIT_FRONT_CENTER)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_CENTER, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_CENTER, OS_FLAG_CLR, &Err); 

	//GP2_FRONT_LEFT_1 **********************************************
	GP2Data  = ADC_GetVal (GP2_FRONT_LEFT_1);

	if(GP2Data > APP_GP2_LIMIT_FRONT_LEFT_1)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_LEFT_1, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_LEFT_1, OS_FLAG_CLR, &Err); 

	//GP2_FRONT_LEFT_2 **********************************************
	GP2Data  = ADC_GetVal (GP2_FRONT_LEFT_2);

	if(GP2Data > APP_GP2_LIMIT_FRONT_LEFT_2)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_LEFT_2, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_LEFT_2, OS_FLAG_CLR, &Err); 

	//GP2_FRONT_RIGHT_1 *********************************************
	GP2Data  = ADC_GetVal (GP2_FRONT_RIGHT_1);

	if(GP2Data > APP_GP2_LIMIT_FRONT_RIGHT_1)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_1, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_1, OS_FLAG_CLR, &Err); 

	//GP2_FRONT_RIGHT_2 *********************************************
	GP2Data  = ADC_GetVal (GP2_FRONT_RIGHT_2);

	if(GP2Data > APP_GP2_LIMIT_FRONT_RIGHT_2)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_2, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_2, OS_FLAG_CLR, &Err); 

	//GP2_FRONT_RIGHT_3 *********************************************
	GP2Data  = ADC_GetVal (GP2_FRONT_RIGHT_3);

	if(GP2Data > APP_GP2_LIMIT_FRONT_RIGHT_3)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_3, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_3, OS_FLAG_CLR, &Err); 
#endif
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_GenerateStrategyFlags()
{
	INT8U		Err;				// Var to get error status
	OS_FLAGS	SystemReadValue;	// Var for reading the system flags
	OS_FLAGS	StrategyReadValue;	// Var for reading the strategy flags
	OS_FLAGS	FlagsToCheck;		// Var for storing elements we want to check

	// Init
	Err = 0;				
	SystemReadValue = 0;	
	StrategyReadValue = 0;
	FlagsToCheck = 0;		

	StrategyReadValue = OSFlagAccept(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_ARMS_STATUS, OS_FLAG_WAIT_SET_ANY, &Err);
	SystemReadValue = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ALL_GP2, OS_FLAG_WAIT_SET_ANY, &Err);

	// Rear Sensors ########################################################################
	FlagsToCheck = 0;
	// All case ---------------

	FlagsToCheck = (APP_PARAM_APPFLAG_GP2_REAR_CENTER);
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_REAR, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_REAR, OS_FLAG_CLR, &Err); 

	// Front Sensors #######################################################################
	FlagsToCheck = 0;
	// Arms Init ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_INIT) == APP_PARAM_STRATEGYFLAG_ARMS_IS_INIT)
	{
		if(AppCurrentColor == c_ColorA)		// Red
			FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_CENTER + APP_PARAM_APPFLAG_GP2_FRONT_LEFT_1 + APP_PARAM_APPFLAG_GP2_FRONT_LEFT_2);

		if(AppCurrentColor == c_ColorB)		// Purple
			FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_CENTER + APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_1 + APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_2);
	}

	// Arms Opened ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED) == APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED)
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_3);

	// Arms Closed ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED) == APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED)
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_LEFT_1 + APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_1);

	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_FRONT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_FRONT, OS_FLAG_CLR, &Err); 
	
	// Left Sensors #####################################################################
	FlagsToCheck = 0;
	// Arms Opened ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED) == APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED)
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_LEFT_1 + APP_PARAM_APPFLAG_GP2_FRONT_LEFT_2);

	// Arms Closed ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED) == APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED)
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_LEFT_2);

	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_LEFT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_LEFT, OS_FLAG_CLR, &Err); 

	// Right Sensors #####################################################################
	FlagsToCheck = 0;
	// Arms Opened ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED) == APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED)
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_1 + APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_2);

	// Arms Closed ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED) == APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED)
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT_RIGHT_2);

	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT, OS_FLAG_CLR, &Err); 
}

// ARMS functions _________________________________________________________________________________
// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsSetStatus(OS_FLAGS flags)
{	
	INT8U		Err;				// Var to get error status
	OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_ARMS_STATUS, OS_FLAG_CLR, &Err);
	OSFlagPost(AppStrategyFlags, flags, OS_FLAG_SET, &Err); 
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsInit()
{
	if(AppCurrentColor == c_ColorA)		// Red
		ARMS_DefaultPosRed();

	if(AppCurrentColor == c_ColorB)		// Purple
		ARMS_DefaultPosPurple();

	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_INIT);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsDeployment()
{
	if(AppCurrentColor == c_ColorA)		// Red
		ARMS_DeploymentRed();

	if(AppCurrentColor == c_ColorB)		// Purple
		ARMS_DeploymentPurple();

	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsOpenDown()
{
	ARMS_OpenDown();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsOpenUp()
{
	ARMS_OpenUp();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsClose()
{
	ARMS_Close();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsOpenOneCD()
{
	ARMS_OpenOneCD();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsOpenTotem()
{
	ARMS_OpenTotem();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsCloseTotem()
{
	ARMS_CloseTotem();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_CLOSED);
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ArmsUngrab()
{
	ARMS_Ungrab();
	TaskSensors_ArmsSetStatus(APP_PARAM_STRATEGYFLAG_ARMS_IS_OPENED);
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
	EnumColor	LastColorRead;		// Used to check color modification

	// Debug ----------------
	CPU_INT16U  GP2Data;
	CPU_INT08U	SW_State;
	char		uart_buffer[8];
	char		*buffer_ptr;
	// ----------------------

	// Init
	Err					= 0;
	CurrentState		= 0;
	NextState			= 0;
	pCurrentMsg			= NULL;
	LastColorRead		= c_NotSet;

	AppDebugMsg("OUFFF TEAM 2012 : Sensors online\r\n");
	
#ifdef	APP_INIT_EXEC_STARTUP_SEQ
#endif

	ARMS_SetSpeed();

#ifdef SENSORS_CALIBRATION
	TaskSensors_ReadColor();
	
// Arms Init from color
//	OSTimeDlyHMSM(0, 0, 1, 0);
//	TaskSensors_ArmsInit();

	// Deployment
//	OSTimeDlyHMSM(0, 0, 3, 0);
//	TaskSensors_ArmsDeployment();

//	TaskSensors_Armspen();

//	OSTimeDlyHMSM(0, 0, 3, 0);
//	TaskSensors_ArmsOpenOneCD();

//	OSTimeDlyHMSM(0, 0, 10, 0);
//	TaskSensors_ArmsOpenTotem();

//	OSTimeDlyHMSM(0, 0, 10, 0);
//	TaskSensors_ArmsCloseTotem();
	
//	OSTimeDlyHMSM(0, 0, 10, 0);
//	TaskSensors_ArmsClose();

//	OSTimeDlyHMSM(0, 0, 3, 0);
	TaskSensors_ArmsUngrab();

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

			if(LastColorRead != AppCurrentColor)
			{
				LastColorRead = AppCurrentColor;
				TaskSensors_ArmsInit();
			}
		}

		// We're waiting for start button activation
		while(OS_TRUE == TaskSensors_IsStartButtonPressed())
		{
			TaskSensors_ReadColor();
			OSTimeDly(1);	// Release proc

			if(LastColorRead != AppCurrentColor)
			{
				LastColorRead = AppCurrentColor;
				TaskSensors_ArmsInit();
			}
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
		TaskSensors_GenerateStrategyFlags();

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
				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsOpenDown: 
					TaskSensors_ArmsOpenDown();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsOpenUp: 
					TaskSensors_ArmsOpenUp();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsDeployment: 
					TaskSensors_ArmsDeployment();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsOpenTotem:
					TaskSensors_ArmsOpenTotem();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsOpenOneCD:
					TaskSensors_ArmsOpenOneCD();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsClose:
					TaskSensors_ArmsClose();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsCloseTotem:
					TaskSensors_ArmsCloseTotem();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_ArmsUngrab:
					TaskSensors_ArmsUngrab();
					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				default: 
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
