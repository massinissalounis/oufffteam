/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : LibMoving.c
*
* Suivi de version :
* 2009-04-08 | PBE | Creation de la version de base pour la coupe 2010
*********************************************************************************************************
*/

#include "LibMoving.h"
#include "mathf.h"
#include "math.h"

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveInMM(StructPos *OldPos, int dist, StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new position
	NewPos->x = OldPos->x + dist * cosf(OldPos->angle);
	NewPos->y = OldPos->y + dist * sinf(OldPos->angle);
	NewPos->angle = OldPos->angle;

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_RotateInDeg(StructPos *OldPos, float AngleInDeg, StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = OldPos->angle + AppConvertDegInRad(AngleInDeg);

	return;
}

// ------------------------------------------------------------------------------------------------
void LibMoving_MoveToAngleInDeg(StructPos *OldPos, float AngleToGoInDeg, StructPos *NewPos)
{
	// Check params
	if((NULL == OldPos) || (NULL == NewPos))
		return;

	// Compute new angle
	NewPos->x = OldPos->x;
	NewPos->y = OldPos->y; 
	NewPos->angle = AppConvertDegInRad(AngleToGoInDeg);

	return;
}

