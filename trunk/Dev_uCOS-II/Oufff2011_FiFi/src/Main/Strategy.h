/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : Strategy.h
*********************************************************************************************************
*/

#ifndef STRATEGY_H
#define STRATEGY_H

#include "AppIncludes.h"

INT8U Strategy_GetInitCmd(EnumColor CurrentColor, StructCmd *InitCmd);
// Function to obtain initial command (defined by color)
// CurrentColor	: Color read from TaskSensors
// InitCmd		: Pointer to store initial command (this command defines the initial pos)
// In case of error, InitCmd is not set

INT8U Strategy_GetNextAction(StructCmd *NextAction);
// Function to obtain next action
// NextAction	: Pointer to store next action (in case of error, NextAction is not modify)


#endif // STRATEGY_H
