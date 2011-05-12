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
// TaskMain_Main()
// ------------------------------------------------------------------------------------------------
void TaskMain_Main(void *p_arg)
{
	EnumColor	LastColorRead= c_NotSet;			// Used to check color modification
	INT8U		Err = 0;							// Var to get error status								
	OS_FLAGS	CurrentFlag = 0;					// Var to read current flag								
	StructMsg	MsgToPost;							// Var to post msg to other tasks						
	char 		uart_buffer[13];
	char 		*buffer_ptr;

	putsUART2("OUFFF TEAM 2011 : Main online\n");

	// Wait other tasks start
	OSTimeDlyHMSM(0, 0, 1, 0);

#ifdef _TARGET_440H
	OSTimeDlyHMSM(0, 0, 4, 0);
	Set_Line_Information( 1, 0, "                 ", 16);
	Set_Line_Information( 2, 0, "                 ", 16);
	AppCurrentColor = c_ColorA;
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
			// Get CurrentPos for current color
			if(AppCurrentColor == c_ColorA)
			{
				// Todo : Define new position from color
				putsUART2("TaskMain : Color = Blue\n");
			}
			else
			{
				// Todo : Define new position from color
				putsUART2("TaskMain : Color = Red\n");
			}

			// Todo : Send new position to TaskMvt
		}

		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ANY, &Err);
	}while((CurrentFlag & APP_PARAM_APPFLAG_START_BUTTON) == 0);

	putsUART2("TaskMain : Go !! Go !! Go !!\n");
	
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

