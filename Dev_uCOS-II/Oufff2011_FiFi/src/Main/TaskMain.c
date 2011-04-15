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

// ------------------------------------------------------------------------------------------------
void TaskMain_Init()
{
	return;
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

	//putsUART2("OUFFF TEAM 2011 : Main online\n");

	/* Todo
	TaskMain_Init();
	
	// Wait other tasks start
	OSTimeDlyHMSM(0, 0, 1, 0);

	// Wait for color
	while(c_NotSet == AppCurrentColor)
		OSTimeDly(1);


	// Get CurrentPos for current color
	if(AppCurrentColor == c_ColorA)
	{
		putsUART2("TaskMain : Color Read -> Blue\n");
	}
	else
	{
		putsUART2("TaskMain : Color Read -> Yellow\n");

	}
	

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
		memcpy(&AppCurrentPos, &TaskMain_NextSetpointPos, sizeof(StructPos));
		
	}
	OSMutexPost(Mut_AppCurrentPos);							// FIN SECTION CRITIQUE

	// Wait for start signal
	putsUART2("TaskMain : Wait for start signal\n");
	OSFlagPend(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ALL, WAIT_FOREVER, &Err);
	putsUART2("TaskMain : Go !! Go !! Go !!\n");
	*/
	// MAIN LOOP ==================================================================================
	do
	{
		// Proc Release
		OSTimeDly(10);
		
		Set_Line_Information( 2, 0, "Debug : ", 8);
		// Check FLAGS for timer status
		//CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_WAIT_SET_ALL, &Err);

		// DEBUG
		{
			if(CLIC_state(SW1) == 1)
			{
				Set_Line_Information( 2, 8, "1 ", 2);
				OSFlagPost(AppFlags, APP_PARAM_APPFLAG_START_BUTTON + APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_SET, &Err);
			}
			else
				Set_Line_Information( 2, 8, "0 ", 2);


			if(CLIC_state(SW2) == 1)
			{
				Set_Line_Information( 2, 10, "1 ", 2);
				OSFlagPost(AppFlags, APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_CLR, &Err);
			}
			else
				Set_Line_Information( 2, 10, "0 ", 2);

            
            if(CLIC_state(SW3) == 1)
			{
				Set_Line_Information( 2, 12, "1 ", 2);
				OSFlagPost(AppFlags, APP_PARAM_APPFLAG_SW_1 + APP_PARAM_APPFLAG_GP2_1, OS_FLAG_SET, &Err);
			}
			else
            {
				Set_Line_Information( 2, 12, "0 ", 2);
				OSFlagPost(AppFlags, APP_PARAM_APPFLAG_SW_1 + APP_PARAM_APPFLAG_GP2_1, OS_FLAG_CLR, &Err);
            }

		}
	
	// We loop until timer is set
	}while((CurrentFlag & APP_PARAM_APPFLAG_TIMER_STATUS) == 0);
	// ===============================================================================================

	// Time is up : Wait for ever
	while(OS_TRUE)
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}

