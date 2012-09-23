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
		case 0:		NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(450, APP_HOMOL_ROBOT_SPEED, NextAction);														CurrentActionID++;	break;
		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN_RIGHT_ONLY;																	CurrentActionID++;	break;
		case 2:		NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(30, APP_HOMOL_ROBOT_SPEED, NextAction);													CurrentActionID++;	break;
		case 3:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;																				CurrentActionID++;	break;
		case 4:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 800;	NextAction->Param3 = 350;		NextAction->Param4 = AppConvertDegInRad(45.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
// For debug on Oufff TEAM playing corner
//		case 4:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 700;	NextAction->Param3 = 310;		NextAction->Param4 = AppConvertDegInRad(45.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 5:		// Select next action from flags
			NextAction->Cmd = Cmd_NotSet;
			OSTimeDlyHMSM(0, 0, 0, 100); 
			CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
			if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
				CurrentActionID = 100;
			else
				CurrentActionID = 6;
			break;
		case 6:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 350;		NextAction->Param4 = AppConvertDegInRad(0.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 7:		// Select next action from flags
			NextAction->Cmd = Cmd_NotSet;
			OSTimeDlyHMSM(0, 0, 0, 100); 
			CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
			if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
				CurrentActionID = 200;
			else
				CurrentActionID = 8;
			break;		
		case 8:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 9:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 10:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 1750;		NextAction->Param4 = AppConvertDegInRad(135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 11:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 12:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-500, APP_HOMOL_ROBOT_SPEED, NextAction);													CurrentActionID = 255;	break;

		// Sub strategy 1
		case 100:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 101:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(90, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 102:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 729.4;	NextAction->Param3 = 420.6;		NextAction->Param4 = AppConvertDegInRad(135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 103:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 104:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-200, APP_HOMOL_ROBOT_SPEED, NextAction);			NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;			CurrentActionID++;	break;	
		case 105:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_CLOSE;				CurrentActionID++;	break;
		case 106:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateToAngleInDeg(0, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 107:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID = 6;	break;

		// Sub strategy 2
		case 200:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 201:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(-45, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 202:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1576.6;	NextAction->Param3 = 279.4;		NextAction->Param4 = AppConvertDegInRad(-45.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 203:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 204:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-200, APP_HOMOL_ROBOT_SPEED, NextAction);			NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;			CurrentActionID++;	break;	
		case 205:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_CLOSE;				CurrentActionID++;	break;
		case 206:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateToAngleInDeg(90, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 207:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID = 8;	break;

		case 255:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	case c_ColorB:	// Red ##############################################################
		switch(CurrentActionID)
		{
		case 0:		NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(450, APP_HOMOL_ROBOT_SPEED, NextAction);														CurrentActionID++;	break;
		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN_LEFT_ONLY;					CurrentActionID++;	break;
		case 2:		NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(-30, APP_HOMOL_ROBOT_SPEED, NextAction);													CurrentActionID++;	break;
		case 3:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;								CurrentActionID++;	break;
		case 4:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 2200;	NextAction->Param3 = 350;		NextAction->Param4 = AppConvertDegInRad(135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 5:		// Select next action from flags
			NextAction->Cmd = Cmd_NotSet;
			CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
			if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
				CurrentActionID = 100;
			else
				CurrentActionID = 6;
			break;
		case 6:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 350;		NextAction->Param4 = AppConvertDegInRad(180.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 7:		// Select next action from flags
			NextAction->Cmd = Cmd_NotSet;
			CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
			if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
				CurrentActionID = 200;
			else
				CurrentActionID = 8;
			break;		
		case 8:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 9:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 10:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 1750;		NextAction->Param4 = AppConvertDegInRad(45.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 11:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 12:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-500, APP_HOMOL_ROBOT_SPEED, NextAction);													CurrentActionID = 255;	break;

		// Sub strategy 1
		case 100:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 101:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(-90, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 102:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 2270.6;	NextAction->Param3 = 420.6;		NextAction->Param4 = AppConvertDegInRad(45.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 103:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 104:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-200, APP_HOMOL_ROBOT_SPEED, NextAction);			NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;			CurrentActionID++;	break;	
		case 105:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_CLOSE;				CurrentActionID++;	break;
		case 106:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateToAngleInDeg(180, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 107:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID = 6;	break;

		// Sub strategy 2
		case 200:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 201:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(45, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 202:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1429.4;	NextAction->Param3 = 279.4;		NextAction->Param4 = AppConvertDegInRad(-135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 203:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 204:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-200, APP_HOMOL_ROBOT_SPEED, NextAction);			NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;			CurrentActionID++;	break;	
		case 205:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_CLOSE;				CurrentActionID++;	break;
		case 206:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateToAngleInDeg(90, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 207:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID = 8;	break;

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
