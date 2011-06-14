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
		InitCmd->Param2				= 065.0;
		InitCmd->Param3				= 233.0;
		InitCmd->Param4				= AppConvertDegInRad(0.0);
		InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
		break;

	case c_ColorB:	// Red ##############################################
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 1000.0;
		InitCmd->Param3				= 1000.0;
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
	case c_ColorA:	// Blue #############################################################
		switch(CurrentActionID)
		{
//		case 0:									NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;					CurrentActionID++;	break;
//		case 1:		OSTimeDlyHMSM(0, 0, 1, 0); 	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN_RIGHT_ONLY;		CurrentActionID++;	break;
//		case 2:		OSTimeDlyHMSM(0, 0, 1, 0); 	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN_LEFT_ONLY;			CurrentActionID++;	break;
//		case 3:		OSTimeDlyHMSM(0, 0, 1, 0); 	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;					CurrentActionID++;	break;
//		case 4:		OSTimeDlyHMSM(0, 0, 1, 0); 	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;					CurrentActionID++;	break;

//		case 0:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 400;	NextAction->Param3 = 0;		NextAction->Param4 = AppConvertDegInRad(0.0);	NextAction->CmdType = CmdType_Blocking;		break;		
//		case 1:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 400;	NextAction->Param3 = 400;	NextAction->Param4 = AppConvertDegInRad(90.0);	NextAction->CmdType = CmdType_Blocking;		break;		
//		case 2:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 0;		NextAction->Param3 = 400;	NextAction->Param4 = AppConvertDegInRad(180.0);	NextAction->CmdType = CmdType_Blocking;		break;		
//		case 3:		NextAction->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = 50;	NextAction->Param2 = 0;		NextAction->Param3 = 0;		NextAction->Param4 = AppConvertDegInRad(0.0);	NextAction->CmdType = CmdType_Blocking;		break;		

		case 0:		NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(450, APP_HOMOL_ROBOT_SPEED, NextAction);														CurrentActionID++;	break;
		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN_RIGHT_ONLY;																	CurrentActionID++;	break;
		case 2:		NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(30, APP_HOMOL_ROBOT_SPEED, NextAction);													CurrentActionID++;	break;
		case 3:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;																				CurrentActionID++;	break;
		case 4:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 700;	NextAction->Param3 = 310;		NextAction->Param4 = AppConvertDegInRad(45.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
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
			CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
			if(CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER == APP_PARAM_APPFLAG_GP2_HOLDER)
				CurrentActionID = 200;
			else
				CurrentActionID = 8;
			break;		
		case 8:		NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 9:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 10:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;	NextAction->Param3 = 1750;		NextAction->Param4 = AppConvertDegInRad(135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 11:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 12:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-500, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID = 255;	break;

		// Sub strategy 1
		case 100:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 101:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(90, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 102:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 729.4;	NextAction->Param3 = 420.6;		NextAction->Param4 = AppConvertDegInRad(135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 103:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 104:	NextAction->Cmd = Mvt_Simple;					NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 800;	NextAction->Param3 = 350;		NextAction->Param4 = USE_CURRENT_VALUE;			NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;			CurrentActionID++;	break;	
		case 105:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_CLOSE;				CurrentActionID++;	break;
		case 106:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveToAngleInDeg(0, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 107:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID = 6;	break;

		// Sub strategy 2
		case 200:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_GRAB;				CurrentActionID++;	break;
		case 201:	NextAction->Cmd = Mvt_Simple;					LibMoving_RotateInDeg(-45, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 202:	NextAction->Cmd = Mvt_UseMixedMode;				NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1576.6;	NextAction->Param3 = 279.4;		NextAction->Param4 = AppConvertDegInRad(135.0);	NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		CurrentActionID++;	break;	
		case 203:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 204:	NextAction->Cmd = Mvt_Simple;					NextAction->Param1 = APP_HOMOL_ROBOT_SPEED;		NextAction->Param2 = 1500;		NextAction->Param3 = 350;		NextAction->Param4 = USE_CURRENT_VALUE;			NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;			CurrentActionID = 8;	break;	
		case 205:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_CLOSE;				CurrentActionID++;	break;
		case 206:	NextAction->Cmd = Mvt_Simple;					LibMoving_MoveToAngleInDeg(90, APP_HOMOL_ROBOT_SPEED, NextAction);												CurrentActionID++;	break;
		case 207:	NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID = 8;	break;

		case 255:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

		// Update ActionID
		// CurrentActionID++;
	break;

	case c_ColorB:	// Red ##############################################################
		switch(CurrentActionID)
		{
//		case 0:		NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(450, APP_HOMOL_ROBOT_SPEED, NextAction);														CurrentActionID++;	break;
//		case 1:		NextAction->Cmd = Mvt_Simple;					LibMoving_MoveInMM(-450, APP_HOMOL_ROBOT_SPEED, NextAction);														CurrentActionID++;	break;
//		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;																				CurrentActionID++;	break;
//		case 0:		NextAction->Cmd = App_SetNewPos;	NextAction->CmdType = CmdType_NonBlocking;	NextAction->Param2 = 1500.0;		NextAction->Param3 = 1400.0;		NextAction->Param4 = AppConvertDegInRad(90.0);	NextAction->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE; 	CurrentActionID++;	 break;
//		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		NextAction->Param1 = HOLDER_OPEN;				CurrentActionID++;	break;
		case 0:		NextAction->Cmd = App_SetNewPos;				NextAction->CmdType = CmdType_NonBlocking;	NextAction->Param2 = 1875.0;		NextAction->Param3 = 1575.0;		NextAction->Param4 = AppConvertDegInRad(0.0);	NextAction->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE; 	CurrentActionID++;	 break;
		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;
					NextAction->Param1 = HOLDER_GRAB;
					CurrentActionID=1201;
					break;	

		case 1200:	NextAction->Cmd = Mvt_Simple;
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED; NextAction->Param2 = 1675; NextAction->Param3 = 1575; NextAction->Param4 = AppConvertDegInRad(0.0);
					NextAction->CmdType = CmdType_Blocking;
					NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_BACK_SENSORS;
					CurrentActionID++;
					break;

		case 1201:	NextAction->Cmd = Mvt_Simple;
					LibMoving_MoveToAngleInDeg(-90, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;
					break;

		case 1202:	NextAction->Cmd = Mvt_Simple;
					LibMoving_MoveToAngleInDeg(-180, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;
					break;
					
		case 1203:	NextAction->Cmd = Sensors_SetHolderStatus;
					NextAction->Param1 = HOLDER_GRIP;
					CurrentActionID++;
					break;
					
		case 1204: 	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID++;	
					break;
					
		case 1205:	NextAction->Cmd = Mvt_UseMixedMode;
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED; NextAction->Param2 = 1675; NextAction->Param3 = 1750; NextAction->Param4 = AppConvertDegInRad(90.0);
					NextAction->CmdType = CmdType_Blocking;
					NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;
					CurrentActionID++;
					break;
					
		case 1206:	NextAction->Cmd = Sensors_SetHolderStatus;
					NextAction->Param1 = HOLDER_OPEN;
					CurrentActionID++;
					break;


//		case 1:		NextAction->Cmd = Sensors_SetHolderLevel;		NextAction->Param1 = HOLDER_LEVEL_HIGH;				CurrentActionID++;	break;

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

		// Update ActionID
		//CurrentActionID++;
	break;

	default:		// Not Set ##########################################################
	break;
	}

	return ERR__NO_ERROR;
}

#endif
