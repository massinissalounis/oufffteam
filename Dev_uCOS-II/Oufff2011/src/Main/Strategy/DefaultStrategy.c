/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : DefaultStrategy.c
*
* Suivi de version :
* 2011-05-10 | PBE | Creation de la version de base pour la coupe 2011
*********************************************************************************************************
*/

#include "../Strategy.h"

#ifdef DEFAULT_STRATEGY_ENABLED

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
		InitCmd->Param2				= 200.0;
		InitCmd->Param3				= 200.0;
		InitCmd->Param4				= AppConvertDegInRad(0.0);
		InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
		break;

	case c_ColorB:	// Red ##############################################
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 200.0;
		InitCmd->Param3				= 200.0;
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
	static INT8U CurrentActionID = 0;
	StructCmd *p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	switch(CurrentColor)
	{
	case c_ColorA:	// Blue #############################################################
		switch(CurrentActionID)
		{
		case 0:	LibMoving_MoveInMM(1500, 60, NextAction);	break;
//		case 0:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 400;	NextAction->Param3 = 0;		NextAction->Param4 = AppConvertDegInRad(0.0);	NextAction->CmdType = CmdType_Blocking;		break;		
//		case 1:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 400;	NextAction->Param3 = 400;	NextAction->Param4 = AppConvertDegInRad(90.0);	NextAction->CmdType = CmdType_Blocking;		break;		
//		case 2:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 0;		NextAction->Param3 = 400;	NextAction->Param4 = AppConvertDegInRad(180.0);	NextAction->CmdType = CmdType_Blocking;		break;		
//		case 3:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 0;		NextAction->Param3 = 0;		NextAction->Param4 = AppConvertDegInRad(0.0);	NextAction->CmdType = CmdType_Blocking;		break;		

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

		// Update ActionID
		CurrentActionID++;
	break;

	case c_ColorB:	// Red ##############################################################
		switch(CurrentActionID)
		{
		case 0:	LibMoving_MoveInMM(500, 40, NextAction);	break;
		case 1:	NextAction->Cmd = Sensors_GrabObject;		break;
		case 2:	LibMoving_MoveInMM(500, 40, NextAction);	break;

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

		// Update ActionID
		CurrentActionID++;
	break;

	default:		// Not Set ##########################################################
	break;
	}

	return ERR__NO_ERROR;
}

#endif
