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

void LibMoving_MoveInMM(int Dist, INT8U Speed, StructMvtPos *NextSetpoint);
	// Dist         : in mm for the movement (>0 go forward, <0 go back)
    // Speed        : Speed to use 
	// NextSetpoint	: pointer to the struct for containing new position
	// MvtMode is set to 'MvtMode_Simple'

void LibMoving_RotateInDeg(float AngleInDeg, INT8U Speed, StructMvtPos *NextSetpoint);
	// AngleInDeg   : in mm for the movement (>0 go forward, <0 go back)
    // Speed        : Speed to use 
	// NextSetpoint	: pointer to the struct for containing new position
	// MvtMode is set to 'MvtMode_Simple'

void LibMoving_MoveToAngleInDeg(float AngleToGoInDeg, INT8U Speed, StructMvtPos *NextSetpoint);
	// AngleToGoInDeg	: angle in degree we want to go
    // Speed            : Speed to use 
	// NextSetpoint	    : pointer to the struct for containing new position
	// MvtMode is set to 'MvtMode_Simple'

// Todo
void LibMoving_DivideMvt(StructMvtPos *OldPos, StructMvtPos *ExpectedPos, int *NewMovingSeqRemainingSteps);
	// OldPos						: pointer to current postion
	// ExpectedPos					: pointer to expected position
	// NewMovingSeqRemainingSteps	: Nb of command set into MovingSeq

// Todo
void LibMoving_CreateEscapeSeq(CPU_INT08U NumEscapeSeq);
	// NumEscapeSeq					: Nb of seq to use for create escape seq
	//		- APP_MOVING_ESCAPE_SEQ_AUTO
	//		- APP_MOVING_ESCAPE_SEQ_RIGHT
	//		- APP_MOVING_ESCAPE_SEQ_LEFT
	//		- APP_MOVING_ESCAPE_SEQ_BACK
	//		- APP_MOVING_ESCAPE_SEQ_STOP
	//		- APP_MOVING_ESCAPE_SEQ_CHECK_CORN
	// Use APP_MOVING_ESCAPE_SEQ_DEFAULT for default escape sequence

BOOLEAN LibMoving_IsSetpointReached(StructMvtPos *SetpointToTest);
    // *SetpointToTest              : Setpoint we have to test

#endif // LIBMOVING
