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

#ifdef MATCH1_STRATEGY_ENABLED

#define DEFAULT_SPEED (60)

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_Blocking;
	InitCmd->Param2				= 2931;	
	InitCmd->Param3				= 1667;	
	InitCmd->Param4				= AppConvertDegInRad(180);
	InitCmd->ActiveSensorsFlag		= APP_PARAM_STRATEGYFLAG_NONE;

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetNextAction(StructCmd *NextAction)
{
	static int		NextActionID = 1;
	static int		TimeoutID = -1;
	int			CurrentActionID = 0;
	INT8U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;
	OS_FLAGS		StrategyFlagsToSet = 0;
	StructCmd 		*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	p->CmdType = CmdType_Blocking;

	// Set CurrentID 
	CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_ACTION_TIMEOUT, OS_FLAG_WAIT_SET_ANY, &Err);
	if(((CurrentFlag & APP_PARAM_APPFLAG_ACTION_TIMEOUT) == APP_PARAM_APPFLAG_ACTION_TIMEOUT) && (TimeoutID != -1))
		CurrentActionID = TimeoutID;
	else
		CurrentActionID = NextActionID;

	// Read Next Action
	switch(CurrentActionID)
	{
		// StructuredFileLoopBegin
		// LoopID = 0
		case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 2;	TimeoutID = -1; p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 600;    		break;	
		case 2:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 3;	TimeoutID = -1; p->Cmd = Sensors_ArmsDeployment;				break;	
		case 3:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 100;	TimeoutID = -1; p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 1660;    p->Param4 = -90;    		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 1
		case 100:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 101;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
		case 101:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 102;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
		case 102:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 103;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
		case 103:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 104;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
		case 104:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 105;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
		case 105:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 106;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -140;    		break;	
		case 106:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 107;	p->Cmd = Sensors_ArmsOpenUp;				break;	
		case 107:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 108;	p->Cmd = Sensors_ArmsOpenDown;				break;	
		case 108:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 109;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -40;    		break;	
		case 109:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 110;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    		break;	
		case 110:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 111;	p->Cmd = Sensors_ArmsClose;				break;	
		case 111:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 112;	p->Cmd = Sensors_ArmsOpenDown;				break;	
		case 112:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 113;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2541;    p->Param3 = 1138;    p->Param4 = -25;    		break;	
		case 113:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 114;	p->Cmd = Sensors_ArmsUngrab;				break;	
		case 114:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 115;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -50;    		break;	
		case 115:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 116;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -310;    		break;	
		case 116:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 200;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 2
		case 200:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 201;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2350;    p->Param3 = 730;    p->Param4 = -90;    		break;	
		case 201:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 202;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2270;    p->Param3 = 410;    p->Param4 = 90;    		break;	
		case 202:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 203;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -350;    		break;	
		case 203:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 204;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
		case 204:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 300;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 340;    p->Param4 = 90;    		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 3
		case 300:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 301;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
		case 301:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 302;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
		case 302:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 303;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
		case 303:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 304;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
		case 304:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 305;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
		case 305:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 306;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -180;    		break;	
		case 306:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 307;	p->Cmd = Sensors_ArmsOpenUp;				break;	
		case 307:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 308;	p->Cmd = Sensors_ArmsOpenDown;				break;	
		case 308:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 309;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 40;    		break;	
		case 309:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 310;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = LEFT_WHEEL;    p->Param4 = 40;    		break;	
		case 310:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 311;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    		break;	
		case 311:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 312;	p->Cmd = Sensors_ArmsClose;				break;	
		case 312:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 313;	p->Cmd = Sensors_ArmsOpenDown;				break;	
		case 313:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2491;    p->Param3 = 1008;    p->Param4 = 20;    		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 4
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 5
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 6
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 7
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 8
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 9
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 10
		// StructuredFileLoopEnd

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

		if((CurrentFlag & (p->Param1)) != 0)
			NextActionID = (int)(p->Param2);
		else
			NextActionID = (int)(p->Param3);

		return StrategyColorA_GetNextAction(p);
	}
	
	// Check for conditionnal strategy command ---------------------------
	if(App_IfGoto_System == p->Cmd)
	{
		// Read the current Flags
		CurrentFlag = OSFlagAccept(AppStrategyFlags, APP_PARAM_STRATEGYFLAG_ALL, OS_FLAG_WAIT_SET_ANY, &Err);

		if((CurrentFlag & (p->Param1)) != 0)
			NextActionID = (int)(p->Param2);
		else
			NextActionID = (int)(p->Param3);

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
	}
	
	// Create the MvtSimple Command --------------------------------------
	if(MvtSimple_MoveInMM == p->Cmd) 
		LibMoving_MoveInMM(p->Param2, p->Param1, p);

	if(MvtSimple_RotateInDeg == p->Cmd)
		LibMoving_RotateInDeg(p->Param4, p->Param1, p);
	
	if(MvtSimple_RotateToAngleInDeg == p->Cmd)
		LibMoving_RotateToAngleInDeg(p->Param4, p->Param1, p);

	// Angle Conversion --------------------------------------------------
	if((Mvt_UsePivotMode == p->Cmd) || (Mvt_UseMixedMode == p->Cmd))
	{
		p->Param4 = AppConvertDegInRad(p->Param4);
	}



	return ERR__NO_ERROR;
}

#endif
