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
OS_EVENT	*AppQueueMainEvent;						// Queue for Main task
OS_EVENT	*AppQueueAsserEvent;					// Queue for Asser task

#if APP_QUEUE_MAIN_SIZE > 0
void*		AppQueueMainStk[APP_QUEUE_MAIN_SIZE];	// Stack to store pointer to msg for Main Queue
#endif
#if APP_QUEUE_ASSER_SIZE > 0
void*		AppQueueAsserStk[APP_QUEUE_ASSER_SIZE];	// Stack to store pointer to msg for Asser Queue
#endif

StructMsg	AppMsgStk[APP_QUEUE_MAIN_SIZE + APP_QUEUE_ASSER_SIZE];	// Stack to store msg for Asser and Main Queue
StructMsg	AppHighPrioMsg;							// Struct to store an high priority msg (e.g. the stop msg)
INT8U		AppMsgCurrentID;						// Next free ID for msg

/***** Structures *****/
StructPos	AppCurrentPos;							// Contains current postion (set by TaskOdo, read by Main)

/***** Enums *****/
EnumColor	CurrentColor;							// Var to contain Color

/***** MUTEX / SEMAPHORES *****/
OS_EVENT	*Mut_AppCurrentPos;						// Mutex to limit access (RW) for CurrentPos variable

/***** FLAGS *****/
OS_FLAG_GRP		*AppFlags;							// Contains all flags for the app							

#endif // APP_H
