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

#include <AppIncludes.h>
#include "AppGlobalVars.h"

#define KP_ANGLE 				50000.0		// Oscillations de 2s environ
#define KI_ANGLE 				0.0
#define KD_ANGLE 				350000.0
#define IMAX_ANGLE 				1000.0

#define VMAX_ANGLE				10000.0
#define ACC_ANGLE				20000.0


#define KP_DISTANCE 			200.0
#define KI_DISTANCE 			0.0
#define KD_DISTANCE 			1500.0
#define IMAX_DISTANCE 			1000.0

#define VMAX_DISTANCE			1.0
#define ACC_DISTANCE			2.0

#define PID_SUM_NB_SAMPLES 		10		// 1000 à l'origine CBE
#define PID_D_PERIOD			1		//100 à l'origine CBE

#define MAX_MOTOR_COMMAND 		32000	// doit être < à 32768

#define ANGLE_CONTROL_INIT 		OS_TRUE; //OS_FALSE;
#define DISTANCE_CONTROL_INIT 	OS_TRUE; //OS_FALSE;
#define DISTANCE_ALPHA_ONLY		50.0

#define ANGLE_VS_DISTANCE_RATIO	0.5 // n % used for angle on full scale
#define SPEED_RATIO				1.0 // n % of maximum speed

// Vars -------------------------------------------------------------------------------------------
struct StructPos TaskAsser_CurrentPos;							// Local var to read current pos


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

	float max_acceleration;
	float max_speed;

	float previous_speed;
	float previous_position;
}SLEWRATE_data;

void TaskAsser_Main(void *p_arg);
	// Fonction principal du process d'asservissement
	// void *p_arg		: Arg for this task


#endif //TASKASSER_H
