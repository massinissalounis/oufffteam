// Fichier de sauvegarde des loops

PATTERN_STRATEGY_NAME = (MATCH2)
PATTERN_DEFAULT_SPEED = (50)

// Valeur d'init ----------------------------------------------------
PATTERN_INIT_CMD = (App_SetNewPos)
PATTERN_INIT_CMD_TYPE = (CmdType_Blocking)
PATTERN_INIT_POS_X = (2931)
PATTERN_INIT_POS_Y = (1667)
PATTERN_INIT_POS_ANGLE = (180)
PATTERN_INIT_ACTIVE_SENSORS = (APP_PARAM_STRATEGYFLAG_NONE)

// StructuredFileLoopBegin
// LoopID = 0
case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 2;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 600;    		break;	
case 2:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 3;	TimeoutID = 1;	p->Cmd = Sensors_ArmsDeployment;				break;	
case 3:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 400;	TimeoutID = 2;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 1660;    p->Param4 = -90;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 2
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 3
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 4
case 400:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 401;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
case 401:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 402;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
case 402:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 403;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
case 403:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 404;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
case 404:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 405;	TimeoutID = -1;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
case 405:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 406;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -140;    		break;	
case 406:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 407;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenUp;				break;	
case 407:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 408;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 408:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 409;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -40;    		break;	
case 409:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 410;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    		break;	
case 410:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 411;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;				break;	
case 411:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 412;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 412:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 413;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2541;    p->Param3 = 1138;    p->Param4 = -25;    		break;	
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
