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
# define GP2_FILTER_THRESHOLD 2 // Oui je suis un gros sale de mettre ca là et alors ....

void TaskSensors_CheckBumpers()
{
	INT8U	Err = 0;						// Var to get error status
	CPU_INT16U  GP2Data;

	static	INT8U	GP2_INTERNAL_REAR_Counter = 0;
	static	INT8U	GP2_INTERNAL_REAR_LONG_Counter = 0;
	static	INT8U	GP2_REAR_HOOP_Counter = 0;
	static	INT8U	GP2_LEFT_HOOP_Counter = 0;
	static	INT8U	GP2_RIGHT_HOOP_Counter = 0;
	static	INT8U	GP2_FRONT_Counter = 0;

#ifdef _TARGET_440H

#else
	//GP2_REAR_INTERNAL *********************************************
	GP2Data  = ADC_GetVal (GP2_REAR_INTERNAL);
	TaskDebug_UpdateValueInt(TASKDEBUG_ID_GP2_REAR_INTERNAL, GP2Data);
	
	if(GP2Data > APP_GP2_LIMIT_REAR_INTERNAL)
	{
		GP2_INTERNAL_REAR_Counter++;
		if(GP2_INTERNAL_REAR_Counter>= GP2_FILTER_THRESHOLD)
			OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_INTERNAL_REAR, OS_FLAG_SET, &Err); 
	}
	else
	{
		GP2_INTERNAL_REAR_Counter = 0;
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_INTERNAL_REAR, OS_FLAG_CLR, &Err); 
	}

	// Long detection for Rear Internal
	if(GP2Data > APP_GP2_LIMIT_REAR_INTERNAL_LONG_DETECTION)
	{
		GP2_INTERNAL_REAR_LONG_Counter++;
		if(GP2_INTERNAL_REAR_LONG_Counter>= GP2_FILTER_THRESHOLD)
			OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_INTERNAL_REAR_LONG, OS_FLAG_SET, &Err);
	}
	else
	{
		GP2_INTERNAL_REAR_LONG_Counter = 0;
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_INTERNAL_REAR_LONG, OS_FLAG_CLR, &Err); 
	}	
		
	//GP2_REAR_HOOP *************************************************
	GP2Data  = ADC_GetVal (GP2_REAR_HOOP);
	TaskDebug_UpdateValueInt(TASKDEBUG_ID_GP2_REAR, GP2Data);

	if(GP2Data > APP_GP2_LIMIT_REAR_HOOP)
	{
		GP2_REAR_HOOP_Counter++;
		if(GP2_REAR_HOOP_Counter>=GP2_FILTER_THRESHOLD)
			OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_HOOP, OS_FLAG_SET, &Err); 
	}
	else
	{
		GP2_REAR_HOOP_Counter = 0;
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_HOOP, OS_FLAG_CLR, &Err); 
	}

	//GP2_REAR_LEFT_HOOP ********************************************
	GP2Data  = ADC_GetVal (GP2_REAR_LEFT_HOOP);
	TaskDebug_UpdateValueInt(TASKDEBUG_ID_GP2_REAR_LEFT, GP2Data);

	if(GP2Data > APP_GP2_LIMIT_REAR_LEFT_HOOP)
	{
		GP2_LEFT_HOOP_Counter++;
		if(GP2_LEFT_HOOP_Counter>= GP2_FILTER_THRESHOLD)
			OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_LEFT_HOOP, OS_FLAG_SET, &Err); 
	}
	else
	{
		GP2_LEFT_HOOP_Counter = 0;
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_LEFT_HOOP, OS_FLAG_CLR, &Err); 
	}

	//GP2_REAR_RIGHT_HOOP *******************************************
	GP2Data  = ADC_GetVal (GP2_REAR_RIGHT_HOOP);
	TaskDebug_UpdateValueInt(TASKDEBUG_ID_GP2_REAR_RIGHT, GP2Data);

	if(GP2Data > APP_GP2_LIMIT_REAR_RIGHT_HOOP)
	{
		GP2_RIGHT_HOOP_Counter++;
		if(GP2_RIGHT_HOOP_Counter>= GP2_FILTER_THRESHOLD)
			OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_RIGHT_HOOP, OS_FLAG_SET, &Err);
	}
	else
	{
		GP2_RIGHT_HOOP_Counter = 0;
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_REAR_RIGHT_HOOP, OS_FLAG_CLR, &Err); 
	}

	//GP2_FRONT *****************************************************
	GP2Data  = ADC_GetVal (GP2_FRONT);
	TaskDebug_UpdateValueInt(TASKDEBUG_ID_GP2_FRONT, GP2Data);

	if(GP2Data > APP_GP2_LIMIT_FRONT)
	{
		GP2_FRONT_Counter++;
		if(GP2_FRONT_Counter>= GP2_FILTER_THRESHOLD)
			OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_SET, &Err);
	}
	else
	{
		GP2_FRONT_Counter = 0;
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2_FRONT, OS_FLAG_CLR, &Err);
	}
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
		// Rear hoop is down, we use hoop_rear  sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_REAR_HOOP);
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

	// Rear Sensors (Long Detection ) ######################################################
	FlagsToCheck = 0;
	// Hoops is down ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN) == APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN)
	{
		// we do nothing
		FlagsToCheck = 0;
	}
	else
	{
		// Rear hoop is up, we use internal sensor for long detection
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_INTERNAL_REAR_LONG);
	}
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_LONG_REAR, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_LONG_REAR, OS_FLAG_CLR, &Err); 

	// Front Sensors #######################################################################
	FlagsToCheck = 0;
	// All cases ---------------
	FlagsToCheck = (APP_PARAM_APPFLAG_GP2_FRONT);
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_FRONT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_FRONT, OS_FLAG_CLR, &Err); 
	
	// Left Sensors ########################################################################
	FlagsToCheck = 0;
	// Hoops is down ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN) == APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN)
	{
		// Rear hoop is down, we use (rear + left + right) sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_REAR_LEFT_HOOP);
	}
	else
	{
		// Rear hoop is up, we use internal sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_NONE);
	}
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_LEFT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_LEFT, OS_FLAG_CLR, &Err); 

	// Right Sensors ########################################################################
	FlagsToCheck = 0;
	// Hoops is down ---------------
	if((StrategyReadValue & APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN) == APP_PARAM_STRATEGYFLAG_REAR_HOOPS_DOWN)
	{
		// Rear hoop is down, we use (rear + left + right) sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_GP2_REAR_RIGHT_HOOP);
	}
	else
	{
		// Rear hoop is up, we use internal sensor
		FlagsToCheck = (APP_PARAM_APPFLAG_NONE);
	}
		
	// Check Sensors
	if((SystemReadValue & FlagsToCheck) != 0)
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT, OS_FLAG_CLR, &Err); 

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
	ARMS_InitReg();
	HOOPS_SetSpeed();
	ARMS_SetSpeed();

	OSTimeDlyHMSM(0, 0, 2, 0);
	TURBINE_Off();
	HOOPS_Up();
	ARMS_Close();

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

		OSTimeDlyHMSM(0, 0, 1, 0);

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
					case HOOP_LEVEL_DOWN:	HOOP_Back_Down();	break;
					case HOOP_LEVEL_UP:		HOOP_Back_Up();		break;
					default:									break;
					}


					if(CmdType_Blocking == pCurrentMsg->CmdType)
						OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_STATUS, OS_FLAG_SET, &Err);
					NextState = 1;
					break;

				// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				case Sensors_SetArmsStatus: 
					switch(pCurrentMsg->Param1)
					{
					case ARM_OPEN:		ARM_Right_Open();		break;
					case ARM_CLOSED:	ARM_Right_Close();		break;
					case ARM_FRONT:		ARM_Right_Front();		break;
					default:									break;
					}

					switch(pCurrentMsg->Param2)
					{
					case ARM_OPEN:		ARM_Left_Open();		break;
					case ARM_CLOSED:	ARM_Left_Close();		break;
					case ARM_FRONT:		ARM_Left_Front();		break;
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
