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
void LibMoving_MoveInMM(StructMvtPos *OldPos, int dist, StructMvtPos *NewPos)
{
/* Todo
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new position
	NewPos->x = OldPos->x + dist * cosf(OldPos->angle);
	NewPos->y = OldPos->y + dist * sinf(OldPos->angle);
	NewPos->angle = OldPos->angle;

	if(dist >= 0)
		NewPos->IDActiveSensors = SENSORS_FRONT_ID;
	else
		NewPos->IDActiveSensors = SENSORS_BACK_ID;

*/
	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateInDeg(StructMvtPos *OldPos, float AngleInDeg, StructMvtPos *NewPos)
{
/* Todo
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = OldPos->angle + AppConvertDegInRad(AngleInDeg);

	NewPos->IDActiveSensors = SENSORS_ALL_ID;

*/
	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveToAngleInDeg(StructMvtPos *OldPos, float AngleToGoInDeg, StructMvtPos *NewPos)
{
/* Todo
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = AppConvertDegInRad(AngleToGoInDeg);

	NewPos->IDActiveSensors = SENSORS_ALL_ID;

*/
	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_DivideMvt(StructMvtPos *OldPos, StructMvtPos *ExpectedPos, int *NewMovingSeqRemainingSteps)
{
/* Todo
	// Check for parameters
	if((NULL == OldPos) || (NULL == ExpectedPos) || (NULL == NewMovingSeqRemainingSteps))
	{
		if(NULL != NewMovingSeqRemainingSteps)
			*NewMovingSeqRemainingSteps == -1;
		
		return;
	}

#ifdef APP_MOVING_ALGO_1_SIMPLE
	// Simple Moving Algo
	float TmpX = 0;
	float TmpY = 0;
	float TmpAngle = 0;
	float TmpNewAngle = 0;

	TmpX = ExpectedPos->x - OldPos->x;
	TmpY = ExpectedPos->y - OldPos->y;

	// If movement is too short for computation, we don't do anything
	/* Todo
	if((fabs(TmpX) < APP_PARAM_ERR_ON_POS) && (fabs(TmpY) < APP_PARAM_ERR_ON_POS))
	{
		// Third (last) one: Turn to the expected pos
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].x	 			= ExpectedPos->x;
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].y	 			= ExpectedPos->y;
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].angle 			= ExpectedPos->angle;
		TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1].IDActiveSensors 	= ExpectedPos->IDActiveSensors;
	
		// Set the nb of steps for this movment
		*NewMovingSeqRemainingSteps = 1;
	}
	*/

/* Todo
	// Movment will be done in 3 steps
	// First one: Turn to be in the correct direction
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).x	 				= OldPos->x;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).y	 				= OldPos->y;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).angle 				= atan2f(TmpY, TmpX);
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]).IDActiveSensors 	= ExpectedPos->IDActiveSensors;

	// Second one: Go to the expected pos
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).x	 				= ExpectedPos->x;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).y	 				= ExpectedPos->y;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).angle 				= TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3].angle;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]).IDActiveSensors 	= ExpectedPos->IDActiveSensors;

	// Third (last) one: Turn to the expected pos
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).x	 				= ExpectedPos->x;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).y	 				= ExpectedPos->y;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).angle 				= ExpectedPos->angle;
	(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]).IDActiveSensors 	= ExpectedPos->IDActiveSensors;

	// Set the nb of steps for this movment
	*NewMovingSeqRemainingSteps = 3;

	// First algo has been set, don't try another one
	return;
#endif

	// if we are here, that means that no moving algo has been set
	*NewMovingSeqRemainingSteps = -1;
*/
	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_CreateEscapeSeq(CPU_INT08U NumEscapeSeq)
{
/* Todo
	switch(NumEscapeSeq)
	{
		case APP_MOVING_ESCAPE_SEQ_STOP: // *********************************************
			// Do nothing. 
			break;

		case APP_MOVING_ESCAPE_SEQ_FRONT_RIGHT: // **************************************
			TaskMain_GetCurrentPos();

			// Define first move : go back
			LibMoving_MoveInMM(&TaskMain_CurrentPos, -150, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 5]));									// Define first movement	
			LibMoving_RotateInDeg(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 5]), -45.0, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 4]));		// Define second movement
			LibMoving_MoveInMM(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 4]), 354, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]));			// Define third movement	
			LibMoving_RotateInDeg(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]), 45.0, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]));		// Define fourth movement
			LibMoving_MoveInMM(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]), 500, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]));			// Define third movement	

			TaskMain_MovingSeqRemainingSteps = 5;																							// Define movement
			TaskMain_NextSetpointPos.Flag = TaskMain_NextSetpointPos.Flag & !(APP_FLAG_POS__LOCK_IN_POS);									// Release movement
			TaskMain_NextSetpointPos.IDActiveSensors = TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 5].IDActiveSensors;							// Activate sensors
			break;

		case APP_MOVING_ESCAPE_SEQ_FRONT_LEFT: // ***************************************
			LibMoving_MoveInMM(&TaskMain_CurrentPos, -150, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 5]));									// Define first movement	
			LibMoving_RotateInDeg(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 5]), 45.0, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 4]));		// Define second movement
			LibMoving_MoveInMM(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 4]), 354, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]));			// Define third movement	
			LibMoving_RotateInDeg(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 3]), -45.0, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]));		// Define fourth movement
			LibMoving_MoveInMM(&(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 2]), 500, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]));			// Define third movement	

			TaskMain_MovingSeqRemainingSteps = 5;																							// Define movement
			TaskMain_NextSetpointPos.Flag = TaskMain_NextSetpointPos.Flag & !(APP_FLAG_POS__LOCK_IN_POS);									// Release movement
			TaskMain_NextSetpointPos.IDActiveSensors = TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 5].IDActiveSensors;							// Activate sensors
			break;

		case APP_MOVING_ESCAPE_SEQ_CHECK_CORN: // ***************************************
			LibMoving_MoveInMM(&TaskMain_CurrentPos, -150, &(TaskMain_MovingSeq[APP_MOVING_SEQ_LEN - 1]));									// Define first movement	

			TaskMain_MovingSeqRemainingSteps = 1;																							// Define movement
			TaskMain_NextSetpointPos.Flag = TaskMain_NextSetpointPos.Flag & !(APP_FLAG_POS__LOCK_IN_POS);									// Release movement
			TaskMain_NextSetpointPos.IDActiveSensors = SENSORS_BACK_ID;																		// Activate sensors

			// Cancel expected position because we can't reach this point. We have to try another...
			memcpy(&TaskMain_ExpectedPos, &TaskMain_NextSetpointPos, sizeof(StructMvtPos));

			// Change next state due to collision
			switch(TaskMain_NextState)
			{
				default:
					break;
			}
			break;

		default:
			break;
	}
*/
}
