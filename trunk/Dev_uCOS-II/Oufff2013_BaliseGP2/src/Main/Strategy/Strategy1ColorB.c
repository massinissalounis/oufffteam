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

#ifdef STRATEGY1_ENABLED

#define DEFAULT_SPEED (60)
#define DEFAULT_PIVOT_SPEED	(50)

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_Blocking;
	InitCmd->Param2				= 2903;	
	InitCmd->Param3				= 547;	
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
		case 1:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 50;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = MainStrategy
		case 50:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 75;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_GLASS_1_DONE;	p->Param2 = 100;	p->Param3 = 55;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 55:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 60;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GLASS_1_DONE;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 60:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1000;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 75:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = 3000;	p->Param3 = 0;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 100:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 125;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_GLASS_2_DONE;	p->Param2 = 150;	p->Param3 = 110;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 110:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 115;	TimeoutID = 150;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2400;	p->Param3 = 1100;	p->Param4 = 0;	break;	// SubStrategyName = MainStrategy
		case 115:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 117;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GLASS_2_DONE;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 117:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2000;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 125:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = 3000;	p->Param3 = 0;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 150:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 175;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_1_DONE + APP_PARAM_STRATEGYFLAG_GIFT_1_TRY);	p->Param2 = 200;	p->Param3 = 155;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 155:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 160;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_1_TRY;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 160:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 165;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 165:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 4000;	TimeoutID = 940;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2400;	p->Param3 = 450;	p->Param4 = -90;	break;	// SubStrategyName = MainStrategy
		case 175:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = 180;	p->Param3 = 0;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 180:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_1_DONE;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 200:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 225;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_2_DONE + APP_PARAM_STRATEGYFLAG_GIFT_2_TRY);	p->Param2 = 250;	p->Param3 = 205;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 205:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 210;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_2_TRY + APP_PARAM_STRATEGYFLAG_GLASS_2_DONE);	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 210:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 215;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 215:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 4000;	TimeoutID = 940;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1800;	p->Param3 = 450;	p->Param4 = -90;	break;	// SubStrategyName = MainStrategy
		case 225:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = 230;	p->Param3 = 0;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 230:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_2_DONE;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 250:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 275;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_3_DONE + APP_PARAM_STRATEGYFLAG_GIFT_3_TRY);	p->Param2 = 300;	p->Param3 = 255;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 255:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 260;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_3_TRY;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 260:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 265;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 265:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 4000;	TimeoutID = 940;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1200;	p->Param3 = 450;	p->Param4 = -90;	break;	// SubStrategyName = MainStrategy
		case 275:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = 280;	p->Param3 = 0;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 280:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_3_DONE;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 300:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 325;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_4_DONE + APP_PARAM_STRATEGYFLAG_GIFT_4_TRY);	p->Param2 = 950;	p->Param3 = 305;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 305:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 310;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_4_TRY;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 310:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 315;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 315:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 4000;	TimeoutID = 942;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 600;	p->Param3 = 450;	p->Param4 = -90;	break;	// SubStrategyName = MainStrategy
		case 325:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = 330;	p->Param3 = 0;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 330:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 950;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_GIFT_4_DONE;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 940:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 0;	TimeoutID = 0;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -200;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 942:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 960;	TimeoutID = 0;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -200;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 950:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 955;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_1_TRY + APP_PARAM_STRATEGYFLAG_GIFT_2_TRY + APP_PARAM_STRATEGYFLAG_GIFT_3_TRY + APP_PARAM_STRATEGYFLAG_GIFT_4_TRY);	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy
		case 955:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = 960;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2400;	p->Param3 = 600;	p->Param4 = 180;	break;	// SubStrategyName = MainStrategy
		case 960:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 970;	TimeoutID = 0;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1500;	p->Param3 = 800;	p->Param4 = 180;	break;	// SubStrategyName = MainStrategy
		case 970:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = (APP_PARAM_STRATEGYFLAG_GIFT_1_TRY + APP_PARAM_STRATEGYFLAG_GIFT_2_TRY + APP_PARAM_STRATEGYFLAG_GIFT_3_TRY + APP_PARAM_STRATEGYFLAG_GIFT_4_TRY);	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = MainStrategy

		case 3000:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 3010;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = Depose
		case 3010:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_LEFT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 3020;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateToAngleInDeg;	p->Param1 = DEFAULT_SPEED;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = 180;	break;	// SubStrategyName = Depose
		case 3020:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 3029;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_UP;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Depose
		case 3029:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 3030;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 500;	break;	// SubStrategyName = Depose
		case 3030:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 3040;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Depose
		case 3040:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Depose

		case 4000:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4005;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = Gift
		case 4005:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4015;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_FALSE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift
		case 4015:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4020;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_UP;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift
		case 4020:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4025;	TimeoutID = -1;	p->Cmd = Sensors_SetArmsStatus;	p->Param1 = ARM_CLOSED;	p->Param2 = ARM_FRONT;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift
		case 4025:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4030;	TimeoutID = 4035;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = 40;	p->Param2 = 350;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift
		case 4030:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4035;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift
		case 4035:		p->CmdType = CmdType_NonBlocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 4040;	TimeoutID = -1;	p->Cmd = Sensors_SetArmsStatus;	p->Param1 = ARM_CLOSED;	p->Param2 = ARM_CLOSED;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift
		case 4040:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -200;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Gift

		case 1000:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1010;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = Glass1
		case 1010:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_LONG_REAR);	NextActionID = 1100;	TimeoutID = 1300;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1180;	p->Param3 = 547;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1100:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1110;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_DOWN;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1110:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1120;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 500;	break;	// SubStrategyName = Glass1
		case 1120:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT);	NextActionID = 1130;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = LEFT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = Glass1
		case 1130:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 1140;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1140:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1150;	TimeoutID = 1400;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2300;	p->Param3 = 817;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1150:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 1160;	TimeoutID = 1600;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2720;	p->Param3 = 630;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1160:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 1170;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2500;	p->Param3 = 630;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1170:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1300:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1100;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1400:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 1401;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1401:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1410;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateInDeg;	p->Param1 = DEFAULT_SPEED;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = Glass1
		case 1410:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT);	NextActionID = 1411;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1403;	p->Param3 = 400;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1411:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1160;	TimeoutID = 1500;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2720;	p->Param3 = 630;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1500:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 1501;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -100;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1501:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1502;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_UP;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1502:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1500;	p->Param3 = 1000;	p->Param4 = 0;	break;	// SubStrategyName = Glass1
		case 1600:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 1601;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -300;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass1
		case 1601:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 1610;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateInDeg;	p->Param1 = DEFAULT_SPEED;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = Glass1
		case 1610:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 1411;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1403;	p->Param3 = 400;	p->Param4 = 0;	break;	// SubStrategyName = Glass1

		case 2000:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2010;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 1;	break;	// SubStrategyName = Glass2
		case 2010:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_LONG_REAR);	NextActionID = 2100;	TimeoutID = 2300;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1180;	p->Param3 = 1050;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2100:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2110;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_DOWN;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2110:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2120;	TimeoutID = -1;	p->Cmd = App_Wait;	p->Param1 = 0;	p->Param2 = 0;	p->Param3 = 0;	p->Param4 = 500;	break;	// SubStrategyName = Glass2
		case 2120:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_RIGHT);	NextActionID = 2130;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = RIGHT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = -90;	break;	// SubStrategyName = Glass2
		case 2130:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT);	NextActionID = 2140;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;	p->Param1 = DEFAULT_PIVOT_SPEED;	p->Param2 = LEFT_WHEEL;	p->Param3 = NotUsed;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2140:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 2150;	TimeoutID = 2400;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2720;	p->Param3 = 1200;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2150:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 2160;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2480;	p->Param3 = 1200;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2160:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2300:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 2100;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2400:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 2401;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -150;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2401:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2410;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateInDeg;	p->Param1 = DEFAULT_SPEED;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = 90;	break;	// SubStrategyName = Glass2
		case 2410:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT + APP_PARAM_STRATEGYFLAG_COLLISION_LEFT);	NextActionID = 2411;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1600;	p->Param3 = 550;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2411:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_FRONT);	NextActionID = 2412;	TimeoutID = 2500;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2720;	p->Param3 = 630;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2412:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 2420;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 2500;	p->Param3 = 630;	p->Param4 = 0;	break;	// SubStrategyName = Glass2
		case 2420:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = App_SetStrategyFlags;	p->Param1 = APP_PARAM_STRATEGYFLAG_SUBSTRATEGY_RESULT;	p->Param2 = OS_TRUE;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2500:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_COLLISION_REAR);	NextActionID = 2501;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;	p->Param1 = DEFAULT_SPEED;	p->Param2 = -100;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2501:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 2502;	TimeoutID = -1;	p->Cmd = Sensors_SetHoopLevel;	p->Param1 = HOOP_LEVEL_UP;	p->Param2 = NotUsed;	p->Param3 = NotUsed;	p->Param4 = NotUsed;	break;	// SubStrategyName = Glass2
		case 2502:		p->CmdType = CmdType_Blocking;	p->ActiveSensorsFlag =	(APP_PARAM_STRATEGYFLAG_NONE);	NextActionID = 0;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;	p->Param1 = DEFAULT_SPEED;	p->Param2 = 1500;	p->Param3 = 1000;	p->Param4 = 0;	break;	// SubStrategyName = Glass2

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
