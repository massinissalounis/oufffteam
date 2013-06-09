/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskDetection.c
*
* Suivi de version :
* 2014-06-05 | PBE | Creation de la version de base pour la coupe 2014
*********************************************************************************************************
*/

#include "TaskDetection.h"
#include "AppGlobalVars.h"
#include "LibPID.h"

/////////////////////////////////////////////////////////////
// DATAS
/////////////////////////////////////////////////////////////

// PID datas
PID_data beacon_motor_pid_data;

/////////////////////////////////////////////////////////////
// MOTOR_CONTROL
/////////////////////////////////////////////////////////////

void Beacon_Motor_Sampling()
{
	// LATCH QUAD RESISTERS
	BEACON_MOTOR_Latch();
}

// Pivot control motion in separated wheel control
float Beacon_Motor_Speed_Control(CPU_INT16S speed_setpoint, CPU_INT16S current_motor_position)
{
	static CPU_INT16S old_motor_position=0;
	
	CPU_INT16S current_motor_speed=0;
	CPU_INT16S error_speed_beacon_motor=0;

	float speed_error_filtered=0.0;
	
	unsigned char end_movement_flag=0;
	

	current_motor_speed = current_motor_position - old_motor_position;
	error_speed_beacon_motor = speed_setpoint - current_motor_speed;
	
	speed_error_filtered = PID_Computation(&beacon_motor_pid_data, (float) error_speed_beacon_motor);
	
	old_motor_position = current_motor_position;
	
	return speed_error_filtered
}

// ------------------------------------------------------------------------------------------------
// TaskDetection_Main()
// ------------------------------------------------------------------------------------------------
void TaskDetection_Main(void *p_arg)
{
//	INT8U InternalScheduler = 0;
	OSTimeDlyHMSM(0, 0, 1, 0);
	AppDebugMsg("OUFFF TEAM 2014 : Detection online\n");
	
	CPU_INT16S motor_position=0;
	CPU_INT08U beacon_status=0;
	
	CPU_INT16S impact_positions[8];
	
	PID_Initialization(&beacon_motor_pid_data, KP_BEACON_MOTOR_SPEED, KI_BEACON_MOTOR_SPEED, KD_BEACON_MOTOR_SPEED, IMAX_BEACON_MOTOR_SPEED);
	
	// Main Loop
	while(OS_TRUE)
	{
		// Increment the scheduler
//		InternalScheduler++;
//		if(InternalScheduler>5) InternalScheduler=0;
		
//		if(InternalScheduler==5)
//		{
			
//		}
		
		// Period 1: Motor control
		motor_position=BEACON_MOTOR_Read();
		motor_command = Beacon_Motor_Speed_Control(BEACON_MOTOR_SPEED_SETPOINT_IN_INC,  motor_position);
		BEACON_MOTOR_Write_PWM(motor_command);
		
		// Period 2: Read the beacon status
		
		beacon_status=BEACON_STATUS_Read();
		
		if(beacon_status==0xFF)
			AppDebugMsg("BEACON: Error message status received\n");
		else
		{

			
			CPU_INT16U BEACON_POSITION_REG (INT8U indix);
		}
		


		

		// Proc Release
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
}
