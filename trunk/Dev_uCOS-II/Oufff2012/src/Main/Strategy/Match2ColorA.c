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

#ifdef MATCH2_STRATEGY_ENABLED

#define DEFAULT_SPEED (70)

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
		CurrentActionID = TimeoutID;
	else
		CurrentActionID = NextActionID;

	// Read Next Action
	switch(CurrentActionID)
	{
		// StructuredFileLoopBegin
		// LoopID = 0
		case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 100;	TimeoutID = 150;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = 85;    p->Param2 = 576;    	break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 1
		case 100:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 101;	TimeoutID = 151;	p->Cmd = MvtSimple_RotateToAngleInDeg;		p->Param1 = DEFAULT_SPEED;    p->Param4 = 90;    	break;	
		case 101:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 102;	TimeoutID = 151;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = 85;    p->Param2 = -367;    	break;	
		case 102:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 103;	TimeoutID = 151;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = 180;    	break;	
		case 103:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 104;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -250;    	break;	
		case 104:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 105;	TimeoutID = 152;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = 85;    p->Param2 = 2500;    p->Param3 = 1000;    p->Param4 = -125;    	break;	
		case 105:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 106;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = 85;    p->Param2 = 500;    	break;	
		case 106:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 107;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = 85;    p->Param2 = 2260;    p->Param3 = 500;    p->Param4 = 90;    	break;	
		case 107:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 108;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -415;    	break;	
		case 108:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 109;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = 85;    p->Param2 = 200;    	break;	
		case 109:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 200;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = 85;    p->Param2 = 1900;    p->Param3 = 345;    p->Param4 = 90;    	break;	
		case 150:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 100;	TimeoutID = 150;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2355;    p->Param3 = 1667;    p->Param4 = 180;    	break;	
		case 151:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 102;	TimeoutID = 152;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2365;    p->Param3 = 1290;    p->Param4 = 90;    	break;	
		case 152:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 106;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2284;    p->Param3 = 472;    p->Param4 = 180;    	break;	
		case 153:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 250;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 345;    p->Param4 = 90;    	break;	
		case 154:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 300;	TimeoutID = -1;	p->Cmd = Sensors_ArmsDeployment;			break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 2
		case 200:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 200;	TimeoutID = -1;	p->Cmd = App_IfGoto_Strategy;		p->Param1 = (APP_PARAM_STRATEGYFLAG_ARMS_IS_INIT);    p->Param2 = 201;    p->Param3 = 202;    	break;	
		case 201:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 202;	TimeoutID = -1;	p->Cmd = Sensors_ArmsDeployment;			break;	
		case 202:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 203;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenOneCD;			break;	
		case 203:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 204;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    	break;	
		case 204:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 205;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenTotem;			break;	
		case 205:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 206;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    	break;	
		case 206:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 207;	TimeoutID = -1;	p->Cmd = Sensors_ArmsCloseTotem;			break;	
		case 207:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 208;	TimeoutID = 250;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -180;    	break;	
		case 208:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 209;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenUp;			break;	
		case 209:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 210;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;			break;	
		case 210:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 211;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 40;    	break;	
		case 211:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 212;	TimeoutID = 251;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = LEFT_WHEEL;    p->Param4 = 40;    	break;	
		case 212:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 213;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    	break;	
		case 213:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 214;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;			break;	
		case 214:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 215;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;			break;	
		case 215:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 216;	TimeoutID = 251;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2491;    p->Param3 = 1008;    p->Param4 = 0;    	break;	
		case 216:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 217;	TimeoutID = 260;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 100;    	break;	
		case 217:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 218;	TimeoutID = 260;	p->Cmd = Sensors_ArmsOpenUp;			break;	
		case 218:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 219;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -300;    	break;	
		case 219:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 220;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;			break;	
		case 220:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 223;	TimeoutID = 260;	p->Cmd = MvtSimple_RotateToAngleInDeg;		p->Param1 = DEFAULT_SPEED;    p->Param4 = -90;    	break;	
		case 223:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 225;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2360;    p->Param3 = 577;    p->Param4 = 180;    	break;	
		case 225:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 300;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1917;    p->Param3 = 577;    p->Param4 = 180;    	break;	
		case 250:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 208;	TimeoutID = 225;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 345;    p->Param4 = 90;    	break;	
		case 251:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = -1;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1674;    p->Param3 = 542;    p->Param4 = 0;    	break;	
		case 260:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 223;	TimeoutID = 400;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2380;    p->Param3 = 1280;    p->Param4 = -90;    	break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 3
		case 300:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 301;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;			break;	
		case 301:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 303;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1767;    p->Param3 = 577;    p->Param4 = 180;    	break;	
		case 303:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 304;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;			break;	
		case 304:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 318;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 200;    	break;	
		case 318:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 305;	TimeoutID = -1;	p->Cmd = MvtSimple_RotateToAngleInDeg;		p->Param1 = DEFAULT_SPEED;    p->Param4 = -135;    	break;	
		case 305:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 306;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1100;    p->Param3 = 408;    p->Param4 = 90;    	break;	
		case 306:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 307;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -325;    	break;	
		case 307:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 308;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 200;    	break;	
		case 308:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 309;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1500;    p->Param3 = 647;    p->Param4 = 0;    	break;	
		case 309:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 310;	TimeoutID = 350;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1990;    p->Param3 = 647;    p->Param4 = 0;    	break;	
		case 310:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 311;	TimeoutID = 350;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -90;    	break;	
		case 311:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 312;	TimeoutID = 350;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = LEFT_WHEEL;    p->Param4 = -135;    	break;	
		case 312:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 313;	TimeoutID = 350;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -280;    	break;	
		case 313:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 314;	TimeoutID = 350;	p->Cmd = MvtSimple_RotateToAngleInDeg;		p->Param1 = DEFAULT_SPEED;    p->Param4 = -90;    	break;	
		case 314:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 315;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -600;    	break;	
		case 315:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 316;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenUp;			break;	
		case 316:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 317;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -320;    	break;	
		case 317:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 400;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 1600;    p->Param4 = -90;    	break;	
		case 350:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 314;	TimeoutID = 350;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2363;    p->Param3 = 805;    p->Param4 = -90;    	break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 4
		case 400:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 401;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenOneCD;			break;	
		case 401:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 402;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    	break;	
		case 402:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 403;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenTotem;			break;	
		case 403:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 404;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    	break;	
		case 404:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 405;	TimeoutID = -1;	p->Cmd = Sensors_ArmsCloseTotem;			break;	
		case 405:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 406;	TimeoutID = 450;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -140;    	break;	
		case 406:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 407;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenUp;			break;	
		case 407:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 408;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;			break;	
		case 408:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 409;	TimeoutID = 451;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -40;    	break;	
		case 409:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 410;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    	break;	
		case 410:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 411;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;			break;	
		case 411:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 412;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;			break;	
		case 412:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = -1;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2541;    p->Param3 = 1138;    p->Param4 = -25;    	break;	
		case 450:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 406;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1852;    p->Param3 = 1623;    p->Param4 = -40;    	break;	
		case 451:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 452;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;			break;	
		case 452:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = -1;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2400;    p->Param3 = 1658;    p->Param4 = 15;    	break;	
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
	if(App_IfGoto_Strategy == p->Cmd)
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
