/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : DefaultStrategy.c
*
* Suivi de version :
* 2012-04-29 | PBE | Creation de la version de base pour la coupe 2012
*********************************************************************************************************
*/

#include "../Strategy.h"

#ifdef TEST_STRATEGY_ENABLED

// ------------------------------------------------------------------------------------------------
INT8U Strategy_GetInitCmd(EnumColor CurrentColor, StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	switch(CurrentColor)
	{
	case c_ColorA:	// Red ############################################# 
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 0.0;
		InitCmd->Param3				= 0.0;
		InitCmd->Param4				= AppConvertDegInRad(0.0);
		InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
		break;

	case c_ColorB:	// Purple ##############################################
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 0.0;
		InitCmd->Param3				= 0.0;
		InitCmd->Param4				= AppConvertDegInRad(0.0);
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
	static unsigned int 	CurrentActionID = 0;
	INT8U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;
	StructCmd 		*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	NextAction->CmdType = CmdType_Blocking;

	switch(CurrentColor)
	{
	case c_ColorA:	// Rouge #############################################################
	case c_ColorB:	// Violet ##############################################################
		switch(CurrentActionID)
		{
		case 0:		NextAction->Cmd = MvtSimple_MoveInMM;		LibMoving_MoveInMM(500, APP_TEST_ROBOT_SPEED, NextAction);			CurrentActionID++;	break;
		case 1:		NextAction->Cmd = MvtSimple_RotateInDeg;	LibMoving_RotateInDeg(90, APP_TEST_ROBOT_SPEED, NextAction);		CurrentActionID++;	break;

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	default:		// Not Set ##########################################################
	break;
	}

	return ERR__NO_ERROR;
}

#endif
