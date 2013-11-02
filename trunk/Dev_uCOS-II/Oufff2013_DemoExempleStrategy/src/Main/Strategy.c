/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : Strategy.c
*
* Suivi de version :
* 2011-11-17 | PBE | Creation de la version de base pour la coupe 2012
*********************************************************************************************************
*/

#include "Strategy.h"
#include "Strategy/StrategyFromColor.h"
#include "LibMoving.h"

// ------------------------------------------------------------------------------------------------
INT8U Strategy_GetInitCmd(EnumColor CurrentColor, StructCmd *InitCmd)
{
	INT8U Ret = ERR__NO_ERROR;

	if(NULL == InitCmd)
		return ERR__INVALID_PARAM;

	switch(CurrentColor)
	{
	case c_ColorA:	// ##################################################
		Ret = StrategyColorA_GetInitCmd(InitCmd);
		break;

	case c_ColorB:	// ##################################################
		Ret = StrategyColorB_GetInitCmd(InitCmd);
		break;

	default:		// ##################################################
		InitCmd = NULL;
		Ret = ERR__INVALID_PARAM;
		break;
	}

	return Ret;
}



// ------------------------------------------------------------------------------------------------
INT8U Strategy_GetNextAction(EnumColor CurrentColor, StructCmd *NextAction)
{
	INT8U Ret = ERR__NO_ERROR;

	if(NULL == NextAction)
		return ERR__INVALID_PARAM;

	switch(CurrentColor)
	{
	case c_ColorA:	// ##################################################################
		Ret = StrategyColorA_GetNextAction(NextAction);
		break;

	case c_ColorB:	// ##################################################################
		Ret = StrategyColorB_GetNextAction(NextAction);
		break;

	default:		// ##################################################################
		break;
	}

	return Ret;
}


