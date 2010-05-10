/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskMain.h
*********************************************************************************************************
*/

#ifndef TASKMAIN_H
#define TASKMAIN_H

#include <AppIncludes.h>

// Vars -------------------------------------------------------------------------------------------
struct StructPos TaskMain_CurrentPos;						// Local var to read current pos
struct StructPos TaskMain_ExpectedPos;						// Local var to store pos we have to go
struct StructPos TaskMain_NextSetpointPos;					// Local var to store pos we have to go
struct StructPos TaskMain_MovingSeq[APP_MOVING_SEQ_LEN];	// Moving sequence (used for complex moving)
													// Last point is stored to index APP_MOVING_SEQ_LEN-1, the point before is stored APP_MOVING_SEQ_LEN-2, etc...
int TaskMain_MovingSeqRemainingSteps;				// Interger to contain number of steps remaining in MovingSeq

// Functions --------------------------------------------------------------------------------------
void TaskMain_GetNextAction();
	// Function to get next action
	// Next postion has been set into the TaskMain_ExpectedPos variable

void TaskMain_GetNextActionForColorA();
	// Function to get next action for color A 
	// Next postion has been set into the TaskMain_ExpectedPos variable

void TaskMain_GetNextActionForColorB();
	// Function to get next action for color B 
	// Next postion has been set into the TaskMain_ExpectedPos variable

void TaskMain_Init();
	// Init function

void TaskMain_CheckForBumpers();
	// Read bumpers flags to check for collision
	// In case of collision, this function create a new crossing point
	//	- For front bumps : We go back
	//  - For other bumps : We stop moving 

void TaskMain_GetCurrentPos();
	// Function to read current position
	// Value are stored into local var

void TaskMain_StopMvt();
	// Function to stop mvt to current position

BOOLEAN TaskMain_IsSetpointReached();
	// Function to indicate if current setpoint has been reached.
	// Return OS_TRUE if it's ok, OS_FALSE otherwise
	// APP_PARAM_ERR_ON_POS and APP_PARAM_ERR_ON_ANGLE allow you to change precision for positionning

void TaskMain_Main(void *p_arg);
	// Fonction principale
	// void *p_arg		: Arg for this task

void LibMoving_MoveInMM(struct StructPos *OldPos, int dist, struct StructPos *NewPos);
	// OldPos	: pointer to current position
	// distance : in mm for the movement (>0 go forward, <0 go back)
	// NewPos	: pointer to the struct for containing new position
	// In this function, Flag of NewPos is set to APP_FLAG_POS__SIMPLE_MOVE, don't change it

void LibMoving_RotateInDeg(struct StructPos *OldPos, float AngleInDeg, struct StructPos *NewPos);
	// OldPos		: pointer to current position
	// AngleInDeg	: angle in degree to do (>0 trigo, <0 horaire)
	// NewPos		: pointer to the struct for containing new position
	// In this function, Flag of NewPos is set to APP_FLAG_POS__SIMPLE_MOVE, don't change it

void LibMoving_MoveToAngleInDeg(struct StructPos *OldPos, float AngleToGoInDeg, struct StructPos *NewPos);
	// OldPos		: pointer to current position
	// AngleInDeg	: angle in degree we want to go
	// NewPos		: pointer to the struct for containing new position

void LibMoving_DivideMvt(struct StructPos *OldPos, struct StructPos *ExpectedPos, int *NewMovingSeqRemainingSteps);
	// OldPos						: pointer to current postion
	// ExpectedPos					: pointer to expected position
	// NewMovingSeqRemainingSteps	: Nb of command set into MovingSeq
	
#endif // TASKMAIN_H
