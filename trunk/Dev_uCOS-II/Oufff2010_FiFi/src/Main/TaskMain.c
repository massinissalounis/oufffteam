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
void TaskMain_GetNextAction()
{
	int i;

	if (	(TaskMain_NextSetpointPos.x == TaskMain_ExpectedPos.x)
		&&	(TaskMain_NextSetpointPos.y == TaskMain_ExpectedPos.y)
		&&	(TaskMain_NextSetpointPos.angle == TaskMain_ExpectedPos.angle))
	{
		// Expected point has been reach, moving sequence must be delete
		TaskMain_MovingSeqRemainingSteps = 0;
		memset(TaskMain_MovingSeq, 0, APP_MOVING_SEQ_LEN * sizeof(StructPos));
		
		// we ask for a new point
		switch(AppCurrentColor)
		{
			case c_Blue:
				TaskMain_GetNextActionForColorA();
				break;

			case c_Red:
				TaskMain_GetNextActionForColorB();
				break;

			default:
				break;
		}
	}
	else
	{
		// Check if there are remaining steps to be done 
		if((TaskMain_MovingSeqRemainingSteps > 0) && (TaskMain_MovingSeqRemainingSteps <= APP_MOVING_SEQ_LEN))
		{
			// We have a moving sequence activated, we use it
			memcpy(	&TaskMain_NextSetpointPos, 
					TaskMain_MovingSeq + APP_MOVING_SEQ_LEN - TaskMain_MovingSeqRemainingSteps, 
					sizeof(StructPos));
		}
		else
		{
			// There is not a moving seq, and expected point has not been reached
			// We have to compute a new moving sequence

		}
	}
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextActionForColorA()
{
	static CurrentActionForColorA = 0;
	StructPos *ptr = &TaskMain_NextSetpointPos;

	// Search for position
	switch(CurrentActionForColorA)
	{
		// Initial position -----------------------------------------------------------------------
		case 0:		ptr->x = 0000.0;	ptr->y = 0000.0;	ptr->angle	= 0000.0;	break;

		// Loop -----------------------------------------------------------------------------------
		case 1:		ptr->x = 0000.0;	ptr->y = 0000.0;	ptr->angle	= 0000.0;	break;
		case 2:		ptr->x = 0010.0;	ptr->y = 0010.0;	ptr->angle	= 0000.0;	break;
		case 3:		break;		//	Make something	
		case 4:		ptr->x = 0010.0;	ptr->y = 0010.0;	ptr->angle	= 0045.0;	break;
		case 5:		ptr->x = 0010.0;	ptr->y = 0010.0;	ptr->angle	= 0045.0;	break;

		// Default --------------------------------------------------------------------------------
		default:
			CurrentActionForColorA = 1;
			TaskMain_GetNextActionForColorA();
			break;
	}

	CurrentActionForColorA++;
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextActionForColorB()
{
	static CurrentActionForColorB = 0;
	StructPos *ptr = &TaskMain_NextSetpointPos;

	switch(CurrentActionForColorB)
	{
		// Initial position -----------------------------------------------------------------------
		case 0:		ptr->x = 0000.0;	ptr->y = 0000.0;	ptr->angle	= 0000.0;	break;

		// Loop -----------------------------------------------------------------------------------
		case 1:		ptr->x = 0000.0;	ptr->y = 0000.0;	ptr->angle	= 0000.0;	break;
		case 2:		ptr->x = 0010.0;	ptr->y = 0010.0;	ptr->angle	= 0000.0;	break;
		case 3:		ptr->x = 0010.0;	ptr->y = 0010.0;	ptr->angle	= 0045.0;	break;
		case 4:		ptr->x = 0010.0;	ptr->y = 0010.0;	ptr->angle	= 0000.0;	break;

		// Default --------------------------------------------------------------------------------
		default:
			CurrentActionForColorB = 1;
			TaskMain_GetNextActionForColorB();
			break;
	}
	CurrentActionForColorB++;
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_Init()
{
	memset(&TaskMain_CurrentPos, 0, sizeof(StructPos));				// Set local CurrentPos to 0						
	memset(&TaskMain_ExpectedPos, 0, sizeof(StructPos));			// Set local ExpectedPos to 0						
	memset(&TaskMain_NextSetpointPos, 0, sizeof(StructPos));		// Set local NextSetpointPos to 0						

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
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
		// Bumper 1
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER1) == APP_PARAM_APPFLAG_BUMPER1)	
		{
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
		// Bumper 2
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER2) == APP_PARAM_APPFLAG_BUMPER2)	
		{
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
		// Bumper 3
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER3) == APP_PARAM_APPFLAG_BUMPER3)	
		{
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
			// Bumper 4
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER4) == APP_PARAM_APPFLAG_BUMPER4)	
		{
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
		// Bumper 5
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER5) == APP_PARAM_APPFLAG_BUMPER5)	
		{
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
		// Bumper 6
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER6) == APP_PARAM_APPFLAG_BUMPER6)	
		{
			TaskMain_StopMvt();	
			// TODO : Action à réaliser
		}
		
		// Bumper 7
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER7) == APP_PARAM_APPFLAG_BUMPER7)	
		{
			TaskMain_StopMvt();	
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
	for(i=0; i<(APP_QUEUES_TOTAL_SIZE); i++)
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

// ------------------------------------------------------------------------------------------------
BOOLEAN TaskMain_IsSetpointReached()
{
	// Check for x and y
	if(		(TaskMain_CurrentPos.x >= (TaskMain_NextSetpointPos.x - APP_PARAM_ERR_ON_POS)) 
		&&	(TaskMain_CurrentPos.y >= (TaskMain_NextSetpointPos.y - APP_PARAM_ERR_ON_POS))
		&&	(TaskMain_CurrentPos.x <= (TaskMain_NextSetpointPos.x + APP_PARAM_ERR_ON_POS))
		&&	(TaskMain_CurrentPos.y <= (TaskMain_NextSetpointPos.y + APP_PARAM_ERR_ON_POS)))
	{
		// Check for angle
		if(		(TaskMain_CurrentPos.angle >= (TaskMain_NextSetpointPos.angle - APP_PARAM_ERR_ON_ANGLE)) 
			&&	(TaskMain_CurrentPos.angle <= (TaskMain_NextSetpointPos.angle + APP_PARAM_ERR_ON_ANGLE)))
		{
			return OS_TRUE;
		}
	}

	return OS_FALSE;
}

// ------------------------------------------------------------------------------------------------
// TaskMain_Main()
// ------------------------------------------------------------------------------------------------
void TaskMain_Main(void *p_arg)
{
	INT8U		Err = 0;				// Var to get error status								
	OS_FLAGS	CurrentFlag = 0;		// Var to read current flag								
	StructMsg	MsgToPost;				// Var to post msg to other tasks						

	TaskMain_Init();

	// Indicate which moving algo we're going to use
	// Create this msg
	MsgToPost.Msg		= Msg_Asser_Algo;
	MsgToPost.Param1	= APP_MOVING_ASSER_IN_POS_ENABLED;
	MsgToPost.Param2	= APP_MOVING_ASSER_IN_ANGLE_ENABLED;
	MsgToPost.Param3	= APP_MOVING_ASSER_IN_SPEED_ENABLED;
	// Post msg to activate moving algo
	AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

	// Get CurrentPos for current color
	TaskMain_GetNextAction();
	
	// Define Current position to OdoTask and AsserTask
	OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);		// SECTION CRITIQUE
	{
		memset(&MsgToPost, 0, sizeof(StructMsg));

		// Create msg for asser task for setting start pos
		MsgToPost.Msg		= Msg_Asser_GoToXYA;
		MsgToPost.Param1	= TaskMain_NextSetpointPos.x;
		MsgToPost.Param2	= TaskMain_NextSetpointPos.y;
		MsgToPost.Param3	= TaskMain_NextSetpointPos.angle;

		// Change Current Pos
		memcpy(&AppCurrentPos, &TaskMain_NextSetpointPos, sizeof(StructPos));

		// Post new expected pos
		AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);
	}
	OSMutexPost(Mut_AppCurrentPos);							// FIN SECTION CRITIQUE

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
	
		// if time is running, we check current postition
		if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0)
		{
			// Check if we are arrived to setpoint
			if(OS_TRUE == TaskMain_IsSetpointReached())
			{
				// Setpoint has been reached, we check for next action
				TaskMain_GetNextAction();

				// We send new pos to asser task
				// Create msg for asser task for setting start pos
				MsgToPost.Msg		= Msg_Asser_GoToXYA;
				MsgToPost.Param1	= TaskMain_NextSetpointPos.x;
				MsgToPost.Param2	= TaskMain_NextSetpointPos.y;
				MsgToPost.Param3	= TaskMain_NextSetpointPos.angle;

				// Post new expected pos
				AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);
			}
		}

	// We loop until timer is set
	}while((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0);

	// Time is up :
	#ifdef _TARGET_STARTER_KIT
		LED_Off(1);
		SoftReset();
	#endif


	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}

