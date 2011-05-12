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
#include "AppGlobalVars.h"

#define TASK_MAIN_FLAGS_TO_READ	(APP_PARAM_APPFLAG_TIMER_STATUS + APP_PARAM_APPFLAG_START_BUTTON + APP_PARAM_APPFLAG_ALL_SENSORS)

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

	// Debug vars
	char 		uart_buffer[13];
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

	#ifdef _TARGET_440H
		memset(Debug_State, 0, 4*sizeof(char));
	#endif

	putsUART2("OUFFF TEAM 2011 : Main online\n");

	// Wait other tasks start
	OSTimeDlyHMSM(0, 0, 1, 0);

#ifdef _TARGET_440H
	OSTimeDlyHMSM(0, 0, 2, 0);
	Set_Line_Information( 1, 0, "                 ", 16);
	Set_Line_Information( 2, 0, "                 ", 16);
#else
	// Wait for color
	while(c_NotSet == AppCurrentColor)
		OSTimeDly(1);
#endif

	// Wait for start signal
	putsUART2("TaskMain : Wait for start signal\n");
	do
	{
		if(AppCurrentColor != LastColorRead)
		{
			LastColorRead = AppCurrentColor;
			// Get CurrentPos for current color
			if(AppCurrentColor == c_ColorA)
			{
				// Todo : Define new position from color
				putsUART2("TaskMain : Color = Blue\n");
				#ifdef _TARGET_440H
					Set_Line_Information( 1, 15, "B", 1);
				#endif
			}
			else
			{
				// Todo : Define new position from color
				putsUART2("TaskMain : Color = Red\n");
				#ifdef _TARGET_440H
					Set_Line_Information( 1, 15, "R", 1);
				#endif
			}

			// Todo : Send new position to TaskMvt
		}

		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ANY, &Err);
	}while((CurrentFlag & APP_PARAM_APPFLAG_START_BUTTON) != APP_PARAM_APPFLAG_START_BUTTON);

	putsUART2("TaskMain : Go !! Go !! Go !!\n");
	
	// MAIN LOOP ==================================================================================
	do
	{
		// Proc Release
		OSTimeDly(10);

		// Update current state
		CurrentState = NextState;

		// Check FLAGS for Task Main
		CurrentFlag = OSFlagAccept(AppFlags, TASK_MAIN_FLAGS_TO_READ, OS_FLAG_WAIT_SET_ALL, &Err);
		
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
				NextState = 1;
				break;

			// CASE 003 ---------------------------------------------------------------------------
			case 3:		// Check Current action status
				// Todo
				break;

			// CASE 004 ---------------------------------------------------------------------------
			case 4:		// Get Next Action
				// Todo
				break;

			// CASE 005 ---------------------------------------------------------------------------
			case 5:		// Send Next Action
				// Todo
				break;

			// CASE 006 ---------------------------------------------------------------------------
			case 6:		// Check Current action type (blocking or none blocking)
				// Todo
				break;

			// CASE 254 ---------------------------------------------------------------------------
			case 254:	// Action to be done if beacon is activated
				// Todo
				break;

			// CASE 255 ---------------------------------------------------------------------------
			case 255:	// Final state
				// Todo
				break;
							
			// DEFAULT ----------------------------------------------------------------------------
			default:	// Undefined state
				// Todo
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

