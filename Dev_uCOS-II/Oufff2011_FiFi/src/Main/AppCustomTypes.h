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

// DEFINE ################################################################
#define	WAIT_FOREVER			0		// Define for Timeout

#define RIGHT_WHEEL				1		// Used for pivot mode
#define LEFT_WHEEL				-1		// Used for pivot mode

// ENUM ##################################################################
// Color ----------------------------------------
typedef enum
{
	c_NotSet = -1,
	c_ColorA,
	c_ColorB,
}EnumColor;

// Mvt Mode -------------------------------------
typedef enum
{
	MvtMode_NotSet = 0,			// Current MvtMode is not set
	MvtMode_AngleOnly,			// Use Asser Mode 1
	MvtMode_DistOnly,			// Use Asser Mode 2
	MvtMode_MixedMode,			// Use Asser Mode 3
	MvtMode_PivotMode,			// Use Asser Mode 4
	MvtMode_Simple,				// Used a simple mvt (don't divide this mvt)
	MvtMode_DontMove,			// Don't move for this mvt
}EnumMvtMode;

// Msg Type -------------------------------------
typedef enum
{								// Dest		| Details																
	Msg_NoMsg = 0,				// None		| To send a NULL msg (not used)											
	Msg_Mvt_MsgType = 100,		// None		| Asser Msg																
	Msg_Mvt_MoveMode1,			// Mvt		| Go to specified angle (Mode 1 = Angle only)
	Msg_Mvt_MoveMode2,			// Mvt		| Go to specified (x,y) position (Mode 2 = Dist only)							
	Msg_Mvt_MoveMode3,			// Mvt		| Go to specified (x,y,a) position (Mode 3 = Mixed Mode)
	Msg_Mvt_MoveMode4,			// Mvt		| Rotate around specified wheel (Mode 4 = Pivot Mode)
	Msg_Mvt_SetCurrentPos,		// Mvt		| Define a new current position
}EnumMsgType;

// STRUCT ################################################################
// Position -------------------------------------
typedef struct
{
	float 		x;					// Pos en x
	float 		y;					// Pos en y
	float 		angle;				// Angle
	CPU_INT16U	right_encoder;		// Right wheel position for mode 4
	CPU_INT16U	left_encoder;		// Left wheel position for mode 4
	char		CurrentState;		// Flag for storing current mvt state
}StructOdoPos;

typedef struct
{
	int MvtMode;				// Mode used to go to next major point
	// MvtMode Type				   Simple			| DontMove	| AngleOnly		| DistOnly		| MixedMode		| PivotMode		|
	short 	Param1;				// Speed(1-100)		| Not Used	| Speed(1-100)	| Speed(1-100)	| Speed(1-100)	| Speed(1-100)	|
	float 	Param2;				// x				| Not Used	| Not Used		| x				| x				| Wheel to lock	|
	float 	Param3;				// y				| Not Used	| Not Used		| y				| y				| Not Used		|
	float	Param4;				// angle			| Not Used	| angle			| Not Used		| angle			| angle			|
	int 	ActiveSensorsFlag;	// Define which sensors we have to use for this movement (if not set, use all external sensors)
}StructMvtPos;

// Msg ------------------------------------------
typedef struct 
{
	EnumMsgType MsgType;	// Msg Type (Msg_NoMsg: Invalid Msg)																					
	BOOLEAN IsRead;		// Flag to indicate if current msg has been read or not																	
	// Msg Parameters	:	Asser_MoveMode1	| Asser_MoveMode2	| Asser_MoveMode3	| Asser_MoveMode4	| Mvt_SetCurrentPos	|
	short Param1;		//	Speed (1-100)	| Speed (1-100)		| Speed (1-100)		| Speed (1-100)		| Not Used			|
	float Param2;		//	Not Used		| x					| x					| Wheel to lock		| x					|
	float Param3;		//	Not Used		| y					| y					| Not Used			| y					|
	float Param4;		//	Angle In Rad	| Not Used			| Angle In Rad		| Angle In Rad		| Angle In Rad		|
}StructMsg;

#endif // APPCUSTOMTYPES_H
