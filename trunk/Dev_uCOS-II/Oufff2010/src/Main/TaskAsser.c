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
struct StructPos setpoint;

// Loop datas
float error_distance;
float scalar_product;
float error_angle;
float error_angle_path2;
float signe_error_angle;
float error_filtered_distance;
float error_filtered_angle;
float raw_command_left;
float raw_command_right;
INT16S command_left;
INT16S command_right;

float error_debug_1;
float error_debug_2;
float error_debug_3;
float index_old_debug;
float error_old_debug;
float error_current_debug;
float D_debug;
float P_debug;
float I_debug;

INT16S duty_left;
INT16S duty_right;


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

	duty_right = abs_value;

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
	
	duty_left = abs_value;

	PWM_M1_SetDC(abs_value);
}

INT16S motor_command_clipping(float command)
{
	if(command > MAX_MOTOR_COMMAND)
	{
		command = MAX_MOTOR_COMMAND;
	}
	else if(command < -MAX_MOTOR_COMMAND )
	{
		command = -MAX_MOTOR_COMMAND;
	}

	return (INT16S) command;
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

	filtered_error = 0.0;
	
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

	//if we are at the begining of the rotating buffer
	//we have to take a value at the end of it
	if(PID_D_PERIOD > pid_data->current_error_old)
	{
		last = PID_SUM_NB_SAMPLES + pid_data->current_error_old - PID_D_PERIOD;
	}
	else
	{
		last = pid_data->current_error_old - PID_D_PERIOD;
	}

	//differential of the error over the period	
	errDif = error - pid_data->error_old[last];
		
	error_debug_3 = errDif;

	//stock last values of the error, so we can
	//differentiate over a custom period
	pid_data->error_old[pid_data->current_error_old]=error;

	pid_data->current_error_old++;
	if(pid_data->current_error_old >= PID_SUM_NB_SAMPLES)
	{
		pid_data->current_error_old = 0; //restart at the beginning of the buffer
	}

	index_old_debug = pid_data->current_error_old;
	error_old_debug = pid_data->error_old[last];
	error_current_debug = error;


	P = error * pid_data->Kp;
	I = pid_data->error_sum * pid_data->Ki;
	D = errDif * pid_data->Kd;
	
	D_debug = D;
	P_debug = P;
	I_debug = I;

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

	memset(&TaskAsser_CurrentPos, 0, sizeof(struct StructPos));

	// init PID
	PID_Initialization();

	SLEWRATE_Initialization();

}

float error_rescale (float error, float scaling_factor, float speed)
{
	float error_rescaled = error;

	if (error >= (float) MAX_MOTOR_COMMAND * scaling_factor * speed)
	{
		error_rescaled = (float) MAX_MOTOR_COMMAND * scaling_factor * speed;
	}
	else
	{
		if(error <= -1.0 * (float) MAX_MOTOR_COMMAND * scaling_factor)
		{
			error_rescaled = -1.0 * (float) MAX_MOTOR_COMMAND * scaling_factor * speed;
		}
	}

	return error_rescaled;
}

// ------------------------------------------------------------------------------------------------
// TaskAsser_Main()
// ------------------------------------------------------------------------------------------------
void TaskAsser_Main(void *p_arg)
{
	INT8U command = 0;
	INT8U Err;
	StructMsg *pCurrentMsg = NULL;
	char uart_buffer[13];
	char * buffer_ptr;
	
	BOOLEAN angle_control = ANGLE_CONTROL_INIT;
	BOOLEAN distance_control = DISTANCE_CONTROL_INIT;
	float speed_ratio = SPEED_RATIO;

	putsUART2("OUFFF TEAM 2010 : Asser online\n");

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

				case Msg_Asser_Algo:	// Define which algo we have to use
					distance_control = (BOOLEAN)pCurrentMsg->Param1;	// Change type of asser to distance algo (if set)
					angle_control = (BOOLEAN)pCurrentMsg->Param2;		// Change type of asser to angle algo (if set)
					break;
						
				case Msg_Asser_SetSpeed:	// Define new speed 
					if(pCurrentMsg->Param1 > 1)
						pCurrentMsg->Param1 = 1.0;	
					speed_ratio = pCurrentMsg->Param1;
					break;

				default :
					break;
			}

			putsUART2("TASK_ASSER : Received Mesg ---> X=");
			buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) pCurrentMsg->Param1, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
			putsUART2(buffer_ptr);
			putsUART2(" , Y=");
			buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) pCurrentMsg->Param2, (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
			putsUART2(buffer_ptr);
			putsUART2(" , Angle=");
			buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) AppConvertRadInDeg(pCurrentMsg->Param3), (CPU_INT08U) 10, (CPU_INT08U) 0, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
			putsUART2(buffer_ptr);
			putsUART2("\n");
		}
			

		// MOTION CONTROL LOOP
		
		// Reset_datas
		error_distance		= 0.0;
		scalar_product		= 0.0;
		error_angle			= 0.0;
		error_angle_path2	= 0.0;
		signe_error_angle	= 0.0;

		

		error_filtered_distance=0.0;
		error_filtered_angle=0.0;

		command_left =0;
		command_right =0;


		// SECTION CRITIQUE : Ask for Mutex on position
		OSMutexPend(Mut_AppCurrentPos, WAIT_FOREVER, &Err);
		{
			// Copy current pos
			memcpy(&TaskAsser_CurrentPos, &AppCurrentPos, sizeof(struct StructPos));
		}

		//END SECTION CRITIQUE : Release Mutex
		OSMutexPost(Mut_AppCurrentPos);

		// Compute error

		// Compute distance : ABS value for vectorial considerations
		error_distance = sqrt(pow(setpoint.x - TaskAsser_CurrentPos.x,2) + pow(setpoint.y - TaskAsser_CurrentPos.y,2));
		// Calcul du produit scalaire
		scalar_product = ( (setpoint.x - TaskAsser_CurrentPos.x)*cos(TaskAsser_CurrentPos.angle) + (setpoint.y - TaskAsser_CurrentPos.y)*sin(TaskAsser_CurrentPos.angle) ); 

		// Compute angle
		if (  (distance_control == 0 && angle_control == 1 ) // Angle mode
			||(distance_control == 1 && angle_control == 1 && error_distance <= DISTANCE_ALPHA_ONLY) ) // Mixed mode : final distance reached
		{
			error_angle = setpoint.angle - TaskAsser_CurrentPos.angle;

			// Condition for PI/-PI movement --> find the shortest movement to perform
			if( TaskAsser_CurrentPos.angle>=0.0) error_angle_path2 = setpoint.angle - (TaskAsser_CurrentPos.angle - 2*M_PI);
			else error_angle_path2 = setpoint.angle - (TaskAsser_CurrentPos.angle + 2*M_PI);

			if(fabs(error_angle_path2)<fabs(error_angle)) error_angle = error_angle_path2;

			error_distance=0;
		}
		
		if ( (distance_control == 1 && angle_control == 1 && error_distance <= DISTANCE_ALPHA_ONLY) ) // Mixed mode : final distance reached
		{
			error_distance = scalar_product;
		}

		if(   (distance_control == 1 && angle_control == 0 && error_distance >= 10) // Distance mode
			||(distance_control == 1 && angle_control == 1 && error_distance > DISTANCE_ALPHA_ONLY) ) // Mixed mode
		{
			// Calcul de la valeur absolue de l'angle à parcourir avec le produit scalaire
			error_angle = acos( scalar_product / error_distance );
			error_debug_1= error_angle;

			// Calcul du sinus de l'angle à parcourir pour avoir le sens de rotation. Avec la produit vectoriel
			signe_error_angle = ( ((setpoint.y - TaskAsser_CurrentPos.y)*cos(TaskAsser_CurrentPos.angle) - (setpoint.x - TaskAsser_CurrentPos.x)*sin(TaskAsser_CurrentPos.angle) ) / error_distance );
			error_debug_2 = signe_error_angle;

			if ( signe_error_angle < 0.0 )
			{
				error_angle = -error_angle;		// Application du signe.
			}
				
			// Détermination si l'on doit reculer plutôt qu'avancer.
			if (error_angle <= -M_PI/2 && error_angle >= - M_PI)	//quart arrière droit
				{
				error_angle = error_angle + M_PI;		// on replace l'angle devant le robot
				error_distance = - error_distance;		// on recule
				}
				
			if (error_angle <= M_PI && error_angle >= M_PI/2)		// quart arrière gauche
				{
				error_angle = error_angle - M_PI;		// on replace l'angle devant le robot
				error_distance = - error_distance;		// on recule
				}
		}

		// Slew rate or quad filter on errors
//		error_angle = SLEWRATE_Compute(& angle_slewrate_data, error_angle);
//		error_distance = SLEWRATE_Compute(& distance_slewrate_data, error_distance);

		// PID filter on errors
		if(angle_control) error_filtered_angle = PID_Computation(&angle_pid_data, error_angle);
		if(distance_control) error_filtered_distance = PID_Computation(&distance_pid_data, error_distance);

		// Re-scale errors to fit on expected scale
		error_filtered_distance = error_rescale (error_filtered_distance, (1.0 - ANGLE_VS_DISTANCE_RATIO), speed_ratio);
		error_filtered_angle = error_rescale (error_filtered_angle, ANGLE_VS_DISTANCE_RATIO, speed_ratio);

		// Command merge
		raw_command_right = error_filtered_distance + error_filtered_angle;
		raw_command_left = error_filtered_distance - error_filtered_angle;
		
		// command clipping
		command_right = motor_command_clipping(raw_command_right);
		command_left = motor_command_clipping(raw_command_left);

		// Motor drive
		right_motor_control (command_right);
		left_motor_control (command_left);

	}
}
