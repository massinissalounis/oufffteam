/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : Fichier de stratégie produit par StrategyGenerator
*
* Suivi de version :
* 2011-06-01 | PBE | Creation de la version de base pour la coupe 2011
* 2011-11-02 | PBE | Mise à jour du fichier pour en faire un fichier pattern pour la couleur A
*********************************************************************************************************
*/

#include "StrategyFromColor.h"

#ifdef 'PATTERN_STRATEGY_NAME'_ENABLED

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_NonBlocking;
	InitCmd->Param2				= 'PATTERN_INIT_POS_X';
	InitCmd->Param3				= 'PATTERN_INIT_POS_Y';
	InitCmd->Param4				= AppConvertDegInRad('PATTERN_INIT_POS_ANGLE');
	InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetNextAction(StructCmd *NextAction)
{
	static int		NextActionID = 1;
	int				CurrentActionID = 0;
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
		case 'PATTERN_COUNTER':	NextAction->CmdType = 'PATTERN_CMD_TYPE';		NextAction->ActiveSensorsFlag =	'PATTERN_ACTIVE_SENSORS_FLAG';	NextActionID = 'PATTERN_NEXT_ACTION_ID';	NextAction->Cmd = 'PATTERN_CMD';		'PATTERN_PARAMS'		break;	

		case 0:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
	}


	return ERR__NO_ERROR;
}

#endif
