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
*********************************************************************************************************
*/

#include "LibMoving.h"

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveInMM(StructPos *OldPos, int dist, StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new position
	NewPos->x = OldPos->x + dist * cosf(OldPos->angle);
	NewPos->y = OldPos->y + dist * sinf(OldPos->angle);
	NewPos->angle = OldPos->angle;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateInDeg(StructPos *OldPos, float AngleInDeg, StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = OldPos->angle + AppConvertDegInRad(AngleInDeg);

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveToAngleInDeg(StructPos *OldPos, float AngleToGoInDeg, StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = AppConvertDegInRad(AngleToGoInDeg);

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_DivideMvt(StructPos *OldPos, StructPos *ExpectedPos, StructPos *NewMovingSeq, int *NewMovingSeqRemainingSteps)
{
	// Check for parameters
	if((NULL == OldPos) || (NULL == ExpectedPos) || (NULL == NewMovingSeq) || (NULL == NewMovingSeqRemainingSteps))
	{
		if(NULL != NewMovingSeqRemainingSteps)
			*NewMovingSeqRemainingSteps == -1;
		
		return;
	}

#ifdef APP_MOVING_ALGO_1_SIMPLE
	// Simple Moving Algo
	float TmpX = 0;
	float TmpY = 0;

	TmpX = ExpectedPos->x - OldPos->x;
	TmpY = ExpectedPos->y - OldPos->y;


	// Movement will be done in 3 steps
	// First one: Turn to be in the correct direction
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 3)->x	 	= OldPos->x;
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 3)->y	 	= OldPos->y;
	if((0 == TmpX) && (0 == TmpY))
		(NewMovingSeq + APP_MOVING_SEQ_LEN - 3)->angle 	= OldPos->angle;
	else
		(NewMovingSeq + APP_MOVING_SEQ_LEN - 3)->angle 	= atan2f(TmpY, TmpX);

	// Second one: Go to the expected pos
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 2)->x	 	= ExpectedPos->x;
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 2)->y	 	= ExpectedPos->y;
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 2)->angle 	= (NewMovingSeq + APP_MOVING_SEQ_LEN - 3)->angle;

	// Third (last) one: Turn to the expected pos
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 1)->x	 	= ExpectedPos->x;
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 1)->y	 	= ExpectedPos->y;
	(NewMovingSeq + APP_MOVING_SEQ_LEN - 1)->angle 	= ExpectedPos->angle;

	// Set the nb of steps for this movment
	*NewMovingSeqRemainingSteps = 3;

	// First algo has been set, don't try another one
	return;
#endif

	// if we are here, that means that no moving algo has been set
	*NewMovingSeqRemainingSteps = -1;
	return;
}
