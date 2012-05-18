// Fichier de sauvegarde des loops

PATTERN_STRATEGY_NAME = (MATCH2)
PATTERN_DEFAULT_SPEED = (50)

// Valeur d'init ----------------------------------------------------
PATTERN_INIT_CMD = (App_SetNewPos)
PATTERN_INIT_CMD_TYPE = (CmdType_Blocking)
PATTERN_INIT_POS_X = (1500)
PATTERN_INIT_POS_Y = (1000)
PATTERN_INIT_POS_ANGLE = (0)
PATTERN_INIT_ACTIVE_SENSORS = (APP_PARAM_STRATEGYFLAG_NONE)

// StructuredFileLoopBegin
// LoopID = 0
case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 150;	TimeoutID = -1;	p->Cmd = App_SetNewPos;		p->Param2 = 2931;    p->Param3 = 1667;    p->Param4 = 180;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
case 150:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 100;	TimeoutID = 150;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2355;    p->Param3 = 1667;    p->Param4 = 180;    		break;	
case 151:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_REAR;	NextActionID = 102;	TimeoutID = 152;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2365;    p->Param3 = 1290;    p->Param4 = 90;    		break;	
case 152:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 106;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2284;    p->Param3 = 472;    p->Param4 = 180;    		break;	
case 153:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_STRATEGYFLAG_COLLISION_FRONT;	NextActionID = 250;	TimeoutID = -1;	p->Cmd = Mvt_UseSpline;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1900;    p->Param3 = 345;    p->Param4 = 90;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 2
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
