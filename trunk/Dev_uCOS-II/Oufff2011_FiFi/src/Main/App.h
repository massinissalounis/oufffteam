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

/***** Queue *****/
OS_EVENT	*AppQueueMvt;						// Queue for storing msg from TaskMain to TaskMvt
OS_EVENT	*AppQueueSensors;					// Queue for storing msg from TaskMain to TaskSensors

#if APP_QUEUE_MAIN_SIZE > 0
void*		AppQueueMainStk[APP_QUEUE_MAIN_SIZE];	// Stack to store pointer to msg for Main Queue
#endif
#if APP_QUEUE_ASSER_SIZE > 0
void*		AppQueueAsserStk[APP_QUEUE_ASSER_SIZE];	// Stack to store pointer to msg for Asser Queue
#endif

StructMsg	AppMsgStk[APP_QUEUES_TOTAL_SIZE];		// Stack to store msg for Asser and Main Queue
StructMsg	AppHighPrioMsg;							// Struct to store an high priority msg (e.g. the stop msg)

/***** Structures *****/
struct StructPos	AppCurrentPos;					// Contains current postion (set by TaskOdo, read by Main)

/***** Enums *****/
EnumColor	AppCurrentColor;						// Var to contain Color

/***** MUTEX / SEMAPHORES *****/
OS_EVENT	*Mut_AppCurrentPos;						// Mutex to limit access (RW) for CurrentPos variable

/***** FLAGS *****/
OS_FLAG_GRP		*AppFlags;							// Contains all flags for the app							

#endif // APP_H
