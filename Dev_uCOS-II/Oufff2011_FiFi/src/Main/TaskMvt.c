/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskMvt.c
*
* Suivi de version :
* 2011-04-01 | PBE | Creation de la version de base pour la coupe 2010
*********************************************************************************************************
*/

#include "TaskMvt.h"
#include "AppGlobalVars.h"

#define TASK_MVT_FLAGS_TO_READ	(APP_PARAM_APPFLAG_TIMER_STATUS + APP_PARAM_APPFLAG_START_BUTTON + APP_PARAM_APPFLAG_ALL_SENSORS)

// ------------------------------------------------------------------------------------------------
void TaskMvt_SendSetpointToTaskAsser(StructCmd *Setpoint)
{
	INT8U			Err;									// Var to get error status								
	StructPos	    CurrentPos;		    					// Data used for storing current pos from TaskOdo

	if(NULL != Setpoint)
	{
		// Check value
		if((USE_CURRENT_VALUE == Setpoint->Param2) || (USE_CURRENT_VALUE == Setpoint->Param3) || (USE_CURRENT_VALUE == Setpoint->Param4))
		{
			// Read current Odo value (needed for next setpoint)
			if(AppGetCurrentPos(&CurrentPos) != ERR__NO_ERROR)
				return;

			// Update value if necessary (only usable for (x,y,alpha) mvt
			if(USE_CURRENT_VALUE == Setpoint->Param2)
				Setpoint->Param2 = CurrentPos.x;

			if(USE_CURRENT_VALUE == Setpoint->Param3)
				Setpoint->Param3 = CurrentPos.y;

			if(USE_CURRENT_VALUE == Setpoint->Param4)
				Setpoint->Param4 = CurrentPos.angle;
		}

		// Send Data
        // Ask for Mutex
        OSMutexPend(App_MutexCmdToTaskAsser, WAIT_FOREVER, &Err);
	    {	
            // Get current Cmd
		    memcpy(&App_CmdToTaskAsser, &Setpoint, sizeof(StructCmd));
	    }	
	    OSMutexPost(App_MutexCmdToTaskAsser);

        // Update last CmdID used
		App_CmdToTaskAsserId++;
	}


	return;
}

// ------------------------------------------------------------------------------------------------
// TaskMvt_Main()
// ------------------------------------------------------------------------------------------------
void TaskMvt_Main(void *p_arg)
{
	// Vars
	StructCmd	    CurrentPath[APP_MOVING_SEQ_LEN];		// Data used for storing path orders
    StructCmd       CurrentCmd;                             // Data for storing current order from TaskMain (to be done)
    StructCmd       StopCmd;								// Command used for stopping the current mvt
	StructPos	    CurrentPos;		    					// Data used for storing current pos from TaskOdo
	OS_FLAGS		CurrentFlag;							// Var to read current flag								
	INT8U			CurrentState;							// Var used for storing current state for state machine
	INT8U			NextState;								// Var used for storing next state for state machine
	INT8U			Err;									// Var to get error status								
	INT8U			EscapeFlag;								// Flag used to select which side to use during an escape seq								
    INT8S           CurrentSetpoint;                        // Pointer to Current setpoint to reach
    unsigned int    LastMainCmdId;                          // Var to store last command received from TaskMain
	unsigned int	SensorsPreviousStatus;					// Var to store previous sensors status to detect Sensors status modification
	unsigned int	SensorsCurrentStatus;					// Var to store current sensors status

	#ifdef _TARGET_440H
		char Debug_State[4];
	#endif

	// Init
	memset(CurrentPath,       0, APP_MOVING_SEQ_LEN * sizeof(StructCmd));
    memset(&CurrentCmd,       0, 1 * sizeof(StructCmd));
	memset(&CurrentPos,       0, 1 * sizeof(StructPos));

	// Define stop cmd
	StopCmd.Cmd					= Mvt_Stop;
	StopCmd.Param1				= 1;
	StopCmd.Param2				= USE_CURRENT_VALUE;
	StopCmd.Param3				= USE_CURRENT_VALUE;
	StopCmd.Param4				= USE_CURRENT_VALUE;
	StopCmd. ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;

	CurrentFlag				= 0;
	CurrentState			= 0;
	NextState				= 0;
	Err						= 0;
	EscapeFlag				= 0;
    CurrentSetpoint			= -1;
    LastMainCmdId			= 0;
	SensorsCurrentStatus	= 0;
	SensorsPreviousStatus	= 0;
					
	#ifdef _TARGET_440H
		memset(Debug_State, 0, 4*sizeof(char));
	#endif

	putsUART2("OUFFF TEAM 2011 : Mvt online\n");
	

	// MAIN LOOP ==================================================================================
	do
	{
		// Proc Release
		OSTimeDly(10);

		// Update current state
		CurrentState = NextState;

		// Save current sensors status
		SensorsPreviousStatus = SensorsCurrentStatus;

		// Check FLAGS for MvtTask
		CurrentFlag = OSFlagAccept(AppFlags, TASK_MVT_FLAGS_TO_READ, OS_FLAG_WAIT_SET_ANY, &Err);
		
		// Read the current sensors status
		SensorsCurrentStatus = CurrentFlag & APP_PARAM_APPFLAG_ALL_SENSORS;

		#ifdef _TARGET_440H
			sprintf(Debug_State, "%03d", CurrentState);
			Set_Line_Information( 1, 0, Debug_State, 3);
			OSTimeDlyHMSM(0, 0, DELAY_S_BETWEEN_NEXT_STATE, DELAY_MS_BETWEEN_NEXT_STATE);
		#endif

		// State machine
		switch(CurrentState)
		{
			// CASE 000 ---------------------------------------------------------------------------
			case 0:		// Init state
				// Check for 'start button' status
				if((CurrentFlag & APP_PARAM_APPFLAG_START_BUTTON) != 0)
				{
					// Start button has been pressed
					NextState = 1;
				}
				else
				{
					// Start button is still inactive
					NextState = 0;
									
					// Check if initial position has been changed
                    // Ask for Mutex
                    OSMutexPend(App_MutexCmdToTaskMvt, WAIT_FOREVER, &Err);
	                {	
                        // Get current Cmd
		                if(App_SetNewPos == App_CmdToTaskMvt.Cmd)
						{
							TaskMvt_SendSetpointToTaskAsser(&App_CmdToTaskMvt);

							// Clear this msg
							memset(&App_CmdToTaskMvt, 0, sizeof(StructCmd) * 1);
						}
	                }	
	                OSMutexPost(App_MutexCmdToTaskMvt);


                    // Place here code for executing Cmd (if necessary)
				}
				break;

			// CASE 001 ---------------------------------------------------------------------------
			case 1:		// Read Timer flag
				if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == APP_PARAM_APPFLAG_TIMER_STATUS)
					NextState = 255;		// Time is up
				else
					NextState = 2;			// Time is running

				break;

			// CASE 002 ---------------------------------------------------------------------------
			case 2:		// Read Msg from Main
				// Check Last CmdID used, if a new msg is ready, use it
				if(App_CmdToTaskMvtId > LastMainCmdId)										
				{	
                    // Ask for Mutex
                    OSMutexPend(App_MutexCmdToTaskMvt, WAIT_FOREVER, &Err);
	                {	
                        // Get current Cmd
		                memcpy(&CurrentCmd, &App_CmdToTaskMvt, sizeof(StructCmd));
	                }	
	                OSMutexPost(App_MutexCmdToTaskMvt);

                    // Update last CmdID used
                    LastMainCmdId = App_CmdToTaskMvtId;

                    // Analyse Cmd
                    switch(CurrentCmd.Cmd)
                    {
                    case Mvt_Stop:
                        NextState = 254;
                        break;

                    case Mvt_UseAngleOnly:
                    case Mvt_Simple:
                    case Mvt_UseDistOnly:
                    case Mvt_UseMixedMode:
                    case Mvt_UsePivotMode:
                        NextState = 253;
                        break;

                    default:
                        // Invalid Command
                        NextState = 3;
                        break;
                    }
				}
				else
				{	// There is no msg available
					NextState = 3;
				}

				break;

			// CASE 003 ---------------------------------------------------------------------------
			case 3:		// Read Bumpers Status
				if(SensorsCurrentStatus == SensorsPreviousStatus)
				{	// There is no change
					NextState = 4;
				}
				else
				{	// One sensor has been activated
					// Which sensors are active
					if((CurrentFlag & APP_PARAM_APPFLAG_FRONT_SENSORS) == 0)
					{	// Front sensors are activated
						NextState = 5;
					}
					else if((CurrentFlag & APP_PARAM_APPFLAG_LEFT_SENSORS) == 0)
					{	// Left sensors are activated
						NextState = 7;
					}
					else if((CurrentFlag & APP_PARAM_APPFLAG_RIGHT_SENSORS) == 0)
					{	// Right sensors are activated
						NextState = 8;
					}
					else if((CurrentFlag & APP_PARAM_APPFLAG_BACK_SENSORS) == 0)
					{	// Back sensors are activated
						NextState = 6;
					}
					else
					{	// There is no sensor activated
						NextState = 4;
					}
				}
				break;

			// CASE 004 ---------------------------------------------------------------------------
			case 4:		// Read Mvt Flag
				// Read Current Pos
				if(AppGetCurrentPos(&CurrentPos) == ERR__NO_ERROR)
                {   // Check CurrentState Value
                    if(CurrentPos.CurrentState == CURRENT_STATE__STOP)
					{
						EscapeFlag = 0;			// Clear escape flag
                        NextState = 9;
					}
					else
                        NextState = 0;
                }
                else
                {   // We are unable to read current pos
                    NextState = 0;
                }
				break;

			// CASE 005 ---------------------------------------------------------------------------
			case 5:		// Escape Seq (Front)
				// Ask for stopping Mvt
				TaskMvt_SendSetpointToTaskAsser(&StopCmd);

				if(EscapeFlag%2 == 0)
					LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_RIGHT, APP_ESCAPE_ROBOT_SPEED, CurrentPath, &CurrentSetpoint);
				else
					LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_LEFT, APP_ESCAPE_ROBOT_SPEED, CurrentPath, &CurrentSetpoint);

				EscapeFlag++;
				break;

			// CASE 006 ---------------------------------------------------------------------------
			case 6:		// Escape Seq (Back)
				// Ask for stopping Mvt
				TaskMvt_SendSetpointToTaskAsser(&StopCmd);
				LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_FRONT, APP_ESCAPE_ROBOT_SPEED, CurrentPath, &CurrentSetpoint);
				break;

			// CASE 007 ---------------------------------------------------------------------------
			case 7:		// Escape Seq (Right)
				// Ask for stopping Mvt
				NextState = 254;
				break;

			// CASE 008 ---------------------------------------------------------------------------
			case 8:		// Escape Seq (Left)
				// Ask for stopping Mvt
				NextState = 254;
				break;

			// CASE 009 ---------------------------------------------------------------------------
			case 9:		// Is temporary setpoint reached ?
                // Check if we have a setpoint to reach
                if((CurrentSetpoint >= 0) && (LibMoving_IsSetpointReached(CurrentPath + CurrentSetpoint) == OS_TRUE))
                {   
                    // Setpoint has been reached
                    NextState = 10;
                }
                else
                {
                    NextState = 0;
                }
 				break;

			// CASE 010 ---------------------------------------------------------------------------
			case 10:	// Is final setpoint reached ?
                // Check if we have a setpoint to reach
                if(LibMoving_IsSetpointReached(&CurrentCmd) == OS_TRUE)
                {
                    // Setpoint has been reached
                    NextState = 254;
                }
                else
                {   // Search for next setpoint
                    NextState = 11;
                }
				break;

			// CASE 011 ---------------------------------------------------------------------------
			case 11:	// Does next setpoint exist ?
				if(CurrentSetpoint > 0)
                {   // Load next Setpoint
                    NextState = 12;
                }
                else
                {   // There is no other setpoint in memory, We have to compute a new path
                    NextState = 253;
                }
				break;

			// CASE 012 ---------------------------------------------------------------------------
			case 12:	// Use next setpoint 
                CurrentSetpoint--;

				if(CurrentSetpoint < 0)
				{
					// There is no more setpoint in memory
					NextState = 0;
				}
				else
				{
					// Send new command to TaskAsser
					TaskMvt_SendSetpointToTaskAsser(CurrentPath + CurrentSetpoint);
				}
				break;

			// CASE 253 ---------------------------------------------------------------------------
			case 253:	// Compute new traj
				// First step, clear all current orders
				memset(CurrentPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructCmd));

				// Compute New traj
				LibMoving_ComputeNewPath(&CurrentCmd, CurrentPath, &CurrentSetpoint);

				// Check if a path has been found ?
				if(CurrentSetpoint > 0)
				{
					// A path has been found, Send new order 
					NextState = 12;

					// Indicates we are moving
					OSFlagPost(AppFlags, APP_PARAM_APPFLAG_MVT_STATE, OS_FLAG_CLR, &Err); 

				}
				else
				{
					// There is no possible path, we do nothing
					NextState = 254;	// STOP action
				}
				break;

			// CASE 254 ---------------------------------------------------------------------------
			case 254:	// Ask for stopping mvt
				// Disable all current path
				CurrentSetpoint = -1;
				memset(CurrentPath, 0,	APP_MOVING_SEQ_LEN * sizeof(StructCmd));
				memcpy(&CurrentCmd,	&StopCmd,	1 * sizeof(StructCmd));

				TaskMvt_SendSetpointToTaskAsser(&StopCmd);

				// Indicates we are stopped
				OSFlagPost(AppFlags, APP_PARAM_APPFLAG_MVT_STATE, OS_FLAG_SET, &Err); 

				NextState = 0;
				break;

			// CASE 255 ---------------------------------------------------------------------------
			case 255:	// End
				// Disable all current path
				CurrentSetpoint = -1;
				memset(CurrentPath, 0,	APP_MOVING_SEQ_LEN * sizeof(StructCmd));
				memset(&CurrentCmd,	0,	1 * sizeof(StructCmd));

				TaskMvt_SendSetpointToTaskAsser(&StopCmd);

				break;

			// DEFAULT ----------------------------------------------------------------------------
			default: // Undefined state
				// Current state is undefined. Clear current path and ask for stopping mvt
				memset(CurrentPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructCmd));
				NextState = 254;		// Ask for Stopping action
				break;
		}
	
	// We loop until timer is set
	}while(CurrentState != 255);
	// ===============================================================================================

	#ifdef _TARGET_440H
		Set_Line_Information( 1, 0, "XXX", 3);
	#endif

	// Time is up : Wait for ever
	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}
