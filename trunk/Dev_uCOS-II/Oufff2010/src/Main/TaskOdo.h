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

#include <AppIncludes.h>

// Conversion factor : determined imperically
// !Calibration methodology!
// 1- Measure increments of encoders for a know distance
// Use several trials to average correctly and compute a first estimation of left and right factors : factor = distance (mm) / nb of incs
// 2- Measure entraxe to determine conversion factor for angle
// 3- Do several trials to refine factors in angle
// First correct angle in right line : if angle +, reduces left factor (because factor scales in 1/x)
// Then correct distance by proportionality :
// current_distance --- coeff 1 ---> distance_to_reach
// current left factor --- coeff 2 ---> current right factor
// new right factor = current right factor * coeff 1 * coeff2

// For distance of 748.5 mm, we add 22632 increments on encoder right and 22613 increments on encoder left
#define CONVERSION_MM_TO_INC_LEFT	(float)(30.225) //30.111
#define CONVERSION_MM_TO_INC_RIGHT  (float)(29.74) // 29.627
// Values storage !
// coupe nuit 12 mai : L = 30.21, R = 29.74
// matin 13 mai (reglage angle sans correction distance) : L = 30.225, R = 29.74


// For an angle of = entraxe
#define CONVERSION_RAD_TO_MM	(float)97.0

void TaskOdo_Main(void *p_arg);
	// Fonction principal du process d'odométrie
	// void *p_arg		: Arg for this task

#endif // TASKODO_H
