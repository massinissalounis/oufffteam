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
extern OS_EVENT			*AppQueueMvt;							// Queue for storing msg from TaskMain to TaskMvt
extern OS_EVENT			*AppQueueSensors;						// Queue for storing msg from TaskMain to TaskSensors

#if APP_QUEUE_MVT_SIZE > 0
extern void*			AppQMvtStk[APP_QUEUE_MVT_SIZE];			// Stack to store pointer to msg for Mvt Queue
#endif
#if APP_QUEUE_SENSORS_SIZE > 0
extern void*			AppQSensorsStk[APP_QUEUE_SENSORS_SIZE];	// Stack to store pointer to msg for Sensors Queue
#endif

extern StructMsg		AppMsgStk[APP_QUEUES_TOTAL_SIZE];		// Stack to store msg for all Queues
extern StructMsg		AppHighPrioMsg;							// Struct to store an high priority msg (e.g. the stop msg)

/***** Structures *****/
extern StructOdoPos		AppCurrentPos;							// Contains current postion (set by TaskOdo, used by Main)
	
/***** Enum *****/
extern EnumColor		AppCurrentColor;						// Contains current color (read from bsp)

/***** MUTEX / SEMAPHORES *****/
extern OS_EVENT			*Mut_AppCurrentPos;						// Mutex to limit access (RW) for CurrentPos variable

/***** FLAGS *****/
extern OS_FLAG_GRP		*AppFlags;								// Contains all flags for this application							

#endif // APPGLOBALVARS_H
