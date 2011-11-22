/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : StrategyFromColor.h
*********************************************************************************************************
*/

#ifndef STRATEGYFROMCOLOR_H
#define STRATEGYFROMCOLOR_H

#include "AppIncludes.h"

// Color A ----------------------------------------------------------------------------------------
INT8U StrategyColorA_GetInitCmd(StructCmd *InitCmd);
// Function to obtain initial Color A command 
// InitCmd		: Pointer to store initial command (this command defines the initial pos)
// In case of error, InitCmd is not set

INT8U StrategyColorA_GetNextAction(StructCmd *NextAction);
// Function to obtain next action for Color A
// NextAction	: Pointer to store next action (in case of error, NextAction is not modified)

// Color B ----------------------------------------------------------------------------------------
INT8U StrategyColorB_GetInitCmd(StructCmd *InitCmd);
// Function to obtain initial Color A command 
// InitCmd		: Pointer to store initial command (this command defines the initial pos)
// In case of error, InitCmd is not set

INT8U StrategyColorB_GetNextAction(StructCmd *NextAction);
// Function to obtain next action for Color A
// NextAction	: Pointer to store next action (in case of error, NextAction is not modified)

#endif // STRATEGYFROMCOLOR_H
