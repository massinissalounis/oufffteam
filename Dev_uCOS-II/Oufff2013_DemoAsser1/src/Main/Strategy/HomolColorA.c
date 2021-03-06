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

#ifdef HOMOL_STRATEGY_ENABLED

#define DEFAULT_SPEED (50)
#define DEFAULT_PIVOT_SPEED	(50)

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_Blocking;
	InitCmd->Param2				= 97;	
	InitCmd->Param3				= 547;	
	InitCmd->Param4				= AppConvertDegInRad(180);
	InitCmd->ActiveSensorsFlag		= APP_PARAM_STRATEGYFLAG_NONE;

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetNextAction(StructCmd *NextAction)
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
			CurrentActionID = SubStrategyReturnID;		// Change NextID to return to the correct ID after SubStrategy loop
		else
			CurrentActionID = 1;						// There is no pending action, we go to the first state
	}

	// Read Next Action
	switch(CurrentActionID)
	{
		// SUB_STRATEGY_BEGIN_LOOP
		case 1:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1000;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = MainStrategy
		case 2:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2000;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 500;	p->Param3 = 630;	p->Param4 = 180;	break;	// SubStrategyName = MainStrategy

		case 2000:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2010;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = DV
		case 2010:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_LEFT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 2020;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateToAngleInDeg;	p->Param1 = DEFAULT_SPEED;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = 0;	break;	// SubStrategyName = DV
		case 2020:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2029;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_UP;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = DV
		case 2029:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2030;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 500;	break;	// SubStrategyName = DV
		case 2030:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2040;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = DV
		case 2040:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = -1;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = DV

		case 1000:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1010;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = V1
		case 1010:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_LONG_REAR);	NextActionID = 1100;	TimeoutID = 1300;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1820;	p->Param3 = 547;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1100:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1110;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_DOWN;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = V1
		case 1110:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1120;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 500;	break;	// SubStrategyName = V1
		case 1120:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT);	NextActionID = 1130;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = V1
		case 1130:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 1140;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = LEFT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1140:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1150;	TimeoutID = 1400;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 700;	p->Param3 = 817;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1150:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 1160;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 280;	p->Param3 = 630;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1160:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 2;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 500;	p->Param3 = 630;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1300:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1100;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = V1
		case 1400:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 1401;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = V1
		case 1401:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1410;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateInDeg;	p->Param1 = DEFAULT_SPEED;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = V1
		case 1410:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT);	NextActionID = 1411;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1597;	p->Param3 = 400;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1411:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1160;	TimeoutID = 1500;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 280;	p->Param3 = 630;	p->Param4 = 180;	break;	// SubStrategyName = V1
		case 1500:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 1501;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -100;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = V1
		case 1501:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1502;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_UP;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = V1
		case 1502:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1500;	p->Param3 = 1000;	p->Param4 = 180;	break;	// SubStrategyName = V1

		// SUB_STRATEGY_END_LOOP

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
	}

	// Check for Wait command --------------------------------------------
	if(App_Wait == p->Cmd)
	{
		// Execute the wait command
		OSTimeDlyHMSM(p->Param1, p->Param2, p->Param3, p->Param4);
		return StrategyColorA_GetNextAction(p);
	}

	// Check for conditionnal system command -----------------------------
	if(App_IfGoto_System == p->Cmd)
	{
		// Read the current Flags
		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ALL, OS_FLAG_WAIT_SET_ANY, &Err);

		if(NextActionID >= 0)
			SubStrategyReturnID = NextActionID;

		// If condition is true, we go to the ID given by Param2, otherwise we use Param3
		if((CurrentFlag & (p->Param1)) != 0)
		{
			NextActionID = (int)(p->Param2);
		}
		else
		{
			NextActionID = (int)(p->Param3);
		}

		return StrategyColorA_GetNextAction(p);
	}
	
	// Check for conditionnal strategy command ---------------------------
	if(App_IfGoto_Strategy == p->Cmd)
	{
		// Read the current Flags
		CurrentFlag = OSFlagAccept(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_ALL, OS_FLAG_WAIT_SET_ANY, &Err);

		if(NextActionID >= 0)
			SubStrategyReturnID = NextActionID;

		// If condition is true, we go to the ID given by Param2, otherwise we use Param3
		if((CurrentFlag & (p->Param1)) != 0)
		{
			NextActionID = (int)(p->Param2);
		}
		else
		{
			NextActionID = (int)(p->Param3);
		}
		
		return StrategyColorA_GetNextAction(p);
	}
	
	// Set / Clear Strategy Flags --------------------------------------
	if(App_SetStrategyFlags == p->Cmd)
	{
		StrategyFlagsToSet = p->Param1;

		if(p->Param2 != 0)
			OSFlagPost(AppStrategyFlags, StrategyFlagsToSet, OS_FLAG_SET, &Err);
		else
			OSFlagPost(AppStrategyFlags, StrategyFlagsToSet, OS_FLAG_CLR, &Err);
		
		return StrategyColorA_GetNextAction(p);
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
