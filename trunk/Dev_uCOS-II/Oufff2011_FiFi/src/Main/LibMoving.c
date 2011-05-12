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

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveInMM(int Dist, INT8U Speed, StructCmd *NextSetpoint)
{
    StructPos CurrentPos;

	// Check params
	if(NULL == NextSetpoint)
		return;

    // Define Setpoint MvtMode and Speed
    NextSetpoint->Cmd = Mvt_Simple;
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
		NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_FRONT_SENSORS;
	else
		NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_BACK_SENSORS;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateInDeg(float AngleInDeg, INT8U Speed, StructCmd *NextSetpoint)
{
    StructPos CurrentPos;

	// Check params
	if(NULL == NextSetpoint)
		return;

    // Define Setpoint MvtMode and Speed
    NextSetpoint->Cmd = Mvt_Simple;
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
	NextSetpoint->Param4 = CurrentPos.angle + AppConvertDegInRad(AngleInDeg);

	NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_ALL_SENSORS;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveToAngleInDeg(float AngleToGoInDeg, INT8U Speed, StructCmd *NextSetpoint)
{
    StructPos CurrentPos;

	// Check params
	if(NULL == NextSetpoint)
		return;

    // Define Setpoint MvtMode and Speed
    NextSetpoint->Cmd = Mvt_Simple;
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

	NextSetpoint->ActiveSensorsFlag = APP_PARAM_APPFLAG_ALL_SENSORS;

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
    case Mvt_Simple:
		// There is only 1 cmd to compute
		memcpy(ExpectedCmd, NewPath + 0, sizeof(StructCmd));
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
		(NewPath + 2)->Param1	 			= ExpectedCmd->Param1;
		(NewPath + 2)->Param2	 			= USE_CURRENT_VALUE;
		(NewPath + 2)->Param3	 			= USE_CURRENT_VALUE;
		(NewPath + 2)->Param4				= atan2f(TmpY, TmpX);
		(NewPath + 2)->ActiveSensorsFlag	= ExpectedCmd->ActiveSensorsFlag;
		
		// Second one: Go to the expected pos
		(NewPath + 1)->Param1	 			= ExpectedCmd->Param1;
		(NewPath + 1)->Param2	 			= ExpectedCmd->Param2;
		(NewPath + 1)->Param3	 			= ExpectedCmd->Param3;
		(NewPath + 1)->Param4 				= USE_CURRENT_VALUE;
		(NewPath + 1)->ActiveSensorsFlag 	= ExpectedCmd->ActiveSensorsFlag;

		// Third (last) one: Turn to the expected pos
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
void LibMoving_CreateEscapeSeq(INT8U EscapeSeqType, INT8U Speed, StructCmd *NewPath, INT8S *NewPathLength)
{
	// Clear memory
	memset(NewPath, 0, APP_MOVING_SEQ_LEN * sizeof(StructCmd));
	*NewPathLength = 0;

	switch(EscapeSeqType)
	{
		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_RIGHT:
			LibMoving_MoveInMM		(-150,	Speed, NewPath + 4);							// Define first movement
			LibMoving_RotateInDeg	(-45,	Speed, NewPath + 3);							// Define second movement
			LibMoving_MoveInMM		(354,	Speed, NewPath + 2);							// Define third movement
			LibMoving_RotateInDeg	(45,	Speed, NewPath + 1);							// Define fourth movement
			LibMoving_MoveInMM		(500,	Speed, NewPath + 0);							// Define last movement

			*NewPathLength = 5;
			break;

		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_LEFT: 
			LibMoving_MoveInMM		(-150,	Speed, NewPath + 4);							// Define first movement
			LibMoving_RotateInDeg	(45,	Speed, NewPath + 3);							// Define second movement
			LibMoving_MoveInMM		(354,	Speed, NewPath + 2);							// Define third movement
			LibMoving_RotateInDeg	(-45,	Speed, NewPath + 1);							// Define fourth movement
			LibMoving_MoveInMM		(500,	Speed, NewPath + 0);							// Define last movement

			*NewPathLength = 5;
			break;

		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_BACK: 
			LibMoving_MoveInMM(-150, Speed, NewPath + 0);									// Define first movement	

			*NewPathLength = 1;
			break;

		// ****************************************************************************************
		case APP_MOVING_ESCAPE_SEQ_FRONT: 
			LibMoving_MoveInMM(150, Speed, NewPath + 0);									// Define first movement	

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
    BOOLEAN Ret             = OS_FALSE;

    if(NULL == SetpointToTest)
        return OS_FALSE;

    // Init var
    memset(&CurrentPos, 0, sizeof(StructPos));

    // Read current odo value
    AppGetCurrentPos(&CurrentPos);

    // Compute Dist and Angle
    DistToSetpoint = (SetpointToTest->Param2 - CurrentPos.x) * (SetpointToTest->Param2 - CurrentPos.x) + (SetpointToTest->Param3 - CurrentPos.y) * (SetpointToTest->Param3 - CurrentPos.y);
    AngleToSetpoint = abs(SetpointToTest->Param4 - CurrentPos.angle);

    switch(SetpointToTest->Cmd)
    {
    // --------------------------------------------------------------------------------------------
    // Check Only for angle
    case Mvt_UseAngleOnly:     
    case Mvt_UsePivotMode:
        if(AngleToSetpoint <= APP_MOVING_ANGLE_APPROCH_PRECISION)
            Ret = OS_TRUE;
        else
            Ret = OS_FALSE;
        break;

    // --------------------------------------------------------------------------------------------
    // Check Only for Dist
    case Mvt_UseDistOnly:
        if(DistToSetpoint <= (APP_MOVING_DIST_APPROCH_PRECISION * APP_MOVING_DIST_APPROCH_PRECISION))
            Ret = OS_TRUE;
        else
            Ret = OS_FALSE;
        break;
        
    // --------------------------------------------------------------------------------------------
    // Check for Angle and Dist
    case Mvt_Simple:
    case Mvt_UseMixedMode:
        if((AngleToSetpoint <= APP_MOVING_ANGLE_APPROCH_PRECISION) && (DistToSetpoint <= (APP_MOVING_DIST_APPROCH_PRECISION * APP_MOVING_DIST_APPROCH_PRECISION)))
            Ret = OS_TRUE;
        else
            Ret = OS_FALSE;
        break;

    // --------------------------------------------------------------------------------------------
    // We have to stay in place
    case Mvt_Stop:
    case Wait:
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
