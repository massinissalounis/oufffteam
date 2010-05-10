/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
* File : AppGlobalVars.h
*********************************************************************************************************
*/

#ifndef APPGLOBALVARS_H
#define APPGLOBALVARS_H 

/***** Queue *****/
extern OS_EVENT		*AppQueueMainEvent;						// Queue for Main task
extern OS_EVENT		*AppQueueAsserEvent;					// Queue for Asser task

#if APP_QUEUE_MAIN_SIZE > 0
extern void*		AppMsgStkMain[APP_QUEUE_MAIN_SIZE];		// Stack to store msg for Main Queue
#endif

#if APP_QUEUE_ASSER_SIZE > 0
extern void*		AppMsgStkAsser[APP_QUEUE_ASSER_SIZE];	// Stack to unread msg for Asser Queue
#endif

extern StructMsg	AppMsgStk[APP_QUEUES_TOTAL_SIZE];		// Stack to store msg for Asser and Main Queue
extern StructMsg	AppHighPrioMsg;							// Struct to store an high priority msg (e.g. the stop msg)

/***** Structures *****/
extern struct StructPos		AppCurrentPos;

/***** Enums *****/
extern EnumColor	AppCurrentColor;						// Var to contain Color

/***** MUTEX / SEMAPHORES *****/
extern OS_EVENT		*Mut_AppCurrentPos;						// Mutex to limit access (RW) for AppCurrentPos variable

/***** FLAGS *****/
extern OS_FLAG_GRP	*AppFlags;								// Contains all flags for the app							

#endif // APPGLOBALVARS_H
