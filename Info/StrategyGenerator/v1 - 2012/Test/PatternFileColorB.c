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

#ifdef 'PATTERN_STRATEGY_NAME'_ENABLED

#define DEFAULT_SPEED ('PATTERN_DEFAULT_SPEED')

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetInitCmd(StructCmd *InitCmd)
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
INT8U StrategyColorA_GetNextAction(StructCmd *NextAction)
{
	static int		NextActionID = 1;
	int			CurrentActionID = 0;
	INT8U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	NextAction->CmdType = CmdType_Blocking;

	// Set CurrentID to NextID
	CurrentActionID = NextActionID;

	// Read Next Action
	switch(CurrentActionID)
	{
		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	NextAction->CmdType = 'PATTERN_CMD_TYPE';		NextAction->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	NextAction->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	
		case 'PATTERN_COUNTER':	
		case 'PATTERN_COUNTER':	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	NextAction->CmdType = 'PATTERN_CMD_TYPE';		NextAction->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	NextAction->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	
		case 'PATTERN_COUNTER':	
		case 'PATTERN_COUNTER':	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 'LOOPID'
		case 'PATTERN_COUNTER':	
		case 'PATTERN_COUNTER':	
		case 'PATTERN_COUNTER':	
		// StructuredFileLoopEnd

		case 0:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
	}


	return ERR__NO_ERROR;
}

#endif
