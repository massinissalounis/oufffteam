/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppGlobalFunc.h
*********************************************************************************************************
*/

#ifndef APPGLOBALFUNC_H
#define APPGLOBALFUNC_H 

void AppDebugMsg(char *DebugMsg);
	// Generic function to display a message on serial port
	// DebugMsg		: Msg to send on serial port

BOOLEAN AppPostQueueMsg(OS_EVENT *PtrQueue, StructMsg *PtrMsgToPost);
	// Generic funct to post a msg into a queue
	// PtrQueue		: Pointer to Queue
	// PtrMsgToPost	: Pointer to msg to post
	// Returns OS_TRUE if msg is sent, OS_FALSE if msg is waiting for transmit

float AppConvertRadInDeg(float ValueInRad);	
	// Funct to convert an angle in Rad to an angle in Deg
	// ValueInRad : Angle to convert

float AppConvertDegInRad(float ValueInDeg);	
	// Funct to convert an angle in Rad to an angle in Deg
	// ValueInDeg : Angle to convert

float AppCheckAngleInRad(float ValueToCheck);
	// Funct to check if specified angle is between -M_PI and +M_PI
	// ValueToCheck : Angle to check

float AppCheckAngleInDeg(float ValueToCheck);
	// Funct to check if specified angle is between -M_PI and +M_PI
	// ValueToCheck : Angle to check

INT8U AppGetCurrentPos(StructPos *CurrentPos);
	// Function for reading current odo position
	// *CurrentPos = Pointer for storing current value
	// Returns :	- ERR__NO_ERROR if no error
	//				- ERR__INVALID_PARAM if CurrentPos is not set or if TaskOdo is not running


#endif // APPGLOBALFUNC_H

