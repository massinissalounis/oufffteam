/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : LibMoving.c
*
* Suivi de version :
* 2009-04-08 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************
*/

#include "LibMoving.h"

extern float error_debug_1;
extern float error_debug_2;
extern float error_debug_3;
extern float error_debug_4;
extern float error_debug_5;

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveInMM(int Dist, int Speed, StructCmd *NextSetpoint)
{
    StructPos CurrentPos;

	// Check params
	if(NULL == NextSetpoint)
		return;

    // Define Setpoint MvtMode and Speed
    NextSetpoint->Cmd = MvtSimple_MoveInMM;
	NextSetpoint->CmdType = CmdType_Blocking;
    NextSetpoint->Param1 = Speed;

    if(NextSetpoint->Param1 > 100)
        NextSetpoint->Param1 = 100;

    if(NextSetpoint->Param1 < 1)
        NextSetpoint->Param1 = 1;

    // Read Current Odo position
    AppGetCurrentPos(&CurrentPos);

	// Compute new position
	NextSetpoint->Param2 = CurrentPos.x + Dist * cosf(CurrentPos.angle);
	NextSetpoint->Param3 = CurrentPos.y + Dist * sinf(CurrentPos.angle);
	NextSetpoint->Param4 = USE_CURRENT_VALUE;

	if(Dist >= 0)
		NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_FRONT;
	else
		NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_SENSORS_BACK;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateInDeg(int AngleInDeg, int Speed, StructCmd *NextSetpoint)
{
    StructPos CurrentPos;
	
	// Check params
	if(NULL == NextSetpoint)
		return;

    // Define Setpoint MvtMode and Speed
    NextSetpoint->Cmd = MvtSimple_RotateInDeg;
	NextSetpoint->CmdType = CmdType_Blocking;
    NextSetpoint->Param1 = Speed;

    if(NextSetpoint->Param1 > 100)
        NextSetpoint->Param1 = 100;

    if(NextSetpoint->Param1 < 1)
        NextSetpoint->Param1 = 1;

    // Read Current Odo position
    AppGetCurrentPos(&CurrentPos);

	// Compute new angle
	NextSetpoint->Param2 = USE_CURRENT_VALUE;
	NextSetpoint->Param3 = USE_CURRENT_VALUE; 
	NextSetpoint->Param4 = AppCheckAngleInRad(CurrentPos.angle + AppConvertDegInRad(AngleInDeg));

	NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_NONE;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateToAngleInDeg(int AngleToGoInDeg, int Speed, StructCmd *NextSetpoint)
{
    StructPos CurrentPos;

	// Check params
	if(NULL == NextSetpoint)
		return;

    // Define Setpoint MvtMode and Speed
    NextSetpoint->Cmd = MvtSimple_RotateToAngleInDeg;
	NextSetpoint->CmdType = CmdType_Blocking;
    NextSetpoint->Param1 = Speed;

    if(NextSetpoint->Param1 > 100)
        NextSetpoint->Param1 = 100;

    if(NextSetpoint->Param1 < 1)
        NextSetpoint->Param1 = 1;

    // Read Current Odo position
    AppGetCurrentPos(&CurrentPos);

	// Compute new angle
	NextSetpoint->Param2 = USE_CURRENT_VALUE;
	NextSetpoint->Param3 = USE_CURRENT_VALUE; 
	NextSetpoint->Param4 = AppConvertDegInRad(AngleToGoInDeg);

	NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_NONE;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_ComputeNewPath(StructCmd *ExpectedCmd, StructCmd *NewPath, INT8S *NewPathLength)
{
	// Check for parameters
	if((NULL == ExpectedCmd) || (NULL == NewPath) || (NULL == NewPathLength))
	{
		if(NULL != NewPathLength)
			*NewPathLength = 0;
		
		return;
	}

	// Vars
	StructPos	    CurrentPos;		    					// Data used for storing current pos from TaskOdo
	float TmpX = 0;
	float TmpY = 0;
	float TmpAngle = 0;
	float TmpNewAngle = 0;

	// Clear New Path memory
	memset(NewPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructCmd));

	// Select Mvt Type
    switch(ExpectedCmd->Cmd)
    {
    // --------------------------------------------------------------------------------------------
    // Simple move (no computation)
    case Mvt_UseAngleOnly:     
    case Mvt_UseDistOnly:
    case Mvt_UsePivotMode:
    case MvtSimple_MoveInMM:
    case MvtSimple_RotateInDeg:
    case MvtSimple_RotateToAngleInDeg:
	case App_SetNewPos:
		// There is only 1 cmd to compute
		memcpy(NewPath + 0, ExpectedCmd, sizeof(StructCmd));
		*NewPathLength = 1;
        break;

    // --------------------------------------------------------------------------------------------
    // Compute for for Mixed Mode
    case Mvt_UseMixedMode:

		// Read for current postition
		if(AppGetCurrentPos(&CurrentPos) != ERR__NO_ERROR)
		{   
			// In case of we are unable to read current position, we return an empty path
			*NewPathLength = 0;
			return;
		}

		// Compute temp values for angle
		TmpX = ExpectedCmd->Param2 - CurrentPos.x;
		TmpY = ExpectedCmd->Param3 - CurrentPos.y;

		// Check dist between current pos and setpoint to check if the movement is not a small mvt
		if(TmpX * TmpX + TmpY * TmpY < APP_MOVING_MINIMAL_DIST_FOR_MIXED_MODE * APP_MOVING_MINIMAL_DIST_FOR_MIXED_MODE)
		{
			// Next movement is to short for using mixed mode, we do nothing
			*NewPathLength = 0;
			return;
		}

		// Movment will be done in 3 steps
		// First one: Turn to be in the correct direction
		(NewPath + 2)->Cmd		 			= Mvt_UseMixedMode;
		(NewPath + 2)->CmdType 				= ExpectedCmd->CmdType;
		(NewPath + 2)->Param1	 			= ExpectedCmd->Param1;
		(NewPath + 2)->Param2	 			= USE_CURRENT_VALUE;
		(NewPath + 2)->Param3	 			= USE_CURRENT_VALUE;
		(NewPath + 2)->Param4				= AppCheckAngleInRad(atan2f(TmpY, TmpX));
		(NewPath + 2)->ActiveSensorsFlag	= ExpectedCmd->ActiveSensorsFlag;
		
		// Second one: Go to the expected pos
		(NewPath + 1)->Cmd		 			= Mvt_UseMixedMode;
		(NewPath + 1)->CmdType 				= ExpectedCmd->CmdType;
		(NewPath + 1)->Param1	 			= ExpectedCmd->Param1;
		(NewPath + 1)->Param2	 			= ExpectedCmd->Param2;
		(NewPath + 1)->Param3	 			= ExpectedCmd->Param3;
		(NewPath + 1)->Param4 				= USE_CURRENT_VALUE;
		(NewPath + 1)->ActiveSensorsFlag 	= ExpectedCmd->ActiveSensorsFlag;

		// Third (last) one: Turn to the expected pos
		(NewPath + 0)->Cmd		 			= Mvt_UseMixedMode;
		(NewPath + 0)->CmdType 				= ExpectedCmd->CmdType;
		(NewPath + 0)->Param1	 			= ExpectedCmd->Param1;
		(NewPath + 0)->Param2	 			= USE_CURRENT_VALUE;
		(NewPath + 0)->Param3	 			= USE_CURRENT_VALUE;
		(NewPath + 0)->Param4				= ExpectedCmd->Param4;
		(NewPath + 0)->ActiveSensorsFlag	= ExpectedCmd->ActiveSensorsFlag;

		// Set the nb of steps for this movment
		*NewPathLength = 3;

        break;

    // --------------------------------------------------------------------------------------------
    // No computation is needed
    default:
        break;
    }

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_CreateEscapeSeq(INT8U EscapeSeqType, int Speed, StructCmd *NewPath, INT8S *NewPathLength)
{
    StructPos CurrentPos;
	StructCmd *Action = NULL;

	// Clear memory
	memset(NewPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructCmd));
	*NewPathLength = 0;

	// Read Current Odo position
	AppGetCurrentPos(&CurrentPos);

	switch(EscapeSeqType)
	{
		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_RIGHT:
			// Compute First mvt
			Action = NewPath + 4;
			Action->Cmd 				= MvtSimple_MoveInMM;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= CurrentPos.x + (-200.0) * cosf(CurrentPos.angle);	
			Action->Param3 				= CurrentPos.y + (-200.0) * sinf(CurrentPos.angle);		
			Action->Param4 				= CurrentPos.angle;	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_BACK;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Second mvt
			Action = NewPath + 3;
			Action->Cmd 				= MvtSimple_RotateInDeg;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2;	
			Action->Param3 				= (Action+1)->Param3;		
			Action->Param4 				= AppCheckAngleInRad((Action+1)->Param4 + AppConvertDegInRad(-45.0));	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_RIGHT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Third mvt
			Action = NewPath + 2;
			Action->Cmd 				= MvtSimple_MoveInMM;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2 + (600.0) * cosf((Action+1)->Param4);	
			Action->Param3 				= (Action+1)->Param3 + (600.0) * sinf((Action+1)->Param4);		
			Action->Param4 				= (Action+1)->Param4;	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_FRONT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Fourth mvt
			Action = NewPath + 1;
			Action->Cmd 				= MvtSimple_RotateInDeg;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2;	
			Action->Param3 				= (Action+1)->Param3;		
			Action->Param4 				= AppCheckAngleInRad((Action+1)->Param4 + AppConvertDegInRad(45.0));	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_LEFT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Fifth mvt
			Action = NewPath + 0;
			Action->Cmd 				= MvtSimple_MoveInMM;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2 + (400.0) * cosf((Action+1)->Param4);	
			Action->Param3 				= (Action+1)->Param3 + (400.0) * sinf((Action+1)->Param4);		
			Action->Param4 				= (Action+1)->Param4;	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_FRONT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			*NewPathLength = 5;
			break;

		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_LEFT:
			// Compute First mvt
			Action = NewPath + 4;
			Action->Cmd 				= MvtSimple_MoveInMM;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= CurrentPos.x + (-200.0) * cosf(CurrentPos.angle);	
			Action->Param3 				= CurrentPos.y + (-200.0) * sinf(CurrentPos.angle);		
			Action->Param4 				= CurrentPos.angle;	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_BACK;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			
			
			// Compute Second mvt
			Action = NewPath + 3;
			Action->Cmd 				= MvtSimple_RotateInDeg;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2;	
			Action->Param3 				= (Action+1)->Param3;		
			Action->Param4 				= (Action+1)->Param4 + AppConvertDegInRad(45.0);	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_LEFT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Third mvt
			Action = NewPath + 2;
			Action->Cmd 				= MvtSimple_MoveInMM;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2 + (600.0) * cosf((Action+1)->Param4);	
			Action->Param3 				= (Action+1)->Param3 + (600.0) * sinf((Action+1)->Param4);		
			Action->Param4 				= (Action+1)->Param4;	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_FRONT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Fourth mvt
			Action = NewPath + 1;
			Action->Cmd 				= MvtSimple_RotateInDeg;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2;	
			Action->Param3 				= (Action+1)->Param3;		
			Action->Param4 				= (Action+1)->Param4 + AppConvertDegInRad(-45.0);	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_RIGHT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			// Compute Fifth mvt
			Action = NewPath + 0;
			Action->Cmd 				= MvtSimple_MoveInMM;		
			Action->CmdType 			= CmdType_Blocking;		
			Action->Param1 				= Speed;	
			Action->Param2 				= (Action+1)->Param2 + (400.0) * cosf((Action+1)->Param4);	
			Action->Param3 				= (Action+1)->Param3 + (400.0) * sinf((Action+1)->Param4);		
			Action->Param4 				= (Action+1)->Param4;	
#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_FRONT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			

			*NewPathLength = 5;
			break;

		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_BACK: 
			Action = NewPath + 0;
			LibMoving_MoveInMM(-150, Speed, Action);										// Define first movement	

#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_BACK;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			
			*NewPathLength = 1;
			break;

		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_FRONT: 
			Action = NewPath + 0;
			LibMoving_MoveInMM(150, Speed, Action);									// Define first movement	

#ifndef APP_PARAM_DISABLE_SENSORS_DURING_ESCAPE
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_SENSORS_FRONT;
#else
			Action->ActiveSensorsFlag	= APP_PARAM_APPFLAG_NONE;
#endif			
			*NewPathLength = 1;
			break;

		// ****************************************************************************************
		default:
			break;
	}
}

// ------------------------------------------------------------------------------------------------
BOOLEAN LibMoving_IsSetpointReached(StructCmd *SetpointToTest)
{
    StructPos CurrentPos;
    float DistToSetpoint    = 0.0;
    float AngleToSetpoint   = 0.0;
    float AngleToSetpoint1  = 0.0;
    float AngleToSetpoint2  = 0.0;
    BOOLEAN Ret             = OS_FALSE;

    if(NULL == SetpointToTest)
        return OS_FALSE;

    // Init var
    memset(&CurrentPos, 0, sizeof(StructPos));

    // Read current odo value
    AppGetCurrentPos(&CurrentPos);

    AngleToSetpoint1 = fabs(SetpointToTest->Param4 - CurrentPos.angle);
    AngleToSetpoint2 = 2*M_PI - AngleToSetpoint1;
	
	if(AngleToSetpoint1 > AngleToSetpoint2)
		AngleToSetpoint = AngleToSetpoint2;
	else
		AngleToSetpoint = AngleToSetpoint1;

	DistToSetpoint = (SetpointToTest->Param2 - CurrentPos.x) * (SetpointToTest->Param2 - CurrentPos.x) + (SetpointToTest->Param3 - CurrentPos.y) * (SetpointToTest->Param3 - CurrentPos.y);

    switch(SetpointToTest->Cmd)
    {
    // --------------------------------------------------------------------------------------------
    // Check Only for angle
    case Mvt_UseAngleOnly:     
    case Mvt_UsePivotMode:
		// Compute the AngleToSetPoint in Pivot Mode
        if(AngleToSetpoint <= APP_MOVING_APPROACH_PRECISION_COEF * APP_MOVING_ANGLE_APPROACH_PRECISION)
            Ret = OS_TRUE;
        else
            Ret = OS_FALSE;
        break;

    // --------------------------------------------------------------------------------------------
    // Check Only for Dist
    case Mvt_UseDistOnly:
        if(DistToSetpoint <= (APP_MOVING_APPROACH_PRECISION_COEF * APP_MOVING_DIST_APPROACH_PRECISION * APP_MOVING_DIST_APPROACH_PRECISION))
            Ret = OS_TRUE;
        else
            Ret = OS_FALSE;
        break;
        
    // --------------------------------------------------------------------------------------------
    // Check for Angle and Dist
    case MvtSimple_RotateInDeg:
	case MvtSimple_MoveInMM:
	case MvtSimple_RotateToAngleInDeg:
    case Mvt_UseMixedMode:
        if((AngleToSetpoint <= APP_MOVING_APPROACH_PRECISION_COEF * APP_MOVING_ANGLE_APPROACH_PRECISION) && (DistToSetpoint <= (APP_MOVING_APPROACH_PRECISION_COEF * APP_MOVING_DIST_APPROACH_PRECISION * APP_MOVING_DIST_APPROACH_PRECISION)))
            Ret = OS_TRUE;
        else
            Ret = OS_FALSE;
        break;

    // --------------------------------------------------------------------------------------------
    // We have to stay in place
    case Mvt_Stop:
    case App_Wait:
        Ret = OS_FALSE;
        break;

    // --------------------------------------------------------------------------------------------
    // MvtMode is not set, exits without any check
    default:
        Ret = OS_TRUE;
        break;
    }

    return Ret;
}
