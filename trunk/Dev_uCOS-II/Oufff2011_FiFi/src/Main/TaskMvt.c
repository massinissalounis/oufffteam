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
// TaskMvt_Main()
// ------------------------------------------------------------------------------------------------
void TaskMvt_Main(void *p_arg)
{
	// Vars
	StructMvtPos	CurrentPath[APP_MOVING_SEQ_LEN];		// Data used for storing setpoints
	StructOdoPos	CurrentOdoPos;							// Data used for storing current pos from TaskOdo
	StructMsg		*pReadMsg;								// Pointer for retreiving msg from QMvt queue				
	OS_FLAGS		CurrentFlag;							// Var to read current flag								
	INT8U			CurrentState;							// Var used for storing current state for state machine
	INT8U			NextState;								// Var used for storing next state for state machine
	INT8U			Err;									// Var to get error status								

	#ifdef _TARGET_440H
		char Debug_State[4];
	#endif

	// Init
	memset(CurrentPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructMvtPos));
	memset(&CurrentOdoPos, 0, 1 * sizeof(StructOdoPos));
	pReadMsg			= NULL;
	CurrentFlag			= 0;
	CurrentState		= 0;
	NextState			= 0;
	Err					= 0;
					
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

		// Check FLAGS for MvtTask
		CurrentFlag = OSFlagAccept(AppFlags, TASK_MVT_FLAGS_TO_READ, OS_FLAG_WAIT_SET_ANY, &Err);


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
				
					// Read Msg from QMvt queue
					pReadMsg = (StructMsg*)OSQAccept(AppQueueMvt, &Err);

					if(NULL != pReadMsg)										
					{	// A message is available
						if(Msg_Mvt_SetCurrentPos == pReadMsg->MsgType)
						{
							// In Init state, we use only 'Msg_Mvt_SetCurrentPos' msg, all other msg are ignored 
							// Todo
						}

						// Delete msg
						pReadMsg->IsRead = OS_TRUE;
						pReadMsg = NULL;
					}
				}
				break;

			// CASE 001 ---------------------------------------------------------------------------
			case 1:		// Read Timer flag
				if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0)
					NextState = 255;		// Time is up
				else
					NextState = 2;			// Time is running

				break;

			// CASE 002 ---------------------------------------------------------------------------
			case 2:		// Read Msg from QMvt Queue
				pReadMsg = (StructMsg*)OSQAccept(AppQueueMvt, &Err);

				if(NULL != pReadMsg)										
				{	// A message is available
				}
				else
				{	// There is no msg available
					NextState = 3;
				}

				break;

			// CASE 003 ---------------------------------------------------------------------------
			case 3:		// Read Bumpers Status
				if((CurrentFlag & APP_PARAM_APPFLAG_ALL_SENSORS) == 0)
				{	// All bumpers are inative
					NextState = 4;
				}
				else
				{	// There is one or more sensors active
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
					{	// There is no expected sensors activated
						NextState = 4;
					}
				}
				break;

			// CASE 004 ---------------------------------------------------------------------------
			case 4:		// Read Mvt Flag
				// Read Current Pos
				if(AppGetCurrentOdoPos(&CurrentOdoPos) == ERR__NO_ERROR)
                {   // Check CurrentState Value
                    if(CurrentOdoPos.CurrentState == CURRENT_STATE__STOP)
                        NextState = 9;
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
				NextState = 254;
				break;

			// CASE 006 ---------------------------------------------------------------------------
			case 6:		// Escape Seq (Back)
				// Ask for stopping Mvt
				NextState = 254;
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
				// Todo
				NextState = 0;
				break;

			// CASE 010 ---------------------------------------------------------------------------
			case 10:	// Is final setpoint reached ?
				// Todo
				NextState = 0;
				break;

			// CASE 011 ---------------------------------------------------------------------------
			case 11:	// Does next setpoint exist ?
				// Todo
				NextState = 0;
				break;

			// CASE 012 ---------------------------------------------------------------------------
			case 12:	// Use next setpoint 
				// Todo
				NextState = 0;
				break;

			// CASE 253 ---------------------------------------------------------------------------
			case 253:	// Compute new traj
				// Todo
				NextState = 0;
				break;

			// CASE 254 ---------------------------------------------------------------------------
			case 254:	// Ask for stopping mvt
				// Todo
				NextState = 0;
				break;

			// CASE 255 ---------------------------------------------------------------------------
			case 255:	// End
				// Todo
				// Ask for stopping action if Mvt Moving Flag is set
				break;

			// DEFAULT ----------------------------------------------------------------------------
			default: // Undefined state
				// Current state is undefined. Clear current path and ask for stopping mvt
				memset(CurrentPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructMvtPos));
				NextState = 254;		// Ask for Stopping action
				break;
		}
	
	// We loop until timer is set
	}while(CurrentState != 255);
	// ===============================================================================================

	// Time is up : Wait for ever
	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}
