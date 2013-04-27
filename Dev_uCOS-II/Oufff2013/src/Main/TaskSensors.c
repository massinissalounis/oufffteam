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
	//GP2_REAR_INTERNAL *********************************************
	GP2Data  = ADC_GetVal (GP2_REAR_INTERNAL);
	TaskDebug_UpdateValueInt(TASKDEBUG_ID_GP2_REAR, GP2Data);
	if(GP2Data > APP_GP2_LIMIT_REAR_INTERNAL)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_INTERNAL_REAR, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_INTERNAL_REAR, OS_FLAG_CLR, &Err); 

	//GP2_REAR_HOOP *************************************************
	GP2Data  = ADC_GetVal (GP2_REAR_HOOP);

	if(GP2Data > APP_GP2_LIMIT_REAR_HOOP)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_HOOP, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_HOOP, OS_FLAG_CLR, &Err); 

	//GP2_REAR_LEFT_HOOP ********************************************
	GP2Data  = ADC_GetVal (GP2_REAR_LEFT_HOOP);

	if(GP2Data > APP_GP2_LIMIT_REAR_LEFT_HOOP)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_LEFT_HOOP, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_LEFT_HOOP, OS_FLAG_CLR, &Err); 

	//GP2_REAR_RIGHT_HOOP *******************************************
	GP2Data  = ADC_GetVal (GP2_REAR_RIGHT_HOOP);

	if(GP2Data > APP_GP2_LIMIT_REAR_RIGHT_HOOP)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_RIGHT_HOOP, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_RIGHT_HOOP, OS_FLAG_CLR, &Err); 

	//GP2_FRONT *****************************************************
	GP2Data  = ADC_GetVal (GP2_FRONT);

	if(GP2Data > APP_GP2_LIMIT_FRONT)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_CLR, &Err); 
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

	// Flag used to indicate to TaskMain if a collision has been detected
	StrategyReadValue = OSFlagAccept(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_ALL_STATE, OS_FLAG_WAIT_SET_ANY, &Err);
	
	// Flag flags which contains all sensors states
	SystemReadValue = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ALL_GP2, OS_FLAG_WAIT_SET_ANY, &Err);

	// Rear Sensors ########################################################################
	FlagsToCheck = 0;
	// Hoops is down ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN) == APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN)
	{
		// Rear hoop is down, we use (rear + left + right) sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_REAR_HOOP + APP_PARAM_APPFLAG_GP2_REAR_LEFT_HOOP + APP_PARAM_APPFLAG_GP2_REAR_RIGHT_HOOP);
	}
	else
	{
		// Rear hoop is up, we use internal sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_INTERNAL_REAR);
	}
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_REAR, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_REAR, OS_FLAG_CLR, &Err); 

	// Front Sensors #######################################################################
	FlagsToCheck = 0;
	// All cases ---------------
	FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT);
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_FRONT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_FRONT, OS_FLAG_CLR, &Err); 
	
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_FunnyAction()
{
	AppDebugMsg("Funny Action !!!\n");
	TURBINE_On();
	OSTimeDlyHMSM(0, 0, 10, 0);
	TURBINE_Off();
	AppDebugMsg("End of Funny Action.\n");
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

	// Init
	Err					= 0;
	CurrentState		= 0;
	NextState			= 0;
	pCurrentMsg			= NULL;
	LastColorRead		= c_NotSet;

	AppDebugMsg("OUFFF TEAM 2013 : Sensors online\r\n");
	
	// Task init : initialize all sensors
	HOOPS_InitReg();
	HOOPS_SetSpeed();
	TURBINE_Off();
	HOOPS_Up();

#ifdef	APP_INIT_EXEC_STARTUP_SEQ
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
				case Sensors_SetHoopLevel: 
					switch(pCurrentMsg->Param1)
					{
					case HOOP_LEVEL_DOWN:	HOOP_Back_Down();	AppDebugMsg("HOOP_Down\n");	break;
					case HOOP_LEVEL_UP:		HOOP_Back_Up();		AppDebugMsg("HOOP_Up\n");	break;
					default:									break;
					}


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
