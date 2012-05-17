/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : LibMoving.h
*********************************************************************************************************
*/

#ifndef LIBMOVING_H
#define LIBMOVING_H 

#include "AppIncludes.h"
#include "mathf.h"
#include "math.h"

void LibMoving_MoveInMM(float Dist, int Speed, StructCmd *NextSetpoint);
	// Dist         : in mm for the movement (>0 go forward, <0 go back)
    // Speed        : Speed to use 
	// NextSetpoint	: pointer to the struct for containing new position
	// MvtMode is set to 'MvtMode_Simple'
	// CmdType is set to 'CmdType_Blocking'

void LibMoving_RotateInDeg(int AngleInDeg, int Speed, StructCmd *NextSetpoint);
	// AngleInDeg   : in mm for the movement (>0 go forward, <0 go back)
    // Speed        : Speed to use 
	// NextSetpoint	: pointer to the struct for containing new position
	// MvtMode is set to 'MvtMode_Simple'
	// CmdType is set to 'CmdType_Blocking'

void LibMoving_RotateToAngleInDeg(int AngleToGoInDeg, int Speed, StructCmd *NextSetpoint);
	// AngleToGoInDeg	: angle in degree we want to go
    // Speed            : Speed to use 
	// NextSetpoint	    : pointer to the struct for containing new position
	// MvtMode is set to 'MvtMode_Simple'
	// CmdType is set to 'CmdType_Blocking'

void LibMoving_ComputeNewPath(StructCmd *ExpectedCmd, StructCmd *NewPath, INT8S *NewPathLength);
	// ExpectedCmd					: Command we have to reach 
	// NewPath						: All commands necessary for reaching ExpectedCmd
	// NewPathLength				: Nb of command defined in NewPath (0 means, no Path is available)

void LibMoving_CreateTimeoutSeq(INT8U TimeoutSeqType, int Speed, StructCmd *NewPath, INT8S *NewPathLength);
	// EscapeSeqType				: Seq type to use for create timeout seq
	//									- APP_MOVING_TIMEOUT_SEQ_FRONT
	//									- APP_MOVING_TIMEOUT_SEQ_BACK
	// Speed						: Speed to use for this escape sequence
	// NewPath						: All commands necessary for this escape seq
	// NewPathLength				: Nb of command defined in NewPath (0 means, no Path is available)

void LibMoving_CreateEscapeSeq(INT8U EscapeSeqType, int Speed, StructCmd *NewPath, INT8S *NewPathLength);
	// EscapeSeqType				: Seq type to use for create escape seq
	//									- APP_MOVING_ESCAPE_SEQ_RIGHT
	//									- APP_MOVING_ESCAPE_SEQ_LEFT
	//									- APP_MOVING_ESCAPE_SEQ_BACK
	// Speed						: Speed to use for this escape sequence
	// NewPath						: All commands necessary for this escape seq
	// NewPathLength				: Nb of command defined in NewPath (0 means, no Path is available)

BOOLEAN LibMoving_IsSetpointReached(StructCmd *SetpointToTest);
    // *SetpointToTest              : Setpoint we have to test

#endif // LIBMOVING
