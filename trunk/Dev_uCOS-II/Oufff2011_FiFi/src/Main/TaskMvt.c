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

#define TASK_MVT_FLAGS_TO_READ	(APP_PARAM_APPFLAG_TIMER_STATUS + APP_PARAM_APPFLAG_START_BUTTON)

// ------------------------------------------------------------------------------------------------
// TaskMvt_Main()
// ------------------------------------------------------------------------------------------------
void TaskMvt_Main(void *p_arg)
{
	// Vars
	StructMvtPos	CurrentPath[APP_MOVING_SEQ_LEN];		// Data used for storing setpoints
	StructMsg		*pReadMsg;								// Pointer for retreiving msg from QMvt queue				
	OS_FLAGS		CurrentFlag;							// Var to read current flag								
	INT8U			CurrentState;							// Var used for storing current state for state machine
	INT8U			NextState;								// Var used for storing next state for state machine
	INT8U			Err;									// Var to get error status								

	// Init
	memset(CurrentPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructMvtPos));
	pReadMsg			= NULL;
	CurrentFlag			= 0;
	CurrentState		= 0;
	NextState			= 0;
	Err					= 0;


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

		// State machine
		switch(CurrentState)
		{
			// CASE 000 ---------------------------------------------------------------------------
			case 0:	// Init state
				LED_Off(0);

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
			case 1:	// Read Timer flag
				LED_Off(0);
				LED_On(1);
				
				if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0)
				{
					// Time is up
					NextState = 255;
				}
				else
				{
					// Todo
				}

				break;

			// CASE 255 ---------------------------------------------------------------------------
			case 255:	// End
				// Todo
				// Ask for stopping action is Flag Moving is set (case 254)

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
