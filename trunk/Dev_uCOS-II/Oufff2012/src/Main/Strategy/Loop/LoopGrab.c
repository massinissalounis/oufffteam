// Fichier de sauvegarde des loops

PATTERN_STRATEGY_NAME = (GRAB)
PATTERN_DEFAULT_SPEED = (60)

// Valeur d'init ----------------------------------------------------
PATTERN_INIT_CMD = (App_SetNewPos)
PATTERN_INIT_CMD_TYPE = (CmdType_Blocking)
PATTERN_INIT_POS_X = (2935)
PATTERN_INIT_POS_Y = (1667)
PATTERN_INIT_POS_ANGLE = (180)
PATTERN_INIT_ACTIVE_SENSORS = (APP_PARAM_APPFLAG_NONE)

// StructuredFileLoopBegin
// LoopID = 0
case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 2;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 600;    		break;	
case 2:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 3;	p->Cmd = Sensors_ArmsDeployment;				break;	
case 3:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 100;	p->Cmd = Mvt_UseMixedMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 1904;    p->Param3 = 1660;    p->Param4 = -90;    		break;	
// StructuredFileLoopEnd

// StructuredFileLoopBegin
// LoopID = 1
case 100:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 101;	p->Cmd = Sensors_ArmsOpenOneCD;				break;	
case 101:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 102;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 130;    		break;	
case 102:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 103;	p->Cmd = Sensors_ArmsOpenTotem;				break;	
case 103:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 104;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 150;    		break;	
case 104:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 105;	p->Cmd = Sensors_ArmsCloseTotem;				break;	
case 105:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 106;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -120;    		break;	
case 106:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 107;	p->Cmd = Sensors_ArmsOpen;				break;	
case 107:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 108;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = RIGHT_WHEEL;    p->Param4 = -45;    		break;	
case 108:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 109;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 550;    		break;	
case 109:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 110;	p->Cmd = Sensors_ArmsClose;				break;	
case 110:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 111;	p->Cmd = Mvt_UsePivotMode;		p->Param1 = DEFAULT_SPEED;    p->Param2 = LEFT_WHEEL;    p->Param4 = -10;    		break;	
case 111:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 112;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = 210;    		break;	
case 112:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 113;	p->Cmd = Sensors_ArmsUngrab;				break;	
case 113:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 114;	p->Cmd = MvtSimple_MoveInMM;		p->Param1 = DEFAULT_SPEED;    p->Param2 = -250;    		break;	
case 114:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = -1;	p->Cmd = Sensors_ArmsOpen;				break;	
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
