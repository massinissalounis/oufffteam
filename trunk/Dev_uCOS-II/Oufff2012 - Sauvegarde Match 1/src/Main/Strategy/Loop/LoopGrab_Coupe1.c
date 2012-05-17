// Fichier de sauvegarde des loops

PATTERN_STRATEGY_NAME = (GRAB_Coupe1)
PATTERN_DEFAULT_SPEED = (50)

// Valeur d'init ----------------------------------------------------
PATTERN_INIT_CMD = (App_SetNewPos)
PATTERN_INIT_CMD_TYPE = (CmdType_Blocking)
PATTERN_INIT_POS_X = (1900)
PATTERN_INIT_POS_Y = (1820)
PATTERN_INIT_POS_ANGLE = (-90)
PATTERN_INIT_ACTIVE_SENSORS = (APP_PARAM_STRATEGYFLAG_NONE)

// StructuredFileLoopBegin
// LoopID = 0
case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 2;	p->Cmd = Sensors_ArmsDeployment;				break;	
case 2:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 300;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 160;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 2
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 3
case 300:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 301;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
case 301:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 302;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
case 302:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 303;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
case 303:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 304;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
case 304:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 305;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
case 305:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 306;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -140;    		break;	
case 306:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 307;	p->Cmd = Sensors_ArmsOpenUp;				break;	
case 307:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 308;	p->Cmd = Sensors_ArmsOpenDown;				break;	
case 308:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 309;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -35;    		break;	
case 309:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 100;    		break;	
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
