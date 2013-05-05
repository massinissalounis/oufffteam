/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : TaskOdo.h
*********************************************************************************************************
*/

#ifndef TASKODO_H
#define TASKODO_H

#include "AppIncludes.h"

// Conversion factor : determined imperically
// !Calibration methodology!
// 1- Measure increments of encoders for a know distance
// Use several trials to average correctly and compute a first estimation of left and right factors : factor = nb of incs / distance (mm)
// 2- Measure entraxe to determine conversion factor for angle
// 3- Do several trials to refine factors in angle
// First correct angle in right line : if angle +, reduces left factor (because factor scales in 1/x)
// Then correct distance by proportionality :
// current_distance --- coeff 1 ---> distance_to_reach
// current left factor --- coeff 2 ---> current right factor
// new right factor = current right factor * coeff 1 * coeff2

// For distance of 2600 mm, we add 55771 increments on encoder right (21.4504) and 55832 increments on encoder left (21.4738)
#define CONVERSION_MM_TO_INC_RIGHT  (float)(21.4504)		// Coupe 2012 : (21.4338)
#define CONVERSION_MM_TO_INC_LEFT	(float)(21.4738)		// Coupe 2012 : (21.4085)

// For an angle of = entraxe
#define CONVERSION_RAD_TO_MM	(float)(273.1)

// For movement detection
#define MOVEMENT_DETECTION_INTERVAL				20 // in 10ms
#define MOVEMENT_DETECTION_ANGLE_THRESHOLD		(1.00 * M_PI / 180.0) // in angle
#define MOVEMENT_DETECTION_DISTANCE_THRESHOLD	10 // in mm

unsigned char movement_detection();

INT8U	TaskOdo_GetCurrentPos(StructPos *CurrentPos);
	// Function for reading current odo position
	// *CurrentPos = Pointer for storing current value
	// Returns :	- ERR__NO_ERROR if no error
	//				- ERR__INVALID_PARAM if CurrentPos is not set

INT8U	TaskOdo_SetCurrentPos(StructPos *NewPos);
	// Function for setting odo position
	// *CurrentPos = Pointer containing new position
	// Returns :	- ERR__NO_ERROR if no error
	//				- ERR__INVALID_PARAM if CurrentPos is not set

void	TaskOdo_Main(void *p_arg);
	// Fonction principal du process d'odométrie
	// void *p_arg		: Arg for this task

#endif // TASKODO_H
