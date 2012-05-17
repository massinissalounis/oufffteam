// Fichier de sauvegarde des loops

PATTERN_STRATEGY_NAME = (HOMOL)
PATTERN_DEFAULT_SPEED = (70)

// Valeur d'init ----------------------------------------------------
PATTERN_INIT_CMD = (App_SetNewPos)
PATTERN_INIT_CMD_TYPE = (CmdType_Blocking)
PATTERN_INIT_POS_X = (2935)
PATTERN_INIT_POS_Y = (1667)
PATTERN_INIT_POS_ANGLE = (180)
PATTERN_INIT_ACTIVE_SENSORS = (APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE)

// StructuredFileLoopBegin
// LoopID = 0
case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 100;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 580;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
case 100:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 101;	p->Cmd = MvtSimple_RotateToAngleInDeg;		p->Param1 = DEFAULT_SPEED;    p->Param4 = 90;    		break;	
case 101:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 102;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -367;    		break;	
case 102:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 103;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = 180;    		break;	
case 103:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 104;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -250;    		break;	
case 104:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 105;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2500;    p->Param3 = 1000;    p->Param4 = -125;    		break;	
case 105:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 106;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 500;    		break;	
case 106:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 107;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 2260;    p->Param3 = 500;    p->Param4 = 90;    		break;	
case 107:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = 108;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -425;    		break;	
case 108:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APP_PARAM_STRATEGYFLAG_NONE;	NextActionID = -1;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 200;    		break;	
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
