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
	static int EscapeIndex = 0;

	if (	(TaskMain_NextSetpointPos.x == TaskMain_ExpectedPos.x)
		&&	(TaskMain_NextSetpointPos.y == TaskMain_ExpectedPos.y)
		&&	(TaskMain_NextSetpointPos.angle == TaskMain_ExpectedPos.angle)
		&&	(TaskMain_MovingSeqRemainingSteps == 0))
	{
		// Expected point has been reached, moving sequence must be deleted
		memset(TaskMain_MovingSeq, 0, APP_MOVING_SEQ_LEN * sizeof(struct StructPos));

		// we ask for a new point
		switch(AppCurrentColor)
		{
			case c_Blue:
				TaskMain_GetNextActionForColorA();
				break;

			case c_Yellow:
				TaskMain_GetNextActionForColorB();
				break;

			default:
				break;
		}

		// Check if it's necessary to compute a new command
		if(APP_FLAG_POS__NO_FLAG != TaskMain_ExpectedPos.Flag)
		{
			// Check Position Flag
			if(APP_FLAG_POS__LOCK_IN_POS == TaskMain_ExpectedPos.Flag)
			{
				TaskMain_NextSetpointPos.Flag = TaskMain_ExpectedPos.Flag;		
				return;
			}

			// Check Simple move Flag
			if(APP_FLAG_POS__SIMPLE_MOVE == TaskMain_ExpectedPos.Flag)
			{
				memcpy(&TaskMain_NextSetpointPos, &TaskMain_ExpectedPos, sizeof(struct StructPos));
				return;
			}
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
					sizeof(struct StructPos));
			TaskMain_MovingSeqRemainingSteps--;

			return;
		}
	}

	
	// Divide moving into simple commands
	TaskMain_GetCurrentPos();
	LibMoving_DivideMvt(&TaskMain_CurrentPos, &TaskMain_ExpectedPos, &TaskMain_MovingSeqRemainingSteps);
	
	// Check if we can move with new data
	if(TaskMain_MovingSeqRemainingSteps <= 0)
	{
		// We are blocked we try an escape seq
		switch(EscapeIndex)
		{
			// Go back
			case 0:
				LibMoving_MoveInMM(&TaskMain_CurrentPos, -150, TaskMain_MovingSeq + APP_MOVING_SEQ_LEN - 1);
				TaskMain_MovingSeqRemainingSteps = 1;
				EscapeIndex++;
				break;

			// Rotate
			case 1:
				LibMoving_RotateInDeg(&TaskMain_CurrentPos, -45, TaskMain_MovingSeq + APP_MOVING_SEQ_LEN - 1);
				TaskMain_MovingSeqRemainingSteps = 1;
				EscapeIndex++;
				break;

			// Move
			case 2:
				LibMoving_MoveInMM(&TaskMain_CurrentPos, 150, TaskMain_MovingSeq + APP_MOVING_SEQ_LEN - 1);
				TaskMain_MovingSeqRemainingSteps = 1;
				EscapeIndex++;
				break;

			// Rotate
			case 3: 
				LibMoving_RotateInDeg(&TaskMain_CurrentPos, 90, TaskMain_MovingSeq + APP_MOVING_SEQ_LEN - 1);
				TaskMain_MovingSeqRemainingSteps = 1;
				EscapeIndex++;
				break;

			default:
				EscapeIndex = 0;
				break;
		}

	}
	
	// Get next postion with new data
	TaskMain_GetNextAction();

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextActionForColorA()
{
	static CPU_INT08U CurrentActionForColorA = 0;
	struct StructPos *ptr = &TaskMain_ExpectedPos;

	// Activate Moving
	ptr->Flag = APP_FLAG_POS__NO_FLAG;

	// Search for position
	switch(CurrentActionForColorA)
	{	
		// Carre
		case 0:		ptr->x = 0200.0;	ptr->y = 0200.0;	ptr->angle	= AppConvertDegInRad(0045.0);		break;
		case 1:		ptr->x = 0200.0;	ptr->y = 0800.0;	ptr->angle	= AppConvertDegInRad(0090.0);		break;
		case 2:		ptr->x = 0800.0;	ptr->y = 0800.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 3:		ptr->x = 0800.0;	ptr->y = 0200.0;	ptr->angle	= AppConvertDegInRad(-090.0);		break;
		case 4:		ptr->x = 0200.0;	ptr->y = 0200.0;	ptr->angle	= AppConvertDegInRad(-180.0);		break;
		case 5:		ptr->x = 0130.0;	ptr->y = 0130.0;	ptr->angle	= AppConvertDegInRad(-135.0);		break;
		

//		case 1:		LibMoving_MoveInMM(TaskMain_CurrentPos, 1000, ptr);									break;
//		case 2:		LibMoving_MoveInMM(TaskMain_CurrentPos, -950, ptr);									break;

		// Default --------------------------------------------------------------------------------
		default:
			ptr->Flag = APP_FLAG_POS__LOCK_IN_POS;
			return;
			break;
	}

	CurrentActionForColorA++;
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextActionForColorB()
{
	static CPU_INT08U CurrentActionForColorB = 0;
	CPU_INT08U TempoColorB = 0;
	struct StructPos *ptr = &TaskMain_ExpectedPos;

	// Activate Moving
	ptr->Flag = APP_FLAG_POS__NO_FLAG;

	switch(CurrentActionForColorB)
	{
/*		// Test de Distance
		case 0:		ptr->x = 0500.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 1:		ptr->x = 1750.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 2:		ptr->x = 0500.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 3:		ptr->x = 1750.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 4:		ptr->x = 0500.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 5:		ptr->x = 1750.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 6:		ptr->x = 0500.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 7:		ptr->x = 1750.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 8:		ptr->x = 0500.0;	ptr->y = 0500.0;	ptr->angle	= AppConvertDegInRad(0000.0);		break;
		case 9:		ptr->x = 0130.0;	ptr->y = 0130.0;	ptr->angle	= AppConvertDegInRad(0225.0);		break;
*/		

		case 0:		LibMoving_MoveInMM(&TaskMain_CurrentPos, 550, ptr);			break;
		case 1:		LibMoving_MoveInMM(&TaskMain_CurrentPos, -450, ptr);		break;

		// Default --------------------------------------------------------------------------------
		default:
			ptr->Flag = APP_FLAG_POS__LOCK_IN_POS;
			return;
			break;
	}
	CurrentActionForColorB++;
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_Init()
{
	memset(&TaskMain_CurrentPos, 0, sizeof(struct StructPos));				// Set local CurrentPos to 0						
	memset(&TaskMain_ExpectedPos, 0, sizeof(struct StructPos));			// Set local ExpectedPos to 0						
	memset(&TaskMain_NextSetpointPos, 0, sizeof(struct StructPos));		// Set local NextSetpointPos to 0						

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_CheckForBumpers()
{
	INT8U		Err;
	OS_FLAGS	CurrentBumpersFlag;
	char uart_buffer[8];
	char * buffer_ptr;
	static BOOLEAN FlagGP2D2_1 = OS_FALSE;		// Flag for simple detection (GB2D2 1)
	static BOOLEAN FlagGP2D2_2 = OS_FALSE;		// Flag for simple detection (GB2D2 2)
	static BOOLEAN FlagGP2D2_3 = OS_FALSE;		// Flag for simple detection (GB2D2 3)
	static BOOLEAN FlagGP2D2_4 = OS_FALSE;		// Flag for simple detection (GB2D2 4)
	static BOOLEAN FlagGP2D2_5 = OS_FALSE;		// Flag for simple detection (GB2D2 5)
	static BOOLEAN FlagClicClic_1 = OS_FALSE;	// Flag for simple detection (ClicClic 1)
	static BOOLEAN FlagClicClic_2 = OS_FALSE;	// Flag for simple detection (ClicClic 2)
	static BOOLEAN FlagClicClic_3 = OS_FALSE;	// Flag for simple detection (ClicClic 3)
	static BOOLEAN FlagClicClic_4 = OS_FALSE;	// Flag for simple detection (ClicClic 4)
	static BOOLEAN FlagGlobal = OS_FALSE;		// Flag for summerise all other bumpers state
		
	// Check for current flag
	CurrentBumpersFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ALL_BUMPERS, OS_FLAG_WAIT_SET_ANY, &Err);

	if((0 != CurrentBumpersFlag) || (OS_TRUE == FlagGlobal))	
	{
		// Otherwise, we have to check, where we have bumped and how to escape
		// GP2D2 : Front
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_GP2D2_FRONT) == APP_PARAM_APPFLAG_GP2D2_FRONT)	
		{
			if(OS_FALSE == FlagGP2D2_1)
			{
				FlagGP2D2_1 = OS_TRUE;
				TaskMain_StopMvt();	
				// TODO : Action à réaliser
				TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
			}
		}
		else
			FlagGP2D2_1 = OS_FALSE;
		
		// GP2D2 : Back
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_GP2D2_BACK) == APP_PARAM_APPFLAG_GP2D2_BACK)	
		{
			if(OS_FALSE == FlagGP2D2_2)
			{
				FlagGP2D2_2 = OS_TRUE;
				TaskMain_StopMvt();	
				// TODO : Action à réaliser
				TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
			}
		}
		else
			FlagGP2D2_2 = OS_FALSE;
		
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
		
		// Clic 4 : Back Center
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC4) == APP_PARAM_APPFLAG_BUMPER_CLIC4)	
		{
			if(OS_FALSE == FlagClicClic_4)
			{
				FlagClicClic_4 = OS_TRUE;
				TaskMain_StopMvt();	
				// TODO : Action à réaliser
				TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
			}
		}
		else
			FlagClicClic_4 = OS_FALSE;

		
		// Clic 3 : Front Center
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC3) == APP_PARAM_APPFLAG_BUMPER_CLIC3)	
		{
			if(OS_FALSE == FlagClicClic_3)
			{
				FlagClicClic_3 = OS_TRUE;
				TaskMain_StopMvt();	
				// TODO : Action à réaliser
				TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
			}
		}
		else
			FlagClicClic_3 = OS_FALSE;
		
		// Clic 2 : Front Right
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC2) == APP_PARAM_APPFLAG_BUMPER_CLIC2)	
		{
			if(OS_FALSE == FlagClicClic_2)
			{
				FlagClicClic_2 = OS_TRUE;
				TaskMain_StopMvt();	
				// TODO : Action à réaliser
				TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
			}
		}
		else
			FlagClicClic_2 = OS_FALSE;
		
		// Clic 1 : Front Left
		if((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC1) == APP_PARAM_APPFLAG_BUMPER_CLIC1)	
		{
			if(OS_FALSE == FlagClicClic_1)
			{
				FlagClicClic_1 = OS_TRUE;
				TaskMain_StopMvt();	
				// TODO : Action à réaliser
				TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
			}
		}
		else
			FlagClicClic_1 = OS_FALSE;

		// Set value of FlagGlobal
		FlagGlobal = FlagGP2D2_1 || FlagGP2D2_2 || FlagGP2D2_3 || FlagGP2D2_4 || FlagGP2D2_5 || FlagClicClic_1 || FlagClicClic_2 || FlagClicClic_3 || FlagClicClic_4;
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
	memcpy(&TaskMain_CurrentPos, &AppCurrentPos, sizeof(struct StructPos));
	
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
	#ifdef _TARGET_STARTER_KIT
		static INT8U NbOfRead = 0;
		INT8U Err;

		NbOfRead++;
		if(NbOfRead > 2)
		{
			NbOfRead = 0;
			
			// Ask for Mutex on position
			OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);
	
			// Modify current pos
			AppCurrentPos.x		= TaskMain_NextSetpointPos.x;
			AppCurrentPos.y		= TaskMain_NextSetpointPos.y;
			AppCurrentPos.angle	= TaskMain_NextSetpointPos.angle;
	
			// Release Mutex
			OSMutexPost(Mut_AppCurrentPos);
		}
	#endif

	// Check for x and y
	if(		(TaskMain_CurrentPos.x >= (TaskMain_NextSetpointPos.x - APP_PARAM_ERR_ON_POS)) 

		&&	(TaskMain_CurrentPos.y >= (TaskMain_NextSetpointPos.y - APP_PARAM_ERR_ON_POS))
		&&	(TaskMain_CurrentPos.x <= (TaskMain_NextSetpointPos.x + APP_PARAM_ERR_ON_POS))
		&&	(TaskMain_CurrentPos.y <= (TaskMain_NextSetpointPos.y + APP_PARAM_ERR_ON_POS)))
	{
		// Check for angle
		if(fabs(AppCheckAngleInRad(TaskMain_NextSetpointPos.angle - TaskMain_CurrentPos.angle)) < APP_PARAM_ERR_ON_ANGLE)
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
	char uart_buffer[13];
	char * buffer_ptr;

	putsUART2("OUFFF TEAM 2010 : Main online\n");

	TaskMain_Init();

	// Indicate which moving algo we're going to use
	// Create this msg
	MsgToPost.Msg		= Msg_Asser_Algo;
	MsgToPost.Param1	= APP_MOVING_ASSER_IN_POS_ENABLED;
	MsgToPost.Param2	= APP_MOVING_ASSER_IN_ANGLE_ENABLED;
	MsgToPost.Param3	= APP_MOVING_ASSER_IN_SPEED_ENABLED;
	// Post msg to activate moving algo
	AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

	// Indicate speed we have to use
	// Create this msg
	MsgToPost.Msg		= Msg_Asser_SetSpeed;
	MsgToPost.Param1	= APP_INIT_ROBOT_SPEED;
	MsgToPost.Param2	= APP_NOT_USED;
	MsgToPost.Param3	= APP_NOT_USED;
	// Post msg to activate moving algo
	AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

	// Wait for start signal
	OSFlagPend(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ALL, WAIT_FOREVER, &Err);

	// Get CurrentPos for current color
	if(AppCurrentColor == c_Blue)
	{
		TaskMain_NextSetpointPos.x 			= APP_INIT_BLUE_POS_X;
		TaskMain_NextSetpointPos.y 			= APP_INIT_BLUE_POS_Y;
		TaskMain_NextSetpointPos.angle 		= AppConvertDegInRad(APP_INIT_BLUE_ANGLE);
		TaskMain_NextSetpointPos.Flag 		= APP_FLAG_POS__NO_FLAG;
	}
	else
	{
		TaskMain_NextSetpointPos.x 			= APP_INIT_YELLOW_POS_X;
		TaskMain_NextSetpointPos.y 			= APP_INIT_YELLOW_POS_Y;
		TaskMain_NextSetpointPos.angle 		= AppConvertDegInRad(APP_INIT_YELLOW_ANGLE);
		TaskMain_NextSetpointPos.Flag 		= APP_FLAG_POS__NO_FLAG;
	}

	memcpy(&TaskMain_ExpectedPos, &TaskMain_NextSetpointPos, sizeof(struct StructPos));

	
	// Define Current position to OdoTask and AsserTask
	OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);		// SECTION CRITIQUE
	{
		memset(&MsgToPost, 0, sizeof(StructMsg));

		// Create msg for asser task for setting start pos
		MsgToPost.Msg		= Msg_Asser_GoToXYA;
		MsgToPost.Param1	= TaskMain_NextSetpointPos.x;
		MsgToPost.Param2	= TaskMain_NextSetpointPos.y;
		MsgToPost.Param3	= TaskMain_NextSetpointPos.angle;

		// Post new expected pos
		AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

		// Change Current Pos
		memcpy(&AppCurrentPos, &TaskMain_NextSetpointPos, sizeof(struct StructPos));
	}
	OSMutexPost(Mut_AppCurrentPos);							// FIN SECTION CRITIQUE

	// MAIN LOOP ==================================================================================
	do
	{
		#ifdef _TARGET_STARTER_KIT
			LED_Toggle(1);
		#endif

		// Proc Release
		OSTimeDly(10);

		// Read Current position
		TaskMain_GetCurrentPos();

		// Check for collisions
		TaskMain_CheckForBumpers();

		// Check FLAGS for timer status
		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_WAIT_SET_ALL, &Err);
	
		// if time is running, we check current postition
		if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0)
		{
			// Check if we are arrived to setpoint
			if(OS_TRUE == TaskMain_IsSetpointReached())
			{
				// Setpoint has been reached, we check for next action
				TaskMain_GetNextAction();

				if(0 == (TaskMain_NextSetpointPos.Flag & APP_FLAG_POS__LOCK_IN_POS))
				{
					// We send new pos to asser task
					// Create msg for asser task for setting start pos
					MsgToPost.Msg		= Msg_Asser_GoToXYA;
					MsgToPost.Param1	= TaskMain_NextSetpointPos.x;
					MsgToPost.Param2	= TaskMain_NextSetpointPos.y;
					MsgToPost.Param3	= TaskMain_NextSetpointPos.angle;
	
					// Test
					OSTimeDlyHMSM(0, 0, 1, 0);		
				
					/*putsUART2("TASK_MAIN : Send Mesg ---> X=");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) TaskMain_NextSetpointPos.x, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					putsUART2(buffer_ptr);
					putsUART2(" , Y=");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) TaskMain_NextSetpointPos.y, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					putsUART2(buffer_ptr);
					putsUART2(" , Angle=");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) AppConvertRadInDeg(TaskMain_NextSetpointPos.angle), (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					putsUART2(buffer_ptr);
					putsUART2("\n");*/
	
					// Post new expected pos
					AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);
				}
			}
		}

	// We loop until timer is set
	}while((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0);
	// ===============================================================================================

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

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveInMM(struct StructPos *OldPos, int dist, struct StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new position
	NewPos->x = OldPos->x + dist * cosf(OldPos->angle);
	NewPos->y = OldPos->y + dist * sinf(OldPos->angle);
	NewPos->angle = OldPos->angle;

	NewPos->Flag = APP_FLAG_POS__SIMPLE_MOVE;
	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateInDeg(struct StructPos *OldPos, float AngleInDeg, struct StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = OldPos->angle + AppConvertDegInRad(AngleInDeg);

	NewPos->Flag = APP_FLAG_POS__SIMPLE_MOVE;
	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveToAngleInDeg(struct StructPos *OldPos, float AngleToGoInDeg, struct StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = AppConvertDegInRad(AngleToGoInDeg);

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_DivideMvt(struct StructPos *OldPos, struct StructPos *ExpectedPos, int *NewMovingSeqRemainingSteps)
{
	// Check for parameters
	if((NULL == OldPos) || (NULL == ExpectedPos) || (NULL == NewMovingSeqRemainingSteps))
	{
		if(NULL != NewMovingSeqRemainingSteps)
			*NewMovingSeqRemainingSteps == -1;
		
		return;
	}

#ifdef APP_MOVING_ALGO_1_SIMPLE
	// Simple Moving Algo
	float TmpX = 0;
	float TmpY = 0;
	float TmpAngle = 0;
	float TmpNewAngle = 0;

	TmpX = ExpectedPos->x - OldPos->x;
	TmpY = ExpectedPos->y - OldPos->y;

	// If movement is too short for computation, we don't do anything
	if((fabs(TmpX) < APP_PARAM_ERR_ON_POS) && (fabs(TmpY) < APP_PARAM_ERR_ON_POS))
	{
		// Third (last) one: Turn to the expected pos
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].x	 	= ExpectedPos->x;
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].y	 	= ExpectedPos->y;
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].angle 	= ExpectedPos->angle;
	
		// Set the nb of steps for this movment
		*NewMovingSeqRemainingSteps = 1;
	}

	// Movment will be done in 3 steps
	// First one: Turn to be in the correct direction
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).x	 	= OldPos->x;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).y	 	= OldPos->y;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).angle 	= atan2f(TmpY, TmpX);

	// Compute Angle
	//TmpAngle = atan2f(TmpY, TmpX);
	//TmpNewAngle = TmpAngle - (TmpAngle / fabs(TmpAngle))*2*M_PI;
	//if(fabs(TmpAngle - OldPos->angle) < fabs(TmpNewAngle - OldPos->angle))
	//	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).angle 	= TmpAngle;
	//else
	//	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).angle 	= TmpNewAngle;

	// Second one: Go to the expected pos
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).x	 	= ExpectedPos->x;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).y	 	= ExpectedPos->y;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).angle 	= TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3].angle;

	// Third (last) one: Turn to the expected pos
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).x	 	= ExpectedPos->x;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).y	 	= ExpectedPos->y;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).angle 	= ExpectedPos->angle;
	// Compute Angle
	//TmpAngle = ExpectedPos->angle;
	//TmpNewAngle = TmpAngle - (TmpAngle / fabs(TmpAngle))*2*M_PI;
	//if(fabs(TmpAngle - OldPos->angle) < fabs(TmpNewAngle - OldPos->angle))
	//	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).angle 	= TmpAngle;
	//else
	//	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).angle 	= TmpNewAngle;

	// Set the nb of steps for this movment
	*NewMovingSeqRemainingSteps = 3;

	// First algo has been set, don't try another one
	return;
#endif

	// if we are here, that means that no moving algo has been set
	*NewMovingSeqRemainingSteps = -1;
	return;
}
