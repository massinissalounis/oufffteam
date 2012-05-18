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
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 2
case 250:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 208;	TimeoutID = 225;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 345;    p->Param4 = 90;    		break;	
case 251:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = -1;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1674;    p->Param3 = 542;    p->Param4 = 0;    		break;	
case 260:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 223;	TimeoutID = 400;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2380;    p->Param3 = 1280;    p->Param4 = -90;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 3
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
