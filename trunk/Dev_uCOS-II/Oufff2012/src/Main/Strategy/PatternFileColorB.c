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

#ifdef 'PATTERN_STRATEGY_NAME'_STRATEGY_ENABLED

#define DEFAULT_SPEED ('PATTERN_DEFAULT_SPEED')

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= 'PATTERN_INIT_CMD';
	InitCmd->CmdType			= 'PATTERN_INIT_CMD_TYPE';
	InitCmd->Param2				= 'PATTERN_INIT_POS_X';	
	InitCmd->Param3				= 'PATTERN_INIT_POS_Y';	
	InitCmd->Param4				= AppConvertDegInRad('PATTERN_INIT_POS_ANGLE');
	InitCmd->ActiveSensorsFlag		= 'PATTERN_INIT_ACTIVE_SENSORS';

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetNextAction(StructCmd *NextAction)
{
	static int		NextActionID = 1;
	int			CurrentActionID = 0;
	INT8U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;
	StructCmd 		*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	p->CmdType = CmdType_Blocking;

	// Set CurrentID to NextID
	CurrentActionID = NextActionID;

	// Read Next Action
	switch(CurrentActionID)
	{
		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	p->CmdType = 'PATTERN_CMD_TYPE';		p->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	p->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
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
		return StrategyColorB_GetNextAction(p);
	}

	// Check for conditionnal command ------------------------------------
	if(App_IfGoto == p->Cmd)
	{
		// Read the current Flags
		CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_WAIT_SET_ANY, &Err);

		if((CurrentFlag & (p->Param1)) != 0)
			CurrentActionID = (int)(p->Param2);
		else
			CurrentActionID = (int)(p->Param3);

		return StrategyColorB_GetNextAction(p);
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