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

//////////////////////////////////////////////
// PID Coefficients
//////////////////////////////////////////////

// Angle loop for theta-alpha
#define KP_ANGLE 				50000.0		// Oscillations de 2s environ
#define KI_ANGLE 				0.0
#define KD_ANGLE 				350000.0
#define IMAX_ANGLE 				1000.0

// Distance loop for theta-alpha
#define KP_DISTANCE 			200.0
#define KI_DISTANCE 			0.0
#define KD_DISTANCE 			1500.0
#define IMAX_DISTANCE 			1000.0

// Wheel loop for separated control
#define KP_WHEEL	 			200.0
#define KI_WHEEL	 			0.0
#define KD_WHEEL	 			1500.0
#define IMAX_WHEEL	 			1000.0

// Generic parameters
#define PID_SUM_NB_SAMPLES 		3		// 1000 à l'origine CBE
#define PID_D_PERIOD			1		//100 à l'origine CBE

//////////////////////////////////////////////
// Speed control Coefficients
//////////////////////////////////////////////

// Used in quadramp
#define DEFAULT_SPEED_DISTANCE	1.0		// n % of maximum speed
#define DEFAULT_ACC_DISTANCE	1.0		// n % of maximum speed per 10 ms

// Used in hold speed control
#define SPEED_ANGLE		1.0 	// n % of maximum speed

//////////////////////////////////////////////
// General Coefficients
//////////////////////////////////////////////

#define MAX_MOTOR_COMMAND 		32000	// doit être < à 32768

#define DISTANCE_ALPHA_ONLY		50.0

#define ANGLE_VS_DISTANCE_RATIO	0.5 // n % used for angle on full scale

#define ASSER_SAMPLING		10 // in ms

//////////////////////////////////////////////
// Global Vars Coefficients
//////////////////////////////////////////////
struct StructPos TaskAsser_CurrentPos;							// Local var to read current pos

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
