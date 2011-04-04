/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : App.h
*********************************************************************************************************
*/

#ifndef APP_H
#define APP_H 

#include "AppIncludes.h"

/***** Queue *****/
OS_EVENT		*AppQueueMvt;							// Queue for storing msg from TaskMain to TaskMvt
OS_EVENT		*AppQueueSensors;						// Queue for storing msg from TaskMain to TaskSensors

#if APP_QUEUE_MVT_SIZE > 0
void*			AppQMvtStk[APP_QUEUE_MVT_SIZE];			// Stack to store pointer to msg for Mvt Queue
#endif
#if APP_QUEUE_SENSORS_SIZE > 0
void*			AppQSensorsStk[APP_QUEUE_SENSORS_SIZE];	// Stack to store pointer to msg for Sensors Queue
#endif

StructMsg		AppMsgStk[APP_QUEUES_TOTAL_SIZE];		// Stack to store msg for all Queues
StructMsg		AppHighPrioMsg;							// Struct to store an high priority msg (e.g. the stop msg)

/***** Structures *****/
StructOdoPos	AppCurrentPos;							// Contains current postion (set by TaskOdo, used by Main)

/***** Enum *****/
EnumColor		AppCurrentColor;						// Contains current color (read from bsp)

/***** MUTEX / SEMAPHORES *****/
OS_EVENT		*Mut_AppCurrentPos;						// Mutex to limit access (RW) for CurrentPos variable

/***** FLAGS *****/
OS_FLAG_GRP		*AppFlags;								// Contains all flags for this application							

#endif // APP_H
