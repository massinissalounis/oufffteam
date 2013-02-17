/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskOdo.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************
*/

#include "TaskOdo.h"
#include "AppGlobalVars.h"

StructPos TaskOdo_CurrentPos;

/***** MUTEX / SEMAPHORES *****/
OS_EVENT	*SemOdo = NULL;
OS_EVENT	*MutexCurrentPos = NULL;				// Mutex to limit access (RW) for CurrentPos variable

extern float error_debug_1;
extern float error_debug_2;
extern float error_debug_3;
extern float error_debug_4;
extern float error_debug_5;

extern INT8U Debug_MainState;
extern INT8U Debug_MvtState;
extern INT8U Debug_AsserRampState;

// Initialize data types
// Struc position
// Impulsed position
	CPU_INT16S QUADD_delta;
	CPU_INT16S QUADG_delta;
	CPU_INT16U QUADD_data;
	CPU_INT16U QUADG_data;
	CPU_INT16U QUADD_data_old;
	CPU_INT16U QUADG_data_old;

// ------------------------------------------------------------------------------------------------
void init_position_manager()
{
	// init datas
	TaskOdo_CurrentPos.x		= 0;
	TaskOdo_CurrentPos.y		= 0;
	TaskOdo_CurrentPos.angle	= 0;
	
	// For mode 4
	TaskOdo_CurrentPos.right_encoder	= 0;
	TaskOdo_CurrentPos.left_encoder		= 0;
}

// ------------------------------------------------------------------------------------------------
void encoders_calibration_measure(void)
{
	static int	i = 0; // Refresh sending UART
	static		CPU_INT16U QUADD_data_old	= 0;
	static		CPU_INT16U QUADG_data_old	= 0;
	static		CPU_INT32S QUADD_count		= 0;
	static		CPU_INT32S QUADG_count		= 0;
	char		uart_buffer[13];
	char		*buffer_ptr;


	CPU_INT16S QUADD_delta	= 0;
	CPU_INT16S QUADG_delta	= 0;

	// Wait for latch to finish 
	QUAD_Wait_for_Latch();

	// Read values from encoders
	QUADD_data = QUADD_Read();
	QUADG_data = QUADG_Read();

	// Compute Delta of increments
	QUADD_delta = QUADD_data - QUADD_data_old;
	QUADG_delta = -(QUADG_data - QUADG_data_old);

	QUADD_count += QUADD_delta;
	QUADG_count += QUADG_delta;

	// Store increments for next computation
	QUADD_data_old = QUADD_data;
	QUADG_data_old = QUADG_data;

	if(i==0)
	{
		AppDebugMsg("ODO_CALIBRATION : ");
		AppDebugMsg("QUADD : ");
		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) QUADD_count, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
		AppDebugMsg(buffer_ptr);
		AppDebugMsg(",QUADG : ");
		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) QUADG_count, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
		AppDebugMsg(buffer_ptr);
		AppDebugMsg("\n");
	}
	i++;
	if(i==50) i=0;
}

// ------------------------------------------------------------------------------------------------
void position_manager_process()
{
	INT8U		Err;

	float QUADD_delta_mm	= 0.0;
	float QUADG_delta_mm	= 0.0;

	float Quad_moy			= 0.0;
	float Quad_diff			= 0.0;
	float Quad_moy_mm		= 0.0;
	float Quad_diff_rad		= 0.0;
	float Delta_x			= 0.0;
	float Delta_y			= 0.0;
	float Delta_angle		= 0.0;

	// Wait for latch to finish 
	QUAD_Wait_for_Latch();

	// Read values from encoders
	QUADD_data = QUADD_Read();
	QUADG_data = QUADG_Read();

	// Compute Delta of increments
	QUADD_delta = QUADD_data - QUADD_data_old;
	QUADG_delta = -(QUADG_data - QUADG_data_old);

	QUADD_delta_mm = QUADD_delta / CONVERSION_MM_TO_INC_RIGHT;
	QUADG_delta_mm = QUADG_delta / CONVERSION_MM_TO_INC_LEFT;

	// Convert in mm and radians
	Quad_moy_mm =	(QUADD_delta_mm + QUADG_delta_mm) / 2;
	Quad_diff =		(QUADD_delta_mm - QUADG_delta_mm);
	Quad_diff_rad = Quad_diff / CONVERSION_RAD_TO_MM;
  
	// Compute trig aproximations
	Delta_x = Quad_moy_mm * cos(TaskOdo_CurrentPos.angle);
	Delta_y = Quad_moy_mm * sin(TaskOdo_CurrentPos.angle);	
	
	// Test on angle

	// Store new datas (with mutex !)
	// SECTION CRITIQUE
	OSMutexPend(MutexCurrentPos, WAIT_FOREVER, &Err);
	{
		TaskOdo_CurrentPos.x = TaskOdo_CurrentPos.x + Delta_x;
		TaskOdo_CurrentPos.y = TaskOdo_CurrentPos.y + Delta_y;
		TaskOdo_CurrentPos.angle = TaskOdo_CurrentPos.angle + Quad_diff_rad;

		if(TaskOdo_CurrentPos.angle>M_PI)
		{
			TaskOdo_CurrentPos.angle = TaskOdo_CurrentPos.angle - 2*M_PI;
		}
		else
		{
			if(TaskOdo_CurrentPos.angle<=-M_PI)
			{
				TaskOdo_CurrentPos.angle = TaskOdo_CurrentPos.angle + 2*M_PI; 
			}
		}		
	
		TaskOdo_CurrentPos.right_encoder = QUADD_data;
		TaskOdo_CurrentPos.left_encoder = QUADG_data;

		TaskOdo_CurrentPos.CurrentState = movement_detection();
	}
	// FIN SECTION CRITIQUE
	OSMutexPost(MutexCurrentPos);

	// Store increments for next computation
	QUADD_data_old = QUADD_data;
	QUADG_data_old = QUADG_data;
}

// ------------------------------------------------------------------------------------------------
void position_manager_timer_handler()
{
	// LATCH QUAD RESISTERS
	QUAD_Latch();
	
	// WAKE UP TASKS
	if(OSSemPost(SemOdo) == OS_NO_ERR)
	{
	//	LED_Toggle(4);
	}
}

// ------------------------------------------------------------------------------------------------
unsigned char movement_detection()
{
	static int count			= 0;

	static float x_old			= 0.0;
	static float y_old			= 0.0;
	static float angle_old		= 0.0;

	static unsigned char flag	= 0;

	count--;
	if(count <= 0)
	{
		count = MOVEMENT_DETECTION_INTERVAL;

		if(	fabs(TaskOdo_CurrentPos.angle - angle_old) < MOVEMENT_DETECTION_ANGLE_THRESHOLD &&
		   	fabs(TaskOdo_CurrentPos.y - y_old) < MOVEMENT_DETECTION_DISTANCE_THRESHOLD &&
			fabs(TaskOdo_CurrentPos.x - x_old) < MOVEMENT_DETECTION_DISTANCE_THRESHOLD )
		{
			flag = 1;
		}
		else 
			flag = 0;
	
		x_old = TaskOdo_CurrentPos.x;
		y_old = TaskOdo_CurrentPos.y;
		angle_old = TaskOdo_CurrentPos.angle;
	}

	return flag;
}


// ------------------------------------------------------------------------------------------------
INT8U	TaskOdo_GetCurrentPos(StructPos *CurrentPos)
{
	INT8U	Err = ERR__NO_ERROR;

	if((NULL == CurrentPos) || (NULL == MutexCurrentPos))
		return ERR__INVALID_PARAM;

	// Begin Critical Section
	OSMutexPend(MutexCurrentPos, WAIT_FOREVER, &Err);
	{	
		memcpy(CurrentPos, &TaskOdo_CurrentPos, sizeof(StructPos));
	}	
	OSMutexPost(MutexCurrentPos);
	// End Critical Section

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
INT8U	TaskOdo_SetCurrentPos(StructPos *NewPos)
{
	INT8U	Err = ERR__NO_ERROR;

	if((NULL == NewPos) || (NULL == MutexCurrentPos))
		return ERR__INVALID_PARAM;

	// Begin Critical Section
	OSMutexPend(MutexCurrentPos, WAIT_FOREVER, &Err);
	{	
		memcpy(&TaskOdo_CurrentPos, NewPos, sizeof(StructPos));
	}	
	OSMutexPost(MutexCurrentPos);
	// End Critical Section

	return ERR__NO_ERROR;
}

// ------------------------------------------------------------------------------------------------
void TaskOdo_Main(void *p_arg)
{
	INT8U err		= ERR__NO_ERROR;
	static int i	= 0;				// Refresh sending UART
	char uart_buffer[8];
	char *buffer_ptr;

	unsigned char no_movement_flag = 1;

	AppDebugMsg("OUFFF TEAM 2013 : Odo online\n");

	SemOdo = OSSemCreate(0);
	MutexCurrentPos = OSMutexCreate(APP_MUTEX_ODO_PRIO, &err);
	if((NULL == MutexCurrentPos) || (NULL == SemOdo))
	{
		AppDebugMsg("DEBUG (TaskOdo.c) : Error -> Unable to create Semaphore or Mutex\n");
		AppDebugMsg("DEBUG (TaskOdo.c) : Entering in sleeping mode...\n");	
		while(OS_TRUE)		// Infinite Loop
			OSTimeDlyHMSM(1, 0, 0, 0);		
	}

	#ifdef _TARGET_440H
		while(OS_TRUE)
		{
			OSTimeDlyHMSM(0, 0, 1, 0);		

			AppDebugMsg("ODO_PROCESS : ");
			AppDebugMsg("x : ");
			buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) TaskOdo_CurrentPos.x, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
			AppDebugMsg(buffer_ptr);
			AppDebugMsg(", y : ");
			buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) TaskOdo_CurrentPos.y, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
			AppDebugMsg(buffer_ptr);
			AppDebugMsg(", alpha : ");
			buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) (TaskOdo_CurrentPos.angle*180.0/M_PI), (CPU_INT08U) 3, (CPU_INT08U) 2, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
			AppDebugMsg(buffer_ptr);
			AppDebugMsg("\n");
		}
	#endif

	init_position_manager();

	TMR2_Init();

	while(OS_TRUE)
	{
		OSSemPend(SemOdo,100,&err);
		if(err==OS_NO_ERR)
		{
			#ifdef ODO_CALIBRATION
				encoders_calibration_measure();
			#else
				position_manager_process();

				//no_movement_flag = movement_detection();

				if(i==0)
				{
#ifdef APP_TASK_ODO_DISPLAY_POSITION
					AppDebugMsg("ODO_PROCESS Position = ");
					AppDebugMsg("x : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) TaskOdo_CurrentPos.x, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg(",\ty : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) TaskOdo_CurrentPos.y, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg(",\talpha : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) (TaskOdo_CurrentPos.angle*180.0/M_PI), (CPU_INT08U) 3, (CPU_INT08U) 2, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg(",\tMainState : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) Debug_MainState, (CPU_INT08U) 3, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg(",\tMvtState : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) Debug_MvtState, (CPU_INT08U) 3, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg(",\tRampState : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) Debug_AsserRampState, (CPU_INT08U) 1, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg("\n");
#endif
#ifdef APP_TASK_ODO_DISPLAY_DEBUG
					AppDebugMsg("Debug1 : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) error_debug_1, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg("\tDebug2 : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) error_debug_2, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg("\tDebug3 : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) error_debug_3, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg("\tDebug4 : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) error_debug_4, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg("\tDebug5 : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) error_debug_5, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					AppDebugMsg(buffer_ptr);
					AppDebugMsg("\n");
#endif
				}
				i++;
				if(i==50) i=0;
			#endif
		}

	}
}
