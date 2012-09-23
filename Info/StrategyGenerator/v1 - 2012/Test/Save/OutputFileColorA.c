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

#ifdef TEST_ENABLED

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorA_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_NonBlocking;
	InitCmd->Param2				= 1;	InitCmd->Param3				= 2;	InitCmd->Param4				= AppConvertDegInRad(3);
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
		// StructuredFileLoopBegin
		// LoopID = 2
		case 200:	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 1;	NextAction->Cmd = Mvt_UseAngleOnly;		NextAction->Param1 = 1;    NextAction->Param4 = 4;    		break;	
		case 201:	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 2;	NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 1;    NextAction->Param2 = 2;    NextAction->Param3 = 3;    NextAction->Param4 = 4;    		break;	
		case 202:	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 3;	NextAction->Cmd = Mvt_Stop;				break;	
		case 204:	NextAction->CmdType = CmdType_NonBlocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 200;	NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 1;    NextAction->Param2 = 2;    NextAction->Param3 = 3;    NextAction->Param4 = 4;    		break;	
		case 205:	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 301;	NextAction->Cmd = App_Wait;		NextAction->Param1 = 1;    NextAction->Param2 = 2;    NextAction->Param3 = 3;    NextAction->Param4 = 4;    		break;	
		case 210:	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 400;	NextAction->Cmd = App_Wait;		NextAction->Param1 = 1;    NextAction->Param2 = 2;    NextAction->Param3 = 3;    NextAction->Param4 = 4;    		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 3
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 4
		// StructuredFileLoopEnd

		case 0:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
	}


	return ERR__NO_ERROR;
}

#endif
