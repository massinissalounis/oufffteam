/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskAsser.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
*********************************************************************************************************


*/

#include "TaskAsser.h"

/////////////////////////////////////////////////////////////
// DATAS
/////////////////////////////////////////////////////////////

// PID datas
PID_data angle_pid_data;
PID_data distance_pid_data;

SLEWRATE_data angle_slewrate_data;
SLEWRATE_data distance_slewrate_data;

// General robot control datas
StructPos setpoint;

// Loop datas
float error_distance;
float error_angle;
float error_filtered_distance;
float error_filtered_angle;
INT16S command_left;
INT16S command_right;

float error_debug_1;
float error_debug_2;
float error_debug_3;

/////////////////////////////////////////////////////////////
// MOTOR CONTROL
/////////////////////////////////////////////////////////////
void right_motor_control (INT16S value)
{
	INT16U abs_value;

	// Select motor direction
	if(value<0)
	{
		IO_M0_SetDirection(1); // MOTOR REAR DIRECTION
		abs_value = - value;
	}
	else
	{
		IO_M0_SetDirection(0); // MOTOR FRONT DIRECTION
		abs_value = value;
	}

	abs_value = abs_value <<1; // full scale data

	PWM_M0_SetDC(abs_value);
}

void left_motor_control (INT16S value)
{
	INT16U abs_value;

	// Select motor direction
	if(value<0)
	{
		IO_M1_SetDirection(1); // MOTOR REAR DIRECTION
		abs_value = - value;
	}
	else
	{ 
		IO_M1_SetDirection(0); // MOTOR FRONT DIRECTION
		abs_value = value;
	}

	abs_value = abs_value <<1; // full scale data

	PWM_M1_SetDC(abs_value);
}

INT16S motor_command_clipping(INT16S command)
{
	if(command > MAX_MOTOR_COMMAND)
	{
		command = MAX_MOTOR_COMMAND;
	}
	else if(command < -MAX_MOTOR_COMMAND)
	{
		command = -MAX_MOTOR_COMMAND;
	}

	return command;
}

/////////////////////////////////////////////////////////////
// FILTERS
/////////////////////////////////////////////////////////////
void QUADRAMP_Compute(void)
{

}

void SLEWRATE_Initialization(void)
{
	angle_slewrate_data.max_acceleration=ACC_ANGLE;
	angle_slewrate_data.max_speed=VMAX_ANGLE;

	angle_slewrate_data.previous_speed=0.0;
	angle_slewrate_data.previous_position=0.0;

	
	distance_slewrate_data.max_acceleration=ACC_DISTANCE;
	distance_slewrate_data.max_speed=VMAX_DISTANCE;

	distance_slewrate_data.previous_speed=0.0;
	distance_slewrate_data.previous_position=0.0;
}

float SLEWRATE_Compute(SLEWRATE_data *data, float final_setpoint)
{
	float max_acceleration;
	float max_speed;

	float speed, position;

	if(final_setpoint<0.0) // Convert speed and acceleration for reverse motion
	{
		max_acceleration = - data->max_acceleration;
		max_speed = - data->max_speed; 
	}
	else
	{
		max_acceleration = data->max_acceleration;
		max_speed = data->max_speed; 
	}

	// Compute speed
	if( abs(speed) < abs(data->max_speed) )
	{
		speed = data->previous_speed + max_acceleration;
	}
	else
	{
		speed = max_speed;
	}

	position = data->previous_position + speed;

	if(position >= final_setpoint)
	{
		position = final_setpoint;
		speed = 0.0; // No further need of speed
	}

	data->previous_speed = speed; // Store current value
	data->previous_position = position;

	return position;
}

void PID_Initialization(void)
{
	int i;

	angle_pid_data.Kp = KP_ANGLE;
	angle_pid_data.Ki = KI_ANGLE;
	angle_pid_data.Kd = KD_ANGLE;
	angle_pid_data.IMax = IMAX_ANGLE;

	distance_pid_data.Kp = KP_DISTANCE;
	distance_pid_data.Ki = KI_DISTANCE;
	distance_pid_data.Kd = KD_DISTANCE;	
	distance_pid_data.IMax = IMAX_DISTANCE;	

	for(i=0; i<PID_SUM_NB_SAMPLES; i++)
	{
		angle_pid_data.error_old[i]=0.0;
		distance_pid_data.error_old[i]=0.0;
	}

	angle_pid_data.current_error_old = 0;
	distance_pid_data.current_error_old = 0;
}

float PID_Computation(PID_data * pid_data, float error)
{
	float P,I,D;
	float filtered_error;
	float errDif;
	int last;
	
	//Compute Sum
	//sum of all errors of the MAX_D_PERIOD previous period
	pid_data->error_sum -= pid_data->error_old[pid_data->current_error_old]; // Substract oldest value
	pid_data->error_sum += error; // Add newest value

	//bound integration values
	if(pid_data->error_sum > pid_data->IMax)
	{
		pid_data->error_sum = pid_data->IMax;
	}
	else if(pid_data->error_sum < -pid_data->IMax)
	{
		pid_data->error_sum = -pid_data->IMax;
	}

	//stock last values of the error, so we can
	//differentiate over a custom period
	pid_data->error_old[pid_data->current_error_old]=error;

	pid_data->current_error_old++;
	if(pid_data->current_error_old >= PID_SUM_NB_SAMPLES)
	{
		pid_data->current_error_old = 0; //restart at the beginning of the buffer
	}

	//if we are at the begining of the rotating buffer
	//we have to take a value at the end of it
	if(PID_D_PERIOD > pid_data->current_error_old)
	{
		last = PID_D_PERIOD + pid_data->current_error_old - PID_D_PERIOD;
	}
	else
	{
		last = pid_data->current_error_old - PID_D_PERIOD;
	}

	//differential of the error over the period
	errDif = error - pid_data->error_old[last];

	P = error * pid_data->Kp;
	I = pid_data->error_sum * pid_data->Ki;
	D = errDif * pid_data->Kd;

	filtered_error = P + I + D;

	return filtered_error;
}

/////////////////////////////////////////////////////////////
// MOTION CONTROL
/////////////////////////////////////////////////////////////

void init_control_motion()
{
	// init structures
	setpoint.x=0.0;
	setpoint.y=0.0;
	setpoint.angle=0.0;

	// init PID
	PID_Initialization();

	SLEWRATE_Initialization();

}

// ------------------------------------------------------------------------------------------------
// TaskAsser_Main()
// ------------------------------------------------------------------------------------------------
void TaskAsser_Main(void *p_arg)
{
	INT8U command = 0;
	INT8U Err;
	StructMsg *pCurrentMsg = NULL;

	BOOLEAN angle_control = ANGLE_CONTROL_INIT;
	BOOLEAN distance_control = DISTANCE_CONTROL_INIT;

	init_control_motion();

	while(OS_TRUE)
	{
		OSTimeDlyHMSM(0,0,0,10);
	
//		LED_Toggle(5);
		
		// Look for asser msg
		pCurrentMsg = (StructMsg*)OSQAccept(AppQueueAsserEvent, &Err);
		
		if(NULL != pCurrentMsg)
		{
			// Indicate current msg has been read
			pCurrentMsg->IsRead = OS_TRUE;

			// SYSTEM CONTROL
			switch(pCurrentMsg->Msg)
			{
				case Msg_Asser_GoToXYA:	// Define new setpoint
					setpoint.x = pCurrentMsg->Param1; 
					setpoint.y = pCurrentMsg->Param2;
					setpoint.angle = pCurrentMsg->Param3;  		
					break;

				case Msg_Asser_Algo:	
					distance_control = (BOOLEAN)pCurrentMsg->Param1;	// Change type of asser to distance algo (if set)
					angle_control = (BOOLEAN)pCurrentMsg->Param2;		// Change type of asser to angle algo (if set)
					break;
				
				default :
					break;
			}
		}
			

		// MOTION CONTROL LOOP
		
		// Reset_datas
		error_distance=0.0;
		error_angle =0.0;

		error_filtered_distance=0.0;
		error_filtered_angle=0.0;

		command_left =0;
		command_right =0;

		// Compute error
		// angle
		// SECTION CRITIQUE : Ask for Mutex on position
		OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);
		{

			// Compute distance : ABS value for vectorial considerations
			error_distance = sqrt(pow(setpoint.x - AppCurrentPos.x,2) + pow(setpoint.y - AppCurrentPos.y,2));

			// Compute angle
			if( error_distance<5 || !distance_control) // Final distance reach --> just correct angle
			{
			error_angle = setpoint.angle - AppCurrentPos.angle;
			}
			else
			{
				error_angle = acos( ( (setpoint.x - AppCurrentPos.x)*cos(AppCurrentPos.angle) + (setpoint.y - AppCurrentPos.y)*sin(AppCurrentPos.angle) ) / error_distance  ) ;
				error_debug_1= error_angle;
			
				error_debug_2 = ( ((setpoint.x - AppCurrentPos.x)*sin(AppCurrentPos.angle) + (setpoint.y - AppCurrentPos.y)*cos(AppCurrentPos.angle)) / error_distance ) ;
			
				if ( error_debug_2 > 0.0 )
				{
					error_angle = -error_angle;
				}

				if ( !(error_angle >= - M_PI/2 && error_angle <= M_PI/2 ) )
				{
					error_distance = - error_distance;
					error_angle = error_angle - M_PI;
				}
			}

			error_debug_3 = error_angle;

			// Compute distance
			//error_distance = sqrt(pow(setpoint.x - AppCurrentPos.x,2) + pow(setpoint.y - AppCurrentPos.y,2));

		}
		//END SECTION CRITIQUE : Release Mutex
		OSMutexPost(Mut_AppCurrentPos);

		// Slew rate or quad filter on errors
//		error_angle = SLEWRATE_Compute(& angle_slewrate_data, error_angle);
//		error_distance = SLEWRATE_Compute(& distance_slewrate_data, error_distance);

		// PID filter on errors
		if(angle_control) error_filtered_angle = PID_Computation(&angle_pid_data, error_angle);
		if(distance_control) error_filtered_distance = PID_Computation(&distance_pid_data, error_distance);

		// Command merge
		command_right = error_filtered_distance + error_filtered_angle;
		command_left = error_filtered_distance - error_filtered_angle;
		
		// command clipping
		command_right = motor_command_clipping(command_right);
		command_left = motor_command_clipping(command_left);

		// Motor drive
		right_motor_control (command_right);
		left_motor_control (command_left);

	}
}
