/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskAsser.h
*********************************************************************************************************
*/

#ifndef TASKASSER_H
#define TASKASSER_H

#include "AppIncludes.h"
#include "AppGlobalVars.h"

// Define
#define DISTANCE_ALPHA_ONLY		        APP_MOVING_DIST_APPROACH_PRECISION 	// Error in mm in distance to consider the change of control mode
										                                    // This parameter is also used to switch on the arrival flag

#define ANGLE_APPROACH_PRECISION		APP_MOVING_ANGLE_APPROACH_PRECISION	// Error in rad for angle to consider the setpoint reached

#define PIVOT_LEFT_APPROACH_PRECISION	(PIVOT_APPROACH_PRECISION * M_PI / 180.0) * CONVERSION_RAD_TO_MM * CONVERSION_MM_TO_INC_LEFT
#define PIVOT_RIGHT_APPROACH_PRECISION	(PIVOT_APPROACH_PRECISION * M_PI / 180.0) * CONVERSION_RAD_TO_MM * CONVERSION_MM_TO_INC_RIGHT


//////////////////////////////////////////////
// Local structures
//////////////////////////////////////////////
typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float IMax;
	float error_old[PID_SUM_NB_SAMPLES];
	int current_error_old;
	float error_sum;
}PID_data;

typedef struct {
	float acceleration_order;
	float speed_order;
	
	float final_approach_limit;
	float origin;
	float acc_distance;

	float speed;

	int state;  // 0: final, 1: acc, 2: Vcte, 3: Decell
}QUADRAMP_data;

//////////////////////////////////////////////
// Function definitions
//////////////////////////////////////////////
void TaskAsser_Main(void *p_arg);
	// Fonction principal du process d'asservissement
	// void *p_arg		: Arg for this task


#endif //TASKASSER_H
