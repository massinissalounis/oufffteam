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

void LibMoving_MoveInMM(StructPos *OldPos, int dist, StructPos *NewPos);
	// OldPos	: pointer to current position
	// distance : in mm for the movement (>0 go forward, <0 go back)
	// NewPos	: pointer to the struct for containing new position

void LibMoving_RotateInDeg(StructPos *OldPos, float AngleInDeg, StructPos *NewPos);
	// OldPos		: pointer to current position
	// AngleInDeg	: angle in degree to do (>0 trigo, <0 horaire)
	// NewPos		: pointer to the struct for containing new position

void LibMoving_MoveToAngleInDeg(StructPos *OldPos, float AngleToGoInDeg, StructPos *NewPos);
	// OldPos		: pointer to current position
	// AngleInDeg	: angle in degree we want to go
	// NewPos		: pointer to the struct for containing new position

void LibMoving_DivideMvt(StructPos *OldPos, StructPos *ExpectedPos, StructPos *NewMovingSeq, int *NewMovingSeqRemainingSteps);
	// OldPos						: pointer to current postion
	// ExpectedPos					: pointer to expected position
	// NewMovingSeq					: pointer to table containing NewMovingSeq (Size of NewMovingSeq is defined by APP_MOVING_SEQ_LEN)
	// NewMovingSeqRemainingSteps	: Nb of command set into MovingSeq
	

#endif // LIBMOVING
