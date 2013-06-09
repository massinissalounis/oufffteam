/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskDetection.h
*********************************************************************************************************
*/

#ifndef TASKDETECTION_H
#define TASKDETECTION_H

#include "AppIncludes.h"

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/


#define KP_BEACON_MOTOR_SPEED			75.0
#define KI_BEACON_MOTOR_SPEED	 		0.0
#define KD_BEACON_MOTOR_SPEED	 		0.0
#define IMAX_BEACON_MOTOR_SPEED 		0.0

#define BEACON_MOTOR_SPEED_SETPOINT		9.0 // in Hz

#define BEACON_MOTOR_SAMPLING_PERIOD		TMR2_TICK // in s
#define BEACON_MOTOR_INCREMENTS_PER_REVOLUTION	1408 // See Motor Datasheet and FPGA code	

#define BEACON_MOTOR_SPEED_SETPOINT_IN_INC	(BEACON_MOTOR_SPEED_SETPOINT*BEACON_MOTOR_INCREMENTS_PER_REVOLUTION)*BEACON_MOTOR_SAMPLING_PERIOD

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/  

// fonctions publiques ----------------------------------------------------------------------------
void TaskDetection_Main(void *p_arg);
	// Main function for detecting other robot
	// void *p_arg		: Arg for this task

#endif // TASKDETECTION_H
