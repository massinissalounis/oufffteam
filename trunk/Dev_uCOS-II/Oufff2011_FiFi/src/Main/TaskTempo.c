/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskTempo.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************
*/

#include "TaskTempo.h"
#include "AppGlobalVars.h"

// ------------------------------------------------------------------------------------------------
// TaskTempo_Main()
// ------------------------------------------------------------------------------------------------
void TaskTempo_Main(void *p_arg)
{
	INT32U	StopTime = 0;			/* Last TICKS number									*/
	INT32U	CurrentTime = 0;		/* Curent TICKS from OS									*/
	INT8U	Err = 0;				/* Var to get error status								*/

	AppDebugMsg("OUFFF TEAM 2011 : Tempo online\n");
	
	// Wait for start msg
	OSFlagPend(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ALL, 0, &Err);
	
	// Compute end time
	StopTime = OSTimeGet() + APP_PARAM_GAME_DURATION * OS_TICKS_PER_SEC;

	#ifdef _TARGET_440H
		Set_Line_Information( 2, 15, "T", 1);
	#endif

	do
	{
		OSTimeDlyHMSM(0, 0, 0, APP_PARAM_TEMPO_RESOLUTION);		// Delay before next TICKS read
		CurrentTime = OSTimeGet();								// Read current TICKS
	}
	while(CurrentTime < StopTime);

	// Time is up. We post the ending flag
	OSFlagPost(AppFlags, APP_PARAM_APPFLAG_TIMER_STATUS, OS_FLAG_SET, &Err); 

	#ifdef _TARGET_440H
		Set_Line_Information( 2, 15, "X", 1);
	#endif

	while(OS_TRUE)	
	{	
		OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	return;
}
