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

void LibMoving_MoveInMM(StructMvtPos *OldPos, int dist, StructMvtPos *NewPos);
	// OldPos	: pointer to current position
	// distance : in mm for the movement (>0 go forward, <0 go back)
	// NewPos	: pointer to the struct for containing new position
	// In this function, Flag of NewPos is set to APP_FLAG_POS__SIMPLE_MOVE, don't change it

void LibMoving_RotateInDeg(StructMvtPos *OldPos, float AngleInDeg, StructMvtPos *NewPos);
	// OldPos		: pointer to current position
	// AngleInDeg	: angle in degree to do (>0 trigo, <0 horaire)
	// NewPos		: pointer to the struct for containing new position
	// In this function, Flag of NewPos is set to APP_FLAG_POS__SIMPLE_MOVE, don't change it

void LibMoving_MoveToAngleInDeg(StructMvtPos *OldPos, float AngleToGoInDeg, StructMvtPos *NewPos);
	// OldPos		: pointer to current position
	// AngleInDeg	: angle in degree we want to go
	// NewPos		: pointer to the struct for containing new position

void LibMoving_DivideMvt(StructMvtPos *OldPos, StructMvtPos *ExpectedPos, int *NewMovingSeqRemainingSteps);
	// OldPos						: pointer to current postion
	// ExpectedPos					: pointer to expected position
	// NewMovingSeqRemainingSteps	: Nb of command set into MovingSeq

void LibMoving_CreateEscapeSeq(CPU_INT08U NumEscapeSeq);
	// NumEscapeSeq					: Nb of seq to use for create escape seq
	//		- APP_MOVING_ESCAPE_SEQ_AUTO
	//		- APP_MOVING_ESCAPE_SEQ_RIGHT
	//		- APP_MOVING_ESCAPE_SEQ_LEFT
	//		- APP_MOVING_ESCAPE_SEQ_BACK
	//		- APP_MOVING_ESCAPE_SEQ_STOP
	//		- APP_MOVING_ESCAPE_SEQ_CHECK_CORN
	// Use APP_MOVING_ESCAPE_SEQ_DEFAULT for default escape sequence

#endif // LIBMOVING
