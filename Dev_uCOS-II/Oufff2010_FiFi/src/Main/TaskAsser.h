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

#define KP_ANGLE 				10000.0
#define KI_ANGLE 				0.0
#define KD_ANGLE 				0.0
#define IMAX_ANGLE 				1000.0

#define VMAX_ANGLE				10000.0
#define ACC_ANGLE				20000.0


#define KP_DISTANCE 			100.0
#define KI_DISTANCE 			1.0
#define KD_DISTANCE 			0.0
#define IMAX_DISTANCE 			1000.0

#define VMAX_DISTANCE			10000.0
#define ACC_DISTANCE			20000.0

#define PID_SUM_NB_SAMPLES 		1000
#define PID_D_PERIOD			100

#define MAX_MOTOR_COMMAND 		30000

#define ANGLE_CONTROL_INIT 		OS_FALSE;
#define DISTANCE_CONTROL_INIT 	OS_TRUE;

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
