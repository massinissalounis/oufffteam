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
// For distance of 748.5 mm, we add 22632 increments on encoder right and 22613 increments on encoder left
#define CONVERSION_MM_TO_INC_LEFT	(float)(30.21)
#define CONVERSION_MM_TO_INC_RIGHT  (float)(29.74)
// For an angle of = entraxe
#define CONVERSION_RAD_TO_MM	(float)97.0

void TaskOdo_Main(void *p_arg);
	// Fonction principal du process d'odométrie
	// void *p_arg		: Arg for this task

#endif // TASKODO_H
