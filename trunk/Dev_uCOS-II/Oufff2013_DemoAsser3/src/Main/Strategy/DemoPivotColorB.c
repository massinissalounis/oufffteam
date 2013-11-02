/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : Fichier de strategie produit par StrategyGenerator
*
* Suivi de version :
* 2011-06-01 | PBE | Creation de la version de base pour la coupe 2011
* 2011-11-02 | PBE | Mise a jour du fichier pour en faire un fichier pattern pour la couleur A
*********************************************************************************************************
*/

#include "StrategyFromColor.h"

#ifdef DEMO_PIVOT_ENABLED

#define DEFAULT_SPEED (60)
#define DEFAULT_PIVOT_SPEED	(60)

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_Blocking;
	InitCmd->Param2				= 2500;	
	InitCmd->Param3				= 1000;	
	InitCmd->Param4				= AppConvertDegInRad(0);
	InitCmd->ActiveSensorsFlag		= APP_PARAM_STRATEGYFLAG_NONE;

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetNextAction(StructCmd *NextAction)
{
	static int		NextActionID = 0;
	static int		TimeoutID = -1;
	static int		SubStrategyReturnID = -1;
	int				CurrentActionID = 0;
	INT8U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;
	OS_FLAGS		StrategyFlagsToSet = 0;
	StructCmd 		*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	p->CmdType = CmdType_Blocking;

	// Set CurrentID to NextID
	CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ACTION_TIMEOUT, OS_FLAG_WAIT_SET_ANY, &Err);
	if(((CurrentFlag & APP_PARAM_APPFLAG_ACTION_TIMEOUT) == APP_PARAM_APPFLAG_ACTION_TIMEOUT) && (TimeoutID != -1))
	{
		CurrentActionID = TimeoutID;
		// Clear Timeout Flag
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_ACTION_TIMEOUT, OS_FLAG_CLR, &Err);
	}
	else
		CurrentActionID = NextActionID;

	// Check if NextID must be change due to previous order
	if(CurrentActionID == 0)
	{
		// We have to check previous order
		if(SubStrategyReturnID > 0)
		{
			CurrentActionID = SubStrategyReturnID;		// Change NextID to return to the correct ID after SubStrategy loop
			SubStrategyReturnID = -1;
		}
		else
		{
			CurrentActionID = 1;						// There is no pending action, we go to the first state
		}
	}

	// Read Next Action
	switch(CurrentActionID)
	{
		// SUB_STRATEGY_BEGIN_LOOP
		case 1:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = MainStrategy
		case 2:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 3;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = MainStrategy
		case 3:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = LEFT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 0;	break;	// SubStrategyName = MainStrategy
		case 4:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 5;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = LEFT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = -90;	break;	// SubStrategyName = MainStrategy
		case 5:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 6;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 0;	break;	// SubStrategyName = MainStrategy
		case 6:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 7;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = MainStrategy
		case 7:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 8;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 180;	break;	// SubStrategyName = MainStrategy
		case 8:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 9;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = -90;	break;	// SubStrategyName = MainStrategy
		case 9:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = -1;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 0;	break;	// SubStrategyName = MainStrategy

		// SUB_STRATEGY_END_LOOP

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
	}

	// Check for Wait command --------------------------------------------
	if(App_Wait == p->Cmd)
	{
		// Nothing to do. All is done in TaskMain
	}

	// Check for conditionnal command -----------------------------
	if((App_IfGoto_System == p->Cmd) || (App_IfGoto_Strategy == p->Cmd))
	{
		// Read the current Flags
		if(App_IfGoto_System == p->Cmd)
			CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ALL, OS_FLAG_WAIT_SET_ANY, &Err);
		else
			CurrentFlag = OSFlagAccept(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_ALL, OS_FLAG_WAIT_SET_ANY, &Err);

		if(NextActionID >= 0)
			SubStrategyReturnID = NextActionID;

		// If condition is true, we go to the ID given by Param2, otherwise we use Param3
		if(((p->Param1 == -1) || (CurrentFlag & (p->Param1)) != 0))
		{
			NextActionID = (int)(p->Param2);
		}
		else
		{
			NextActionID = (int)(p->Param3);
		}
	}
	
	// Set / Clear Strategy Flags --------------------------------------
	if(App_SetStrategyFlags == p->Cmd)
	{
		// Nothing to do. All is done in TaskMain
	}
	
	// Create the MvtSimple Command --------------------------------------
	if(MvtSimple_MoveInMM == p->Cmd) 
		LibMoving_MoveInMM(p->Param2, p->Param1, p);

	if(MvtSimple_RotateInDeg == p->Cmd)
		LibMoving_RotateInDeg(p->Param4, p->Param1, p);
	
	if(MvtSimple_RotateToAngleInDeg == p->Cmd)
		LibMoving_RotateToAngleInDeg(p->Param4, p->Param1, p);

	// Angle Conversion --------------------------------------------------
	if((Mvt_UsePivotMode == p->Cmd) || (Mvt_UseMixedMode == p->Cmd) || (Mvt_UseSpline == p->Cmd))
	{
		p->Param4 = AppConvertDegInRad(p->Param4);
	}

	return ERR__NO_ERROR;
}

#endif
