/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : AppGlobalFunc.c
*
* Suivi de version :
* 2009-03-26 | PBE | Creation de la version de base pour la coupe 2010
*********************************************************************************************************


*/

#include "AppIncludes.h"
#include "AppGlobalFunc.h"
#include "AppGlobalVars.h"

// ------------------------------------------------------------------------------------------------
BOOLEAN AppPostQueueMsg(OS_EVENT *PtrQueue, StructMsg *PtrMsgToPost)
{
	static INT8U CurrentIndex = 0;
	int i, NextFreeIndex;
	char uart_buffer[13];
	char * buffer_ptr;

	// Check param
	if((NULL == PtrQueue) || (NULL == PtrMsgToPost))
		return;

	// Initialisation
	NextFreeIndex = -1;
	i = 0;
	
	// Search for free place
	while((i<APP_QUEUES_TOTAL_SIZE) && (-1 == NextFreeIndex))
	{
		if(CurrentIndex >= APP_QUEUES_TOTAL_SIZE)
			CurrentIndex = CurrentIndex - APP_QUEUES_TOTAL_SIZE;

		if(OS_TRUE == AppMsgStk[CurrentIndex].IsRead)
			NextFreeIndex = CurrentIndex;

		CurrentIndex++;
		i++;
	}

	// If NextFreeIndex is set to -1, no free place are available, msg can't be sent 
	// otherwise we create the msg
	if(NextFreeIndex >= 0)
	{
		// Create Msg
		AppMsgStk[NextFreeIndex].IsRead	=	OS_FALSE;				// Msg is unread
		AppMsgStk[NextFreeIndex].Msg	=	PtrMsgToPost->Msg;		// Msg to post 
		AppMsgStk[NextFreeIndex].Param1	=	PtrMsgToPost->Param1;	// Param1
		AppMsgStk[NextFreeIndex].Param2	=	PtrMsgToPost->Param2;	// Param2
		AppMsgStk[NextFreeIndex].Param3	=	PtrMsgToPost->Param3;	// Param3

		// Post Msg
		OSQPost(PtrQueue, (void*)(&(AppMsgStk[NextFreeIndex])));
		#ifdef _TARGET_STARTER_KIT
			LED_Toggle(2);
		#endif

		return OS_TRUE;
	}
	else
	{
		putsUART2("AppGlobalFunc : Queue Full !!!\n");
		return OS_FALSE;
	}

	return OS_FALSE;
}

// ------------------------------------------------------------------------------------------------
float AppConvertRadInDeg(float ValueInRad)
{
	// Conversion
	return AppCheckAngleInDeg((ValueInRad * 180.0) / M_PI);
}

// ------------------------------------------------------------------------------------------------
float AppConvertDegInRad(float ValueInDeg)
{
	float tmp;
	// Conversion
	tmp = (ValueInDeg * M_PI) / 180.0;
	tmp = AppCheckAngleInRad(tmp);
	return tmp;
}

// ------------------------------------------------------------------------------------------------
float AppCheckAngleInRad(float ValueToCheck)
{
	// Check if value is less than PI rad
	while(ValueToCheck >= M_PI)
		ValueToCheck = ValueToCheck - 2*M_PI;

	// Check if value is more than -PI rad
	while(ValueToCheck < -M_PI)
		ValueToCheck = ValueToCheck + 2*M_PI;

	return ValueToCheck;
}

// ------------------------------------------------------------------------------------------------
float AppCheckAngleInDeg(float ValueToCheck)
{
	// Check if value is less than 180 deg
	while(ValueToCheck >= 180.0)
		ValueToCheck = ValueToCheck - 360.0;

	// Check if value is more than -180 deg
	while(ValueToCheck <= -180.0)
		ValueToCheck = ValueToCheck + 360.0;

	return ValueToCheck;
}
