/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : Homol.c
*
* Suivi de version :
* 2011-06-02 | PBE | Creation de la version de base pour la coupe 2011
*********************************************************************************************************
*/

#include "../Strategy.h"

#ifdef STRATEGY_1_ENABLED

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
	static unsigned int		CurrentActionID = 0;
	static INT8U			NbObjectFoundInLine1 = 0; 
	INT8U 					Err = 0;
	OS_FLAGS				CurrentFlag = 0;
	StructCmd				*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	NextAction->CmdType = CmdType_Blocking;


	// Use this method for naming pawns
	// |----------|----------|----------|----------|----------|----------|
	// |                         Pawns                        |Start Red | <-|
	// |----------|----------|----------|----------|----------|----------|   |
	// |XXXX      |          |          |          |          |          |   | 
	// |----------|----------4----------3----------2----------1----------|   | Red area
	// |XXXX      |          | Bonus B  |          |  Bonus B |          |   |
	// |----------|----------5----------6----------7----------8----------|   | 
	// | Bonus R  |          |          |          |          |          | <-|
	// |----------|----------|----------|----------|----------|----------|
	// | Bonus B  |          |          |          |          |          | <-|
	// |----------|----------5----------6----------7----------8----------|   |
	// |XXXX      |          | Bonus R  |          | Bonus R  |          |   |
	// |----------|----------4----------3----------2----------1----------|   | Blue area
	// |XXXX      |          |          |          |          |          |   |
	// |----------|----------|----------|----------|----------|----------|   |
	// |                         Pawns                        |Start Blue| <-|
	// |----------|----------|----------|----------|----------|----------|



	switch(CurrentColor)
	{
	case c_ColorA:	// Blue #############################################################
		switch(CurrentActionID)
		{
		// Start sequence ---------------------------------------------------------------------------------------------------------------------------
		case 0:		NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(450, APP_DEFAULT_ROBOT_SPEED, NextAction);														
					CurrentActionID++;	
					break;

		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN_RIGHT_ONLY;																	
					CurrentActionID++;	
					break;

		case 2:		NextAction->Cmd = Mvt_Simple;					
					LibMoving_RotateInDeg(30, APP_DEFAULT_ROBOT_SPEED, NextAction);													
					CurrentActionID++;	
					break;

		case 3:		NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;																				
					CurrentActionID++;	
					break;

		case 4:		NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 800;	NextAction->Param3 = 350;		NextAction->Param4 = AppConvertDegInRad(45.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		
					CurrentActionID++;	
					break;	

		// Check for the first pawn (Pawn B1) -------------------------------------------------------------------------------------------------------
		case 5:		// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 100;
					else
						CurrentActionID = 6;
					break;

		// Check for the second pawn (Pawn B2) ------------------------------------------------------------------------------------------------------
		case 6:		NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID++;	
					break;

		case 7:		NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(90, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 8:		NextAction->Cmd = Sensors_SetHolderLevel;	
					NextAction->Param1 = HOLDER_LEVEL_LOW;				
					CurrentActionID++;	
					break;

		case 9:		NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 800;	NextAction->Param3 = 525;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		
					CurrentActionID++;	
					break;	

		case 10:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
					{
						if(NbObjectFoundInLine1 == 0)
							CurrentActionID = 11;
						else
							CurrentActionID = 202;
					}
					else
					{
						CurrentActionID = 300;
					}
					break;

		case 11:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 12:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(-180, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 13:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 876.6;		NextAction->Param3 = 279.4;		NextAction->Param4 = AppConvertDegInRad(-45.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		
					CurrentActionID++;	
					break;	

		case 14:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;																				
					CurrentActionID++;	
					break;

		case 15:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-200, APP_DEFAULT_ROBOT_SPEED, NextAction);
					NbObjectFoundInLine1 = 1;														
					CurrentActionID = 200;	
					break;

		// Manage the first object ------------------------------------------------------------------------------------------------------------------
		case 100:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 101:	NextAction->Cmd = Mvt_UsePivotMode;
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = LEFT_WHEEL;		NextAction->Param4 = AppConvertDegInRad(00.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;		
					CurrentActionID++;	
					break;	
					
		case 102:	NextAction->Cmd = Mvt_UsePivotMode;
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = RIGHT_WHEEL;		NextAction->Param4 = AppConvertDegInRad(-45.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;		
					CurrentActionID++;	
					break;	

		case 103:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 104:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-100, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;	
					break;

		case 105:	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID++;	
					break;

		case 106:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(67, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 107:	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_LOW;				
					CurrentActionID++;	
					break;
							
		case 108:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 800;		NextAction->Param3 = 700;		NextAction->Param4 = AppConvertDegInRad(45.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					NbObjectFoundInLine1 = 1;
					CurrentActionID = 10;	
					break;	
		
		// Manage the fourth object -----------------------------------------------------------------------------------------------------------------
		case 200:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 800;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;	

		case 201:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						if(NbObjectFoundInLine1 == 0)
							CurrentActionID = 302;
						else
							CurrentActionID = 202;
					else
						CurrentActionID = 600;
					break;

		case 202:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 203:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 680;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;

		case 204:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 680;		NextAction->Param3 = 1765;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;	

		case 205:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 206:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-275, APP_DEFAULT_ROBOT_SPEED, NextAction);
					NbObjectFoundInLine1 = 2;
					CurrentActionID = 400;	
					break;

		// Manage the third pawn --------------------------------------------------------------------------------------------------------------------
		case 300:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 800;		NextAction->Param3 = 900;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;	
		
		case 301:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
					{
						if(NbObjectFoundInLine1 == 0)
							CurrentActionID = 302;
						else
							CurrentActionID = 202;
					}
					else
					{
						CurrentActionID = 200;
					}
					break;

		case 302:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 303:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(-90, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 304:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 800;		NextAction->Param3 = 525;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					NbObjectFoundInLine1 = 1;
					CurrentActionID = 13;
					break;	

		// Check one pawn from line 2 (pawn 5) ------------------------------------------------------------------------------------------------------
		case 400:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1150;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(0.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 401:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 402;
					break;

		case 402:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1150;		NextAction->Param3 = 1050;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 403:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 404;
					break;

		case 404:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1150;		NextAction->Param3 = 700;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 405:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 406;
					break;

		case 406:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1150;		NextAction->Param3 = 400;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 407:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 408;
					break;

		case 408:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1150;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID = 505;
					break;

		// Manage object found on line 2 ------------------------------------------------------------------------------------------------------------
		case 500:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 501:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1380;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 502:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1380;		NextAction->Param3 = 1742;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 503:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 504:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-350, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 505:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1380;		NextAction->Param3 = 1225;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 506:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1700;		NextAction->Param3 = 850;		NextAction->Param4 = AppConvertDegInRad(-45.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 507:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 508:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-35, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 509:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(-135, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 510:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-750, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 511:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 512:	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID = 999;	
					break;

		// Manage the last pawns -------------------------------------------------------------------------------------------------------------------
		case 600:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(275, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;	
					break;

		case 601:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					NbObjectFoundInLine1 = 2;
					break;

		case 602:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-275, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;	
					break;

		case 603:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 203;
					else
						CurrentActionID = 400;
					break;


		case 999:
		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	case c_ColorB:	// Red ##############################################################
		switch(CurrentActionID)
		{
		// Start sequence ---------------------------------------------------------------------------------------------------------------------------
		case 0:		NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(450, APP_DEFAULT_ROBOT_SPEED, NextAction);														
					CurrentActionID++;	
					break;

		case 1:		NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN_LEFT_ONLY;																	
					CurrentActionID++;	
					break;

		case 2:		NextAction->Cmd = Mvt_Simple;					
					LibMoving_RotateInDeg(-30, APP_DEFAULT_ROBOT_SPEED, NextAction);													
					CurrentActionID++;	
					break;

		case 3:		NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;																				
					CurrentActionID++;	
					break;

		case 4:		NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;	NextAction->Param3 = 350;		NextAction->Param4 = AppConvertDegInRad(135.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		
					CurrentActionID++;	
					break;	

		// Check for the first pawn (Pawn B1) -------------------------------------------------------------------------------------------------------
		case 5:		// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 100;
					else
						CurrentActionID = 6;
					break;

		// Check for the second pawn (Pawn B2) ------------------------------------------------------------------------------------------------------
		case 6:		NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID++;	
					break;

		case 7:		NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(90, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 8:		NextAction->Cmd = Sensors_SetHolderLevel;	
					NextAction->Param1 = HOLDER_LEVEL_LOW;				
					CurrentActionID++;	
					break;

		case 9:		NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;	NextAction->Param3 = 600;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		
					CurrentActionID++;	
					break;	

		case 10:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
					{
						if(NbObjectFoundInLine1 == 0)
							CurrentActionID = 11;
						else
							CurrentActionID = 202;
					}
					else
					{
						CurrentActionID = 300;
					}
					break;

		case 11:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 12:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(180, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 13:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2129.4;		NextAction->Param3 = 279.4;		NextAction->Param4 = AppConvertDegInRad(-135.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;		
					CurrentActionID++;	
					break;	

		case 14:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;																				
					CurrentActionID++;	
					break;

		case 15:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-200, APP_DEFAULT_ROBOT_SPEED, NextAction);
					NbObjectFoundInLine1 = 1;														
					CurrentActionID = 200;	
					break;

		// Manage the first object ------------------------------------------------------------------------------------------------------------------
		case 100:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 101:	NextAction->Cmd = Mvt_UsePivotMode;
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = RIGHT_WHEEL;		NextAction->Param4 = AppConvertDegInRad(-180.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;		
					CurrentActionID++;	
					break;	
					
		case 102:	NextAction->Cmd = Mvt_UsePivotMode;
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = LEFT_WHEEL;		NextAction->Param4 = AppConvertDegInRad(-135.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;		
					CurrentActionID++;	
					break;	

		case 103:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 104:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-100, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;	
					break;

		case 105:	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID++;	
					break;

		case 106:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(157, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 107:	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_LOW;				
					CurrentActionID++;	
					break;
							
		case 108:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;		NextAction->Param3 = 700;		NextAction->Param4 = AppConvertDegInRad(135.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					NbObjectFoundInLine1 = 1;
					CurrentActionID = 10;	
					break;	
		
		// Manage the fourth object -----------------------------------------------------------------------------------------------------------------
		case 200:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;

		case 201:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						if(NbObjectFoundInLine1 == 0)
							CurrentActionID = 302;
						else
							CurrentActionID = 202;
					else
						CurrentActionID = 600;
					break;

		case 202:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 203:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2320;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;	

		case 204:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2320;		NextAction->Param3 = 1865;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;		

		case 205:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 206:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-275, APP_DEFAULT_ROBOT_SPEED, NextAction);
					NbObjectFoundInLine1 = 2;
					CurrentActionID = 400;	
					break;

		// Manage the third pawns -------------------------------------------------------------------------------------------------------------------
		case 300:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;		NextAction->Param3 = 900;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;	
					break;

		case 301:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);
					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
					{
						if(NbObjectFoundInLine1 == 0)
							CurrentActionID = 302;
						else
							CurrentActionID = 202;
					}
					else
					{
						CurrentActionID = 200;
					}
					break;

		case 302:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 303:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(-90, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 304:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;		NextAction->Param3 = 525;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					NbObjectFoundInLine1 = 1;
					CurrentActionID = 13;
					break;	

		// Check one pawn from line 2 (pawn 5) ------------------------------------------------------------------------------------------------------
		case 400:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1850;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(-180.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 401:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 402;
					break;

		case 402:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1850;		NextAction->Param3 = 1050;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 403:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet; 
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 404;
					break;

		case 404:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1850;		NextAction->Param3 = 700;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 405:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 406;
					break;

		case 406:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1850;		NextAction->Param3 = 400;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 407:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 500;
					else
						CurrentActionID = 408;
					break;

		case 408:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 2200;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID = 505;
					break;

		// Manage object found on line 2 ------------------------------------------------------------------------------------------------------------
		case 500:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 501:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1620;		NextAction->Param3 = 1400;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;
		
		case 502:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1620;		NextAction->Param3 = 1742;		NextAction->Param4 = AppConvertDegInRad(90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 503:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 504:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-350, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 505:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1620;		NextAction->Param3 = 1225;		NextAction->Param4 = AppConvertDegInRad(-90.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 506:	NextAction->Cmd = Mvt_UseMixedMode;				
					NextAction->Param1 = APP_DEFAULT_ROBOT_SPEED;		NextAction->Param2 = 1300;		NextAction->Param3 = 850;		NextAction->Param4 = AppConvertDegInRad(-135.0);	
					NextAction->CmdType = CmdType_Blocking;		NextAction->ActiveSensorsFlag =	APP_PARAM_APPFLAG_FRONT_SENSORS;	
					CurrentActionID++;
					break;

		case 507:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					break;

		case 508:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-35, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 509:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveToAngleInDeg(-45, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 510:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-750, APP_DEFAULT_ROBOT_SPEED, NextAction);												
					CurrentActionID++;	
					break;

		case 511:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_OPEN;				
					CurrentActionID++;	
					break;

		case 512:	NextAction->Cmd = Sensors_SetHolderLevel;		
					NextAction->Param1 = HOLDER_LEVEL_HIGH;				
					CurrentActionID = 999;	
					break;

		// Manage the last pawns -------------------------------------------------------------------------------------------------------------------
		case 600:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(275, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;	
					break;

		case 601:	NextAction->Cmd = Sensors_SetHolderStatus;		
					NextAction->Param1 = HOLDER_GRAB;				
					CurrentActionID++;	
					NbObjectFoundInLine1 = 2;
					break;

		case 602:	NextAction->Cmd = Mvt_Simple;					
					LibMoving_MoveInMM(-275, APP_DEFAULT_ROBOT_SPEED, NextAction);
					CurrentActionID++;	
					break;

		case 603:	// Select next action from flags
					NextAction->Cmd = Cmd_NotSet;
					CurrentFlag = OSFlagAccept(AppFlags, APP_PARAM_APPFLAG_GP2_HOLDER, OS_FLAG_WAIT_SET_ANY, &Err);

					if((CurrentFlag & APP_PARAM_APPFLAG_GP2_HOLDER) == APP_PARAM_APPFLAG_GP2_HOLDER)
						CurrentActionID = 203;
					else
						CurrentActionID = 400;
					break;

		case 999:
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
