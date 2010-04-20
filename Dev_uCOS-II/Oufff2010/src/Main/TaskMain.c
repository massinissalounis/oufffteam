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
*********************************************************************************************************


*/

#include "TaskMain.h"
#include "AppGlobalVars.h"

// ------------------------------------------------------------------------------------------------
// TaskMain_Main()
// ------------------------------------------------------------------------------------------------
void TaskMain_Main(void *p_arg)
{
	INT8U		Err = 0;				/* Var to get error status								*/
	OS_FLAGS	CurrentFlag = 0;		/* Var to read current flag								*/

	TaskMain_Init();

	// Wait for start signal
	OSFlagPend(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ALL, WAIT_FOREVER, &Err);

	do
	{
		LED_Toggle(1);
		OSTimeDly(10);

		// Read Current position
		TaskMain_GetCurrentPos();

		// Check for collisions
		TaskMain_CheckForBumpers();

		// Check FLAGS for timer status
		CurrentFlag = OSFlagPend(AppFlags, APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_WAIT_SET_ALL, 1, &Err);
	
	// We loop until timer is set
	}while((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0);

	// Time is up :
	#ifdef _TARGET_STARTER_KIT
		LED_Off(1);
		//SoftReset();
	#endif


	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_Init()
{
	memset(&TaskMain_CurrentPos, 0, sizeof(StructPos));				/* Set local CurrentPos to 0						*/

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_CheckForBumpers()
{
	INT8U		Err;
	OS_FLAGS	CurrentBumpersFlag;
		
	// Check for current flag
	CurrentBumpersFlag = OSFlagPend(AppFlags, APP_PARAM_APPFLAG_ALL_BUMPERS, OS_FLAG_WAIT_SET_ANY, 1, &Err);

	if(0 != CurrentBumpersFlag)	
	{
		// Otherwise, we have to check, where we have bumped and how to escape
		// Bumper 0
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER0) == APP_PARAM_APPFLAG_BUMPER0)	
		{
			// TODO : Action à réaliser
		}
		
		// Bumper 1
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER1) == APP_PARAM_APPFLAG_BUMPER1)	
		{
			// TODO : Action à réaliser
		}
		
		// Bumper 2
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER2) == APP_PARAM_APPFLAG_BUMPER2)	
		{
			// TODO : Action à réaliser
		}
		
		// Bumper 3
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER3) == APP_PARAM_APPFLAG_BUMPER3)	
		{
			// TODO : Action à réaliser
		}
		
			// Bumper 4
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER4) == APP_PARAM_APPFLAG_BUMPER4)	
		{
			// TODO : Action à réaliser
		}
		
		// Bumper 5
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER5) == APP_PARAM_APPFLAG_BUMPER5)	
		{
			// TODO : Action à réaliser
		}
		
		// Bumper 6
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER6) == APP_PARAM_APPFLAG_BUMPER6)	
		{
			// TODO : Action à réaliser
		}
		
		// Bumper 7
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER7) == APP_PARAM_APPFLAG_BUMPER7)	
		{
			// TODO : Action à réaliser
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetCurrentPos()
{
	INT8U Err;

	// Ask for Mutex on position
	OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);
	
	// Copy current pos
	memcpy(&TaskMain_CurrentPos, &AppCurrentPos, sizeof(StructPos));
	
	// Release Mutex
	OSMutexPost(Mut_AppCurrentPos);

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_StopMvt()
{
	int i;

	// flush current queue
	OSQFlush(AppQueueAsserEvent);

	// Create msg (an high priority msg) for stopping mvt
	TaskMain_GetCurrentPos();		// Read current Pos

	AppHighPrioMsg.IsRead = OS_FALSE;
	AppHighPrioMsg.Msg = Msg_Asser_GoToXYA;
	AppHighPrioMsg.Param1 = TaskMain_CurrentPos.x;		// X
	AppHighPrioMsg.Param2 = TaskMain_CurrentPos.y;		// Y
	AppHighPrioMsg.Param3 = TaskMain_CurrentPos.angle;	// ALPHA

	// Send STOP msg
	OSQPostFront(AppQueueAsserEvent, (void*)(&AppHighPrioMsg));

	// Set all pending msg for AsserTask status to READ
	for(i=0; i<(APP_QUEUE_ASSER_SIZE + APP_QUEUE_MAIN_SIZE); i++)
	{
		if(		((AppMsgStk[i].Msg - Msg_Asser_MsgType) > 0 ) 
			&&	((AppMsgStk[i].Msg - Msg_Asser_MsgType) < 100))
		{
			memset(&(AppMsgStk[i]), 0, sizeof(StructMsg));
			AppMsgStk[i].IsRead = OS_FALSE;
		}
	}

	return;
}
