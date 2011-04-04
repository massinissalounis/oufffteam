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

int TaskMain_NextState;

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextAction()
{
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextActionForColorA() // Blue
{
//	StructMvtPos *ptr = &TaskMain_ExpectedPos;

	// Activate Moving
//	ptr->IDActiveSensors = SENSORS_FRONT_ID;

	// Search for position
	switch(TaskMain_NextState)
	{	
		// Test pre match
//		case 0:		LibMoving_MoveInMM(&TaskMain_CurrentPos, -1000, ptr);								ptr->mode_control = 2;		LibMoving_SetSpeed(APP_INIT_ROBOT_SPEED); 		ptr->IDActiveSensors = SENSORS_FRONT_ID;  	break;
//		case 0: 	ptr->x = 0000.0; 	ptr->y = 0000.0;	ptr->angle = AppConvertDegInRad(0.0);		ptr->mode_control = 4;		LibMoving_SetSpeed(APP_INIT_ROBOT_SPEED); 		ptr->IDActiveSensors = SENSORS_FRONT_ID;  	break;
//		case 1: 	ptr->x = 0000.0; 	ptr->y = 0000.0;	ptr->angle = AppConvertDegInRad(0.0);		ptr->mode_control = 3;		LibMoving_SetSpeed(APP_INIT_ROBOT_SPEED); 		ptr->IDActiveSensors = SENSORS_FRONT_ID;  	break;

		// Default --------------------------------------------------------------------------------
		default:
//			ptr->IDActiveSensors = SENSORS_NONE_ID;
//			ptr->Flag = APP_FLAG_POS__LOCK_IN_POS;
//			return;
			break;
	}

	TaskMain_NextState++;
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_GetNextActionForColorB() // Yellow
{
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_Init()
{
	int i;

	memset(&TaskMain_CurrentPos, 0, sizeof(StructOdoPos));			// Set local CurrentPos to 0						
	memset(&TaskMain_ExpectedPos, 0, sizeof(StructOdoPos));			// Set local ExpectedPos to 0						
	memset(&TaskMain_NextSetpointPos, 0, sizeof(StructOdoPos));		// Set local NextSetpointPos to 0	

	TaskMain_NextState = 0;
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_CheckForBumpers()
{
	INT8U		Err;
	OS_FLAGS	CurrentBumpersFlag;
	char uart_buffer[8];
	char * buffer_ptr;
	int i;
	int TmpFlag;

	int IDActiveSensors = TaskMain_NextSetpointPos.IDActiveSensors;
	
	static BOOLEAN SensorsFlag[SENSORS_ALL+1];

	// Check for current flag
	CurrentBumpersFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ALL_BUMPERS, OS_FLAG_WAIT_SET_ANY, &Err);

	if((0 != CurrentBumpersFlag) || (OS_TRUE == SensorsFlag[SENSORS_ALL]))	
	{
		// Otherwise, we have to check, where we have bumped and how to escape
		// GP2D2_1 : Front **************************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_GP2D2_FRONT) == APP_PARAM_APPFLAG_GP2D2_FRONT) && ((IDActiveSensors & SENSORS_GPD2D_1_ID) == SENSORS_GPD2D_1_ID))	
		{
			if(OS_FALSE == SensorsFlag[SENSORS_GPD2D_1])
			{
				putsUART2("TaskMain: Collision -> GP2D2_FRONT\n");
				SensorsFlag[SENSORS_GPD2D_1] = OS_TRUE;

				// Check if we are checking for corn
//				if(!((TaskMain_NextSetpointPos.Flag & APP_FLAG_POS__CHECK_CORN) == APP_FLAG_POS__CHECK_CORN))
//				{
					TaskMain_StopMvt();
					
					// Select anti collision from color
//					if(c_Blue == AppCurrentColor)
//						LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_STOP);
	
//					if(c_Yellow == AppCurrentColor)
//						LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_STOP);
//				}
			}
		}
		else
		{
			SensorsFlag[SENSORS_GPD2D_1] = OS_FALSE;
		}
		
		// GP2D2_2 : Back ***************************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_GP2D2_BACK) == APP_PARAM_APPFLAG_GP2D2_BACK) && ((IDActiveSensors & SENSORS_GPD2D_2_ID) == SENSORS_GPD2D_2_ID))	
		{
			if(OS_FALSE == SensorsFlag[SENSORS_GPD2D_2])
			{
				putsUART2("TaskMain: Collision -> GP2D2_BACK\n");
				SensorsFlag[SENSORS_GPD2D_2] = OS_TRUE;
				TaskMain_StopMvt();	
				LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_STOP);
			}
		}
		else
		{
			SensorsFlag[SENSORS_GPD2D_2] = OS_FALSE;
		}
		
		// GP2D2_3 : Not Used ***********************************************************
/*		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_GP2D2_3) == APP_PARAM_APPFLAG_GP2D2_3) && ((IDActiveSensors & SENSORS_GPD2D_3_ID) == SENSORS_GPD2D_3_ID))
		{
			// TODO : Action à réaliser
		}
		else
		{
			SensorsFlag[SENSORS_GPD2D_3] = OS_FALSE;
		}

		// GP2D2_4 : Not Used ***********************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_GP2D2_4) == APP_PARAM_APPFLAG_GP2D2_4) && ((IDActiveSensors & SENSORS_GPD2D_4_ID) == SENSORS_GPD2D_4_ID))
		{
			// TODO : Action à réaliser
		}
		else
		{
			SensorsFlag[SENSORS_GPD2D_4] = OS_FALSE;
		}
*/
		// Clic 1 : Not Used **********************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC1) == APP_PARAM_APPFLAG_BUMPER_CLIC1) && ((IDActiveSensors & SENSORS_SW_1_ID) == SENSORS_SW_1_ID))	
		{
				// TODO : Action à réaliser
		}
		else
		{
			SensorsFlag[SENSORS_SW_1] = OS_FALSE;
		}

		// Clic 2 : Not Used *********************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC2) == APP_PARAM_APPFLAG_BUMPER_CLIC2) && ((IDActiveSensors & SENSORS_SW_2_ID) == SENSORS_SW_2_ID))	
		{
				// TODO : Action à réaliser
		}
		else
		{
			SensorsFlag[SENSORS_SW_2] = OS_FALSE;
		}
		
		// Clic 3 : Front Center ********************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC3) == APP_PARAM_APPFLAG_BUMPER_CLIC3) && ((IDActiveSensors & SENSORS_SW_3_ID) == SENSORS_SW_3_ID))	
		{
			if(OS_FALSE == SensorsFlag[SENSORS_SW_3])
			{
				putsUART2("TaskMain: Collision -> CLIC_FRONT_CENTER\n");
				SensorsFlag[SENSORS_SW_3] = OS_TRUE;

				// Check if we are checking for corn
//				if((TaskMain_NextSetpointPos.Flag & APP_FLAG_POS__CHECK_CORN) == APP_FLAG_POS__CHECK_CORN)
//				{
//					TaskMain_StopMvt();	
//					LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_CHECK_CORN);
//				}
//				else
//				{
					TaskMain_StopMvt();	
					// Select anti collision from color
//					if(c_Blue == AppCurrentColor)
//						LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_STOP);
	
//					if(c_Yellow == AppCurrentColor)
//						LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_STOP);
//				}
			}
		}
		else
		{
			SensorsFlag[SENSORS_SW_3] = OS_FALSE;
		}
		
		// Clic 4 : Back Center *********************************************************
		if(((CurrentBumpersFlag & APP_PARAM_APPFLAG_BUMPER_CLIC4) == APP_PARAM_APPFLAG_BUMPER_CLIC4) && ((IDActiveSensors & SENSORS_SW_4_ID) == SENSORS_SW_4_ID))	
		{
			if(OS_FALSE == SensorsFlag[SENSORS_SW_4])
			{
				putsUART2("TaskMain: Collision -> CLIC_BACK_CENTER\n");
				SensorsFlag[SENSORS_SW_4] = OS_TRUE; 
				TaskMain_StopMvt();	
				LibMoving_CreateEscapeSeq(APP_MOVING_ESCAPE_SEQ_STOP);
			}
		}
		else
		{
			SensorsFlag[SENSORS_SW_4] = OS_FALSE;
		}

		// Set value of FlagGlobal
		SensorsFlag[SENSORS_ALL] = OS_FALSE;
		for(i=0; i<SENSORS_ALL; i++)
			SensorsFlag[SENSORS_ALL] = SensorsFlag[SENSORS_ALL] | SensorsFlag[i];
	
		if(OS_FALSE == SensorsFlag[SENSORS_ALL])
			TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__NO_FLAG;
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
	memcpy(&TaskMain_CurrentPos, &AppCurrentPos, sizeof(StructOdoPos));
	
	// Release Mutex
	OSMutexPost(Mut_AppCurrentPos);

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_StopMvt()
{
	int i;
	int IDActiveSensors = TaskMain_NextSetpointPos.IDActiveSensors;

	// flush current queue
//	OSQFlush(AppQueueAsserEvent);

	// Create msg (an high priority msg) for stopping mvt
	TaskMain_GetCurrentPos();		// Read current Pos

	AppHighPrioMsg.IsRead = OS_FALSE;
	AppHighPrioMsg.Msg = Msg_Asser_GoToXYA;
	AppHighPrioMsg.Param1 = TaskMain_CurrentPos.x;		// X
	AppHighPrioMsg.Param2 = TaskMain_CurrentPos.y;		// Y
	AppHighPrioMsg.Param3 = TaskMain_CurrentPos.angle;	// ALPHA
	AppHighPrioMsg.Param4 = TaskMain_CurrentPos.mode_control;

	// Send STOP msg
//	OSQPostFront(AppQueueAsserEvent, (void*)(&AppHighPrioMsg));

	// Block movement until next order
	memcpy(&TaskMain_NextSetpointPos, &TaskMain_CurrentPos, sizeof(StructOdoPos));
	TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;
	TaskMain_NextSetpointPos.IDActiveSensors = IDActiveSensors;
	
	// Set all pending msg for AsserTask status to READ
	for(i=0; i<(APP_QUEUES_TOTAL_SIZE); i++)
	{
		if(		((AppMsgStk[i].Msg - Msg_Asser_MsgType) > 0 ) 
			&&	((AppMsgStk[i].Msg - Msg_Asser_MsgType) < 100))
		{
			memset(&(AppMsgStk[i]), 0, sizeof(StructMsg));
			AppMsgStk[i].IsRead = OS_TRUE;
		}
	}

	return;
}

// ------------------------------------------------------------------------------------------------
void TaskMain_StopAsser()
{
	int i;
	StructMsg	MsgToPost;							// Var to post msg to other tasks						

	// Stop movement
	TaskMain_StopMvt();

	// Disable all order from main
	TaskMain_NextSetpointPos.Flag = APP_FLAG_POS__LOCK_IN_POS;

	// Create stop msg
	MsgToPost.IsRead = OS_FALSE;
	MsgToPost.Msg = Msg_Asser_Algo;
	MsgToPost.Param1 = 0;		
	MsgToPost.Param2 = 0;		
	MsgToPost.Param3 = 0;	
	MsgToPost.Param4 = 0;	

	// Send msg
//	AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

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
	/* Todo
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
	*/

	return OS_FALSE;
}

// ------------------------------------------------------------------------------------------------
// TaskMain_Main()
// ------------------------------------------------------------------------------------------------
void TaskMain_Main(void *p_arg)
{
	INT8U		Err = 0;							// Var to get error status								
	OS_FLAGS	CurrentFlag = 0;					// Var to read current flag								
	StructMsg	MsgToPost;							// Var to post msg to other tasks						
	BOOLEAN		MsgIsWaitingForTransmit = OS_FALSE;	// Flag to indicate if a msg is waiting
	char 		uart_buffer[13];
	char 		*buffer_ptr;

	putsUART2("OUFFF TEAM 2011 : Main online\n");

	TaskMain_Init();
	
	// Wait other tasks start
	OSTimeDlyHMSM(0, 0, 1, 0);

	// Indicate which moving algo we're going to use
	// Create this msg
	MsgToPost.Msg		= Msg_Asser_Algo;
	MsgToPost.Param4	= APP_MOVING_ASSER_INITIAL_MODE_CTRL;
	// Post msg to activate moving algo
//	AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

	// Indicate speed we have to use
	// Create this msg
	MsgToPost.Msg		= Msg_Asser_SetSpeed;
	MsgToPost.Param1	= APP_INIT_ROBOT_SPEED;
	MsgToPost.Param2	= APP_NOT_USED;
	MsgToPost.Param3	= APP_NOT_USED;
	MsgToPost.Param4	= APP_NOT_USED;

	// Post msg to activate moving algo
//	AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

	//OSTimeDlyHMSM(0,0,1,0);

	// Wait for color
	while(c_NotSet == AppCurrentColor)
		OSTimeDly(1);


	// Get CurrentPos for current color
	/* Todo
	if(AppCurrentColor == c_Blue)
	{
		TaskMain_NextSetpointPos.x 					= APP_INIT_BLUE_POS_X;
		TaskMain_NextSetpointPos.y 					= APP_INIT_BLUE_POS_Y;
		TaskMain_NextSetpointPos.angle 				= AppConvertDegInRad(APP_INIT_BLUE_ANGLE);
		TaskMain_NextSetpointPos.Flag 				= APP_FLAG_POS__NO_FLAG;
		TaskMain_NextSetpointPos.IDActiveSensors	= SENSORS_NONE_ID;
		TaskMain_NextSetpointPos.mode_control		= APP_MOVING_ASSER_INITIAL_MODE_CTRL;
		putsUART2("TaskMain : Color Read -> Blue\n");
	}
	else
	{
		TaskMain_NextSetpointPos.x 					= APP_INIT_YELLOW_POS_X;
		TaskMain_NextSetpointPos.y 					= APP_INIT_YELLOW_POS_Y;
		TaskMain_NextSetpointPos.angle 				= AppConvertDegInRad(APP_INIT_YELLOW_ANGLE);
		TaskMain_NextSetpointPos.Flag 				= APP_FLAG_POS__NO_FLAG;
		TaskMain_NextSetpointPos.IDActiveSensors	= SENSORS_NONE_ID;
		TaskMain_NextSetpointPos.mode_control		= APP_MOVING_ASSER_INITIAL_MODE_CTRL;
		putsUART2("TaskMain : Color Read -> Yellow\n");
	}
	*/
	memcpy(&TaskMain_ExpectedPos, &TaskMain_NextSetpointPos, sizeof(StructOdoPos));

	// Define Current position to OdoTask and AsserTask
	OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);		// SECTION CRITIQUE
	{
		memset(&MsgToPost, 0, sizeof(StructMsg));

		// Create msg for asser task for setting start pos
		MsgToPost.Msg		= Msg_Asser_GoToXYA;
		MsgToPost.Param1	= TaskMain_NextSetpointPos.x;
		MsgToPost.Param2	= TaskMain_NextSetpointPos.y;
		MsgToPost.Param3	= TaskMain_NextSetpointPos.angle;
		MsgToPost.Param4	= TaskMain_NextSetpointPos.mode_control;

		// Post new expected pos
//		AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost);

		// Change Current Pos
		memcpy(&AppCurrentPos, &TaskMain_NextSetpointPos, sizeof(StructOdoPos));
	}
	OSMutexPost(Mut_AppCurrentPos);							// FIN SECTION CRITIQUE

	// Wait for start signal
	putsUART2("TaskMain : Wait for start signal\n");
	OSFlagPend(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ALL, WAIT_FOREVER, &Err);
	putsUART2("TaskMain : Go !! Go !! Go !!\n");
	
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

		// Check FLAGS for timer status
		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_WAIT_SET_ALL, &Err);
	
		// if time is running, we check current postition
		if((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0)
		{
			// Check for collisions
			TaskMain_CheckForBumpers();

			// Check if we can move
			if(!(APP_FLAG_POS__LOCK_IN_POS == (TaskMain_NextSetpointPos.Flag & APP_FLAG_POS__LOCK_IN_POS)))
			{
				if(OS_FALSE == MsgIsWaitingForTransmit)
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
						MsgToPost.Param4	= TaskMain_ExpectedPos.mode_control;
		
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
//						MsgIsWaitingForTransmit = !(AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost));
					}
				}
				else
				{
					// Post wainting msg
//					MsgIsWaitingForTransmit = !(AppPostQueueMsg(AppQueueAsserEvent, &MsgToPost));
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

	// Stop Asser
	TaskMain_StopAsser();

	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}

