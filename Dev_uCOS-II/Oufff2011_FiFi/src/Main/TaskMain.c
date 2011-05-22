/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskMain.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************


*/

#include "TaskMain.h"
#include "Strategy.h"
#include "AppGlobalVars.h"

#define TASK_MAIN_FLAGS_TO_READ	(APP_PARAM_APPFLAG_TIMER_STATUS + APP_PARAM_APPFLAG_START_BUTTON + APP_PARAM_APPFLAG_ALL_SENSORS + APP_PARAM_APPFLAG_ACTION_STATUS)

// ------------------------------------------------------------------------------------------------
void TaskMain_SendSetpointToTaskMvt(StructCmd *NextCmd)
{
	INT8U			Err;									// Var to get error status								

	if(NULL != NextCmd)
	{
		// Send Data
        // Ask for Mutex
        OSMutexPend(App_MutexCmdToTaskMvt, WAIT_FOREVER, &Err);
	    {	
            // Send Cmd
		    memcpy(&App_CmdToTaskMvt, NextCmd, sizeof(StructCmd));
	    }	
	    OSMutexPost(App_MutexCmdToTaskMvt);

        // Update last CmdID used
		App_CmdToTaskMvtId++;
	}

	return;
}

// ------------------------------------------------------------------------------------------------
// TaskMain_Main()
// ------------------------------------------------------------------------------------------------
void TaskMain_Main(void *p_arg)
{
	EnumColor	LastColorRead;						// Used to check color modification
	OS_FLAGS	CurrentFlag;						// Var to read current flag								
	INT8U		CurrentState;						// Var used for storing current state for state machine
	INT8U		NextState;							// Var used for storing next state for state machine
	INT8U		Err;								// Var to get error status								
	StructCmd	CurrentCmd;							// Var to store current action to be done
	StructCmd	NextCmd;							// Var to store next action to be done

	// Debug vars
	char 		uart_buffer[20];
	char 		*buffer_ptr;
	#ifdef _TARGET_440H
		char Debug_State[4];
	#endif

	// Init
	LastColorRead			= c_NotSet;
	CurrentFlag				= 0;
	CurrentState			= 0;
	NextState				= 0;
	Err						= 0;

	memset(uart_buffer, 0, 20);

	#ifdef _TARGET_440H
		memset(Debug_State, 0, 4*sizeof(char));
	#endif

	AppDebugMsg("OUFFF TEAM 2011 : Main online\n");

	// Wait other tasks start
	OSTimeDlyHMSM(0, 0, 1, 0);

#ifdef _TARGET_440H
	OSTimeDlyHMSM(0, 0, 1, 0);
	Set_Line_Information( 1, 0, "                 ", 16);
	Set_Line_Information( 2, 0, "                 ", 16);
#else
	// Wait for color
	while(c_NotSet == AppCurrentColor)
		OSTimeDly(1);
#endif

	// Wait for start signal
	AppDebugMsg("TaskMain : Wait for start signal\n");
	do
	{
		// Proc Release
		OSTimeDlyHMSM(0, 0, 0, 10);

		if(AppCurrentColor != LastColorRead)
		{
			LastColorRead = AppCurrentColor;
			// Get CurrentPos for current color
			if(AppCurrentColor == c_ColorA)
			{
				AppDebugMsg("TaskMain : Color = Blue\n");
				#ifdef _TARGET_440H
					Set_Line_Information( 1, 15, "B", 1);
				#endif
			}
			else
			{
				AppDebugMsg("TaskMain : Color = Red\n");
				#ifdef _TARGET_440H
					Set_Line_Information( 1, 15, "R", 1);
				#endif
			}
			
			if(ERR__NO_ERROR == Strategy_GetInitCmd(LastColorRead, &NextCmd))
			{
				TaskMain_SendSetpointToTaskMvt(&NextCmd);
			}
		}

		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ANY, &Err);
	}while((CurrentFlag & APP_PARAM_APPFLAG_START_BUTTON) != APP_PARAM_APPFLAG_START_BUTTON);

	AppDebugMsg("TaskMain : Go !! Go !! Go !!\n");
	
	// MAIN LOOP ==================================================================================
	do
	{
		// Proc Release
		OSTimeDlyHMSM(0, 0, 0, 10);

		// Update current state
		CurrentState = NextState;

		// Check FLAGS for Task Main
		CurrentFlag = OSFlagAccept(AppFlags, TASK_MAIN_FLAGS_TO_READ, OS_FLAG_WAIT_SET_ANY, &Err);

		#ifdef _TARGET_440H
			sprintf(Debug_State, "%03d", CurrentState);
			Set_Line_Information( 2, 0, Debug_State, 3);
			OSTimeDlyHMSM(0, 0, DELAY_S_BETWEEN_NEXT_STATE, DELAY_MS_BETWEEN_NEXT_STATE);
		#endif

		// State machine
		switch(CurrentState)
		{
			// CASE 000 ---------------------------------------------------------------------------
			case 0:		// Init state
				NextState = 1;
				break;

			// CASE 001 ---------------------------------------------------------------------------
			case 1:		// Check Timer
				if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == APP_PARAM_APPFLAG_TIMER_STATUS)
					NextState = 255;		// Time is up
				else
					NextState = 2;			// Time is running

				break;

			// CASE 002 ---------------------------------------------------------------------------
			case 2:		// Check Beacons
				// Todo
				NextState = 3;
				break;

			// CASE 003 ---------------------------------------------------------------------------
			case 3:		// Check Current action status
				if((CurrentFlag & APP_PARAM_APPFLAG_ACTION_STATUS) == APP_PARAM_APPFLAG_ACTION_STATUS)
				{
					// Flag is set, action is finished
					NextState = 4;
					// Todo : verifier si l'action s'est finie comme attendue
				}
				else
				{
					// Action is running
					NextState = 6;
				}
				break;

			// CASE 004 ---------------------------------------------------------------------------
			case 4:		// Get Next Action
				if(ERR__NO_ERROR == Strategy_GetNextAction(AppCurrentColor, &NextCmd))
				{
					NextState = 5;
				}
				else
				{
					NextState = 1;
				}
				break;

			// CASE 005 ---------------------------------------------------------------------------
			case 5:		// Send Next Action
				if(CmdType_NotSet != NextCmd.CmdType)
				{
					CurrentCmd = NextCmd;
					memset(&NextCmd, 0, sizeof(StructCmd));

					TaskMain_SendSetpointToTaskMvt(&CurrentCmd);
				}

				NextState = 1;
				break;

			// CASE 006 ---------------------------------------------------------------------------
			case 6:		// Check Current action type (blocking or none blocking)
				switch(CurrentCmd.CmdType)
				{
				case CmdType_Blocking:
					NextState = 1;
					break;

				case CmdType_NonBlocking:
					NextState = 4;
					break;

				default:
					NextState = 1;
					break;
				}
				break;

			// CASE 254 ---------------------------------------------------------------------------
			case 254:	// Action to be done if beacon is activated
				NextCmd.ActiveSensorsFlag = APP_PARAM_APPFLAG_NONE;
				NextCmd.Cmd			= Mvt_Stop;
				NextCmd.CmdType		= CmdType_Blocking;

				NextState = 5;
				break;

			// CASE 255 ---------------------------------------------------------------------------
			case 255:	// Final state
				NextState = 255;
				break;
							
			// DEFAULT ----------------------------------------------------------------------------
			default:	// Undefined state
				NextState = 1;
				break;
		}

	// We loop until timer is set
	}while(CurrentState != 255);
	// ===============================================================================================

	#ifdef _TARGET_440H
		Set_Line_Information( 2, 0, "XXX", 3);
	#endif

	// Time is up : Wait for ever
	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}

