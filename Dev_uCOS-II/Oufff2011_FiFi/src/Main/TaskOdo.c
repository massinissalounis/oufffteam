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
*********************************************************************************************************
*/

#include "TaskOdo.h"

struct StructPos *pos;
OS_EVENT *SemOdo;

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
void init_position_manager(struct StructPos *p)
{
	// init structures
	pos=p;
	// init datas
	pos->x=0;
	pos->y=0;
	pos->angle=0;
	
	// For mode 4
	pos->right_encoder=0;
	pos->left_encoder=0;

}

// ------------------------------------------------------------------------------------------------
void encoders_calibration_measure(void)
{
	static CPU_INT16U QUADD_data_old = 0;
	static CPU_INT16U QUADG_data_old = 0;
	static CPU_INT32S QUADD_count = 0;
	static CPU_INT32S QUADG_count = 0;

//	CPU_INT16U QUADD_data=0;
//	CPU_INT16U QUADG_data=0;
	CPU_INT16S QUADD_delta=0;
	CPU_INT16S QUADG_delta=0;

	// Wait for latch to finish 
	QUAD_Wait_for_Latch();

	// Read values from encoders
	QUADD_data=QUADD_Read();
	QUADG_data=QUADG_Read();

	// Compute Delta of increments
	QUADD_delta = QUADD_data - QUADD_data_old;
	QUADG_delta = -(QUADG_data - QUADG_data_old);

	QUADD_count += QUADD_delta;
	QUADG_count += QUADG_delta;

	// Store increments for next computation
	QUADD_data_old=QUADD_data;
	QUADG_data_old=QUADG_data;

	static int i=0; // Refresh sending UART
	char uart_buffer[13];
	char * buffer_ptr;


	if(i==0)
	{
		putsUART2("ODO_CALIBRATION : ");
		putsUART2("QUADD : ");
		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) QUADD_count, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
		putsUART2(buffer_ptr);
		putsUART2(",QUADG : ");
		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) QUADG_count, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
		putsUART2(buffer_ptr);
		putsUART2("\n");
	}
	i++;
	if(i==50) i=0;
}

// ------------------------------------------------------------------------------------------------
void position_manager_process()
{
//	static CPU_INT16U QUADD_data_old = 0;
//	static CPU_INT16U QUADG_data_old = 0;

//	CPU_INT16S QUADD_delta=0;
//	CPU_INT16S QUADG_delta=0;

//	CPU_INT16U QUADD_data=0;
//	CPU_INT16U QUADG_data=0;

	INT8U		Err;

	float QUADD_delta_mm = 0.0;
	float QUADG_delta_mm = 0.0;

	float Quad_moy = 0.0;
	float Quad_diff = 0.0;
	float Quad_moy_mm = 0.0;
	float Quad_diff_rad = 0.0;
	float Delta_x = 0.0;
	float Delta_y = 0.0;
	float Delta_angle = 0.0;

	// Wait for latch to finish 
	QUAD_Wait_for_Latch();

	// Read values from encoders
	QUADD_data=QUADD_Read();
	QUADG_data=QUADG_Read();

	// Compute Delta of increments
	QUADD_delta = QUADD_data - QUADD_data_old;
	QUADG_delta = -(QUADG_data - QUADG_data_old);

	QUADD_delta_mm = QUADD_delta / CONVERSION_MM_TO_INC_RIGHT;
	QUADG_delta_mm = QUADG_delta / CONVERSION_MM_TO_INC_LEFT;

	// Convert in mm and radians
	Quad_moy_mm = (QUADD_delta_mm + QUADG_delta_mm) / 2;
	Quad_diff = (QUADD_delta_mm - QUADG_delta_mm);
	Quad_diff_rad = Quad_diff / CONVERSION_RAD_TO_MM;
  
	// Compute trig aproximations
	Delta_x = Quad_moy_mm * cos(pos->angle);
	Delta_y = Quad_moy_mm * sin(pos->angle);	
	
	// Test on angle

	// Store new datas (with mutex !)
	// SECTION CRITIQUE
	OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);
		pos->x = pos->x + Delta_x;
		pos->y = pos->y + Delta_y;
		pos->angle = pos->angle + Quad_diff_rad;

		if(pos->angle>M_PI)
		{
			pos->angle = pos->angle - 2*M_PI;
		}
		else
		{
			if(pos->angle<=-M_PI)
			{
				pos->angle = pos->angle + 2*M_PI; 
			}
		}		
	// FIN SECTION CRITIQUE
	
	pos->right_encoder=QUADD_data;;
	pos->left_encoder=QUADG_data;
	OSMutexPost(Mut_AppCurrentPos);

	// Store increments for next computation
	QUADD_data_old=QUADD_data;
	QUADG_data_old=QUADG_data;
}

// ------------------------------------------------------------------------------------------------
void position_manager_timer_handler()
{
	// LATCH QUAD RESISTERS
	QUAD_Latch();
	
	// WAKE UP TASKS
	if(OSSemPost(SemOdo)==OS_NO_ERR)
	{
		LED_Toggle(4);
	}
}

// ------------------------------------------------------------------------------------------------
void TaskOdo_Main(void *p_arg)
{
	INT8U err;

	putsUART2("OUFFF TEAM 2011 : Odo online\n");

	init_position_manager(&AppCurrentPos);

	SemOdo = OSSemCreate(0);

	TMR2_Init();

	while(OS_TRUE)
	{
		OSSemPend(SemOdo,100,&err);
		if(err==OS_NO_ERR)
		{
			LED_Toggle(5);
			#ifdef ODO_CALIBRATION
				encoders_calibration_measure();
			#else
				position_manager_process();

				static int i=0; // Refresh sending UART
				char uart_buffer[8];
				char * buffer_ptr;
			
				if(i==0)
				{
					putsUART2("ODO_PROCESS : ");
					putsUART2("x : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) pos->x, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					putsUART2(buffer_ptr);
					putsUART2(",y : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) pos->y, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					putsUART2(buffer_ptr);
					putsUART2(",alpha : ");
					buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) (pos->angle*180.0/M_PI), (CPU_INT08U) 3, (CPU_INT08U) 2, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
					putsUART2(buffer_ptr);
					putsUART2("\n");
				}
				i++;
				if(i==50) i=0;
			#endif
		}

	}
}
