// Fichier de sauvegarde des loops

PATTERN_STRATEGY_NAME = (MATCH1)
PATTERN_DEFAULT_SPEED = (60)

// Valeur d'init ----------------------------------------------------
PATTERN_INIT_CMD = (App_SetNewPos)
PATTERN_INIT_CMD_TYPE = (CmdType_Blocking)
PATTERN_INIT_POS_X = (2931)
PATTERN_INIT_POS_Y = (1667)
PATTERN_INIT_POS_ANGLE = (180)
PATTERN_INIT_ACTIVE_SENSORS = (APP_PARAM_STRATEGYFLAG_NONE)

// StructuredFileLoopBegin
// LoopID = 0
case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 2;	TimeoutID = 0;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 600;    		break;	
case 2:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 3;	TimeoutID = 1;	p->Cmd = Sensors_ArmsDeployment;				break;	
case 3:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 100;	TimeoutID = 2;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 1660;    p->Param4 = -90;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
case 100:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 101;	TimeoutID = 3;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
case 101:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 102;	TimeoutID = 4;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
case 102:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 103;	TimeoutID = 5;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
case 103:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 104;	TimeoutID = 6;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
case 104:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 105;	TimeoutID = 7;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
case 105:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 106;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -140;    		break;	
case 106:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 107;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenUp;				break;	
case 107:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 108;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 108:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 109;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -40;    		break;	
case 109:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 110;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    		break;	
case 110:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 111;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;				break;	
case 111:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 112;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 112:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 113;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2541;    p->Param3 = 1138;    p->Param4 = -25;    		break;	
case 113:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 114;	TimeoutID = -1;	p->Cmd = Sensors_ArmsUngrab;				break;	
case 114:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 115;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -50;    		break;	
case 115:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 116;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -310;    		break;	
case 116:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 200;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 2
case 200:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 201;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2350;    p->Param3 = 730;    p->Param4 = -90;    		break;	
case 201:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 202;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2270;    p->Param3 = 410;    p->Param4 = 90;    		break;	
case 202:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 203;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -350;    		break;	
case 203:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 204;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
case 204:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 300;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 340;    p->Param4 = 90;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 3
case 300:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 301;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
case 301:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 302;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
case 302:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 303;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
case 303:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 304;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
case 304:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 305;	TimeoutID = -1;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
case 305:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 306;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -180;    		break;	
case 306:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 307;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenUp;				break;	
case 307:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 308;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 308:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 309;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 40;    		break;	
case 309:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 310;	TimeoutID = -1;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = LEFT_WHEEL;    p->Param4 = 40;    		break;	
case 310:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 311;	TimeoutID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 300;    		break;	
case 311:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 312;	TimeoutID = -1;	p->Cmd = Sensors_ArmsClose;				break;	
case 312:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 313;	TimeoutID = -1;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 313:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = -1;	TimeoutID = -1;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2491;    p->Param3 = 1008;    p->Param4 = 20;    		break;	
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
