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

#ifdef HOMOL_STRATEGY_ENABLED

#define DEFAULT_SPEED (70)

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetInitCmd(StructCmd *InitCmd)
{
	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	InitCmd->Cmd				= App_SetNewPos;
	InitCmd->CmdType			= CmdType_Blocking;
	InitCmd->Param2				= 65;	
	InitCmd->Param3				= 1667;	
	InitCmd->Param4				= AppConvertDegInRad(0);
	InitCmd->ActiveSensorsFlag		= APP_PARAM_APPFLAG_NONE;

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U StrategyColorB_GetNextAction(StructCmd *NextAction)
{
	static int		NextActionID = 1;
	int			CurrentActionID = 0;
	INT8U 			Err = 0;
	OS_FLAGS		CurrentFlag = 0;
	StructCmd 		*p = NextAction;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	// Set all actions as blocking actions
	p->CmdType = CmdType_Blocking;

	// Set CurrentID to NextID
	CurrentActionID = NextActionID;

	// Read Next Action
	switch(CurrentActionID)
	{
		// StructuredFileLoopBegin
		// LoopID = 0
		case 1:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 100;	p->Cmd = MvtSimple_MoveInMM;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = 580;    		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 1
		case 100:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 101;	p->Cmd = MvtSimple_RotateToAngleInDeg;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param4 = 90;    		break;	
		case 101:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 102;	p->Cmd = MvtSimple_MoveInMM;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = -367;    		break;	
		case 102:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 103;	p->Cmd = Mvt_UsePivotMode;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = LEFT_WHEEL;    NextAction->Param4 = 0;    		break;	
		case 103:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 104;	p->Cmd = MvtSimple_MoveInMM;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = -250;    		break;	
		case 104:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 105;	p->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = 500;    NextAction->Param3 = 1000;    NextAction->Param4 = -55;    		break;	
		case 105:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 106;	p->Cmd = MvtSimple_MoveInMM;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = 500;    		break;	
		case 106:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 107;	p->Cmd = Mvt_UseMixedMode;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = 740;    NextAction->Param3 = 500;    NextAction->Param4 = 90;    		break;	
		case 107:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 108;	p->Cmd = MvtSimple_MoveInMM;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = -425;    		break;	
		case 108:	p->CmdType = CmdType_Blocking;		p->ActiveSensorsFlag =	APP_PARAM_APPFLAG_NONE;	NextActionID = 108;	p->Cmd = MvtSimple_MoveInMM;		NextAction->Param1 = DEFAULT_SPEED;    NextAction->Param2 = 170;    		break;	
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 2
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 3
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 4
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 5
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 6
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 7
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 8
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 9
		// StructuredFileLoopEnd

		// StructuredFileLoopBegin
		// LoopID = 10
		// StructuredFileLoopEnd

		default:
			return ERR__NO_MORE_DATA_AVAILABLE;
			break;
	}

	// Check for Wait command --------------------------------------------
	if(App_Wait == p->Cmd)
	{
		// Execute the wait command
		OSTimeDlyHMSM(p->Param1, p->Param2, p->Param3, p->Param4);
		return StrategyColorB_GetNextAction(p);
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
