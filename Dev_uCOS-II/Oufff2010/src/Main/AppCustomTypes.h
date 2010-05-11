/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppCustomTypes.h
*********************************************************************************************************
*/

#ifndef APPCUSTOMTYPES_H
#define APPCUSTOMTYPES_H

#include "AppConfig.h"

// DEFINE ################################################################
#define	WAIT_FOREVER			0		// Define for Timeout

// ENUM ##################################################################
// Color ----------------------------------------
typedef enum
{
	c_NotSet = -1,
	c_Black,
	c_Red,
	c_Blue,
	c_Green,
	c_Yellow
}EnumColor;

// Msg Type -------------------------------------
typedef enum
{								// Dest		| Details																
	Msg_NoMsg = 0,				// None		| To send a NULL msg (not used)											
	Msg_Asser_MsgType = 100,	// None		| Asser Msg																
	Msg_Asser_GoToXYA,			// Asser	| Msg to give a new position setpoint in XYA coord						
	Msg_Asser_Algo,				// Asser	| Msg to choose which algo we want to use								
	Msg_Asser_SetSpeed,			// Asser	| Msg to set robot speed (value is from 0 (no move) to 1 (full speeed)
}EnumMsg;

// STRUCT ################################################################
// Position -------------------------------------
 struct StructPos
{
	float 	x;			// Pos en x
	float 	y;			// Pos en y
	float 	angle;		// Angle
	int		Flag;		// Flag for this position
						// Use APP_FLAG_POS__... to make a Flag value
};

// Msg ------------------------------------------
typedef struct
{
	EnumMsg Msg;		// Msg to be sent (Msg_NoMsg: Invalid Msg)																					
	BOOLEAN IsRead;		// Flag to indicate if current msg has been read or not																	
	// Msg Parameters	:  Msg_Asser_GoToXYA	| Msg_Asser_Algo								| Msg_Asser_SetSpeed								
	float Param1;		// X					| Set to use Asser In Pos (Clear otherwise)		| Speed rate (between 0 and 1.0)
	float Param2;		// Y					| Set to use Asser In Angle (Clear otherwise)	| Not Used
	float Param3;		// ALPHA				| Set to use Asser In Speed (Not Used Yet)		| Not Used
}StructMsg;

#endif // APPCUSTOMTYPES_H