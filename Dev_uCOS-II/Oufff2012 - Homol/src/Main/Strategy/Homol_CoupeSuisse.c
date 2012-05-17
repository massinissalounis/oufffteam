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
#include "../LibMoving.h"

#ifdef SUISSE_STRATEGY_ENABLED

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
		InitCmd->Param2				= 2935.0;
		InitCmd->Param3				= 1667.0;
		InitCmd->Param4				= AppConvertDegInRad(180.0);
		InitCmd->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
		break;

	case c_ColorB:	// Purple ##############################################
		InitCmd->Cmd				= App_SetNewPos;
		InitCmd->CmdType			= CmdType_NonBlocking;
		InitCmd->Param2				= 65.0;
		InitCmd->Param3				= 1667.0;
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
	case c_ColorA:	// Red #############################################################
		switch(CurrentActionID)
		{
		case 0:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 580.0;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 1:		p->Cmd = MvtSimple_RotateToAngleInDeg;	p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;															p->Param4 = 90.0;	p->ActiveSensorsFlag = APP_PARAM_APPFLAG_NONE;					CurrentActionID++;	break;
		case 2:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = -367;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;
		case 3:		p->Cmd = Mvt_UsePivotMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = RIGHT_WHEEL;						p->Param4 = 180.0;	p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;
		case 4:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = -250;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;
		case 5:		p->Cmd = Mvt_UseMixedMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 2500;			p->Param3 = 1000;	p->Param4 = -145;	p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 6:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 500;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 7:		p->Cmd = Mvt_UseMixedMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 2260;			p->Param3 = 500;	p->Param4 = 90;		p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 8:		p->Cmd = Mvt_UseMixedMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED * 0.5;	p->Param2 = 2260;			p->Param3 = 65;		p->Param4 = 90;		p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	case c_ColorB:	// Purple ##############################################################
		switch(CurrentActionID)
		{
		case 0:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 580.0;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 1:		p->Cmd = MvtSimple_RotateToAngleInDeg;	p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;															p->Param4 = 90.0;	p->ActiveSensorsFlag = APP_PARAM_APPFLAG_NONE;					CurrentActionID++;	break;
		case 2:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = -367;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;
		case 3:		p->Cmd = Mvt_UsePivotMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = LEFT_WHEEL;							p->Param4 = 0;		p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;
		case 4:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = -250;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;
		case 5:		p->Cmd = Mvt_UseMixedMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 500;			p->Param3 = 1000;	p->Param4 = -55;	p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 6:		p->Cmd = MvtSimple_MoveInMM;			p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 500;													p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 7:		p->Cmd = Mvt_UseMixedMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED;			p->Param2 = 740;			p->Param3 = 500;	p->Param4 = 90;		p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;			CurrentActionID++;	break;
		case 8:		p->Cmd = Mvt_UseMixedMode;				p->CmdType = CmdType_Blocking;	p->Param1 = APP_HOMOL_ROBOT_SPEED * 0.5;	p->Param2 = 740;			p->Param3 = 65;		p->Param4 = 90;		p->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;			CurrentActionID++;	break;

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
		}

	break;

	default:		// Not Set ##########################################################
	break;
	}

	// Check for Wait command --------------------------------------------
	if(App_Wait == p->Cmd)
	{
		// Execute the wait command
		OSTimeDlyHMSM(p->Param1, p->Param2, p->Param3, p->Param4);
		return Strategy_GetNextAction(CurrentColor, p);
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

		return Strategy_GetNextAction(CurrentColor, p);
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
