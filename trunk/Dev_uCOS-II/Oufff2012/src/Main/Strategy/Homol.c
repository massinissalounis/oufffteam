/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : Homol.c
*
* Suivi de version :
* 2011-06-01 | PBE | Creation de la version de base pour la coupe 2011
*********************************************************************************************************
*/

#include "../Strategy.h"

#ifdef HOMOL_STRATEGY_ENABLED

// ------------------------------------------------------------------------------------------------
INT8U Strategy_GetInitCmd(EnumColor CurrentColor, StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	switch(CurrentColor)
	{
	case c_ColorA:	// Blue ############################################# 
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 065.0;
		InitCmd->Param3				= 233.0;
		InitCmd->Param4				= AppConvertDegInRad(0.0);
		InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
		break;

	case c_ColorB:	// Red ##############################################
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 2935.0;
		InitCmd->Param3				= 233.0;
		InitCmd->Param4				= AppConvertDegInRad(180.0);
		InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
		break;

	default:		// ##################################################
		InitCmd = NULL;
		return ERR__INVALID_PARAM;
		break;
	}

	return ERR__NO_ERROR;
}



// ------------------------------------------------------------------------------------------------
INT8U Strategy_GetNextAction(EnumColor CurrentColor, StructCmd *NextAction)
{
	static INT16U	CurrentActionID = 0;
	INT16U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;
	StructCmd		*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	NextAction->CmdType = CmdType_Blocking;

	switch(CurrentColor)
	{
	case c_ColorA:	// Blue #############################################################
		switch(CurrentActionID)
		{
		case 255:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	case c_ColorB:	// Red ##############################################################
		switch(CurrentActionID)
		{
		case 255:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	default:		// Not Set ##########################################################
	break;
	}

	// ToDo2012 : Faire la verification des commandes MvtSimple_... et calculer à ce moment les positions

	// Todo2012 : Faire la verification de la commande App_Wait et effectuer l'attente (Action non bloquante).

	// Todo2012 : Faire la verification de la commande App_IfGoto et mettre à jour CurrentActionID en fonction

	return ERR__NO_ERROR;
}

#endif
