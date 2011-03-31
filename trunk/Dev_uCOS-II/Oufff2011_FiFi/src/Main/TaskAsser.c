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
PID_data wheel_right_pid_data;
PID_data wheel_left_pid_data;

SLEWRATE_data angle_slewrate_data;
SLEWRATE_data distance_slewrate_data;

QUADRAMP_data distance_quadramp_data;

// General robot control datas
struct StructPos setpoint;

// Loop datas
float error_debug_1;
float error_debug_2;
float error_debug_3;
float index_old_debug;
float error_old_debug;
float error_current_debug;
float D_debug;
float P_debug;
float I_debug;

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
void QUADRAMP_Initialization(QUADRAMP_data *data, float acc, float speed, float approach)
{
	data->acceleration_order=acc;
	data->speed_order=speed;
	
	data->final_approach_limit=approach;

	data->speed=0.0;
	data->old_filtered_error=0.0;
}

float QUADRAMP_Compute(QUADRAMP_data *data, float error)
{
	float filtered_error=0.0;
	
	float break_distance=0.0;
	float Tech= ASSER_SAMPLING*0.001; // ms conversion
	
	int tmp1;
	float tmp2;
	
	int state=0; // 0: stop, 1: acc, 2: Vcte, 3: Decell, 4: final

	// Phase detection
	tmp1=abs(data->speed/data->acceleration_order); // break_time in loop times
	tmp2=data->speed;
	while(tmp1!=0)
	{
		break_distance+=data->speed*Tech;
		tmp2-=data->acceleration_order;
		tmp1--;
	}

	if(abs(error)>break_distance) // acc or Vcte
	{
		if(data->speed<data->speed_order) state = 1;
		else state = 2;
	}
	else // Decell or Final
	{
		if(abs(error)<=data->final_approach_limit) state = 4;
		else state = 3;
	}
	
	switch(state)
	{
		case 0:
			break;
			
		case 1:
			data->speed+=(data->acceleration_order*Tech);
			if(data->speed>data->speed_order) data->speed = data->speed_order;
			filtered_error=data->old_filtered_error+(data->speed*Tech);
			break;
			
		case 2:
			filtered_error=data->old_filtered_error+(data->speed*Tech);
			break;
			
		case 3:
			data->speed-=(data->acceleration_order*Tech);
			if(data->speed<=0.0) data->speed = 0.0;
			filtered_error=data->old_filtered_error+(data->speed*Tech);
			break;
			
		default:
			break;	
	}
	
	data->old_filtered_error=filtered_error;
	
	if(error<0.0) filtered_error=-filtered_error;
	
	return filtered_error;
}

/// SLEWRATEs to delete ? unused in the source code.
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
	
	wheel_left_pid_data.Kp = KP_WHEEL;
	wheel_left_pid_data.Ki = KI_WHEEL;
	wheel_left_pid_data.Kd = KD_WHEEL;	
	wheel_left_pid_data.IMax = IMAX_WHEEL;
	
	wheel_right_pid_data.Kp = KP_WHEEL;
	wheel_right_pid_data.Ki = KI_WHEEL;
	wheel_left_pid_data.Kd = KD_WHEEL;	
	wheel_left_pid_data.IMax = IMAX_WHEEL;	

	for(i=0; i<PID_SUM_NB_SAMPLES; i++)
	{
		angle_pid_data.error_old[i]=0.0;
		distance_pid_data.error_old[i]=0.0;
		wheel_right_pid_data.error_old[i]=0.0;
		wheel_left_pid_data.error_old[i]=0.0;
	}

	angle_pid_data.current_error_old = 0;
	distance_pid_data.current_error_old = 0;
	wheel_right_pid_data.current_error_old = 0;
	wheel_left_pid_data.current_error_old = 0;
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
	setpoint.right_encoder=0;
	setpoint.left_encoder=0;

	memset(&TaskAsser_CurrentPos, 0, sizeof(struct StructPos));

	// init PID
	PID_Initialization();

	SLEWRATE_Initialization();
	
	QUADRAMP_Initialization(&distance_quadramp_data, DEFAULT_ACCELERATION, DEFAULT_SPEED, DISTANCE_ALPHA_ONLY);

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

float angle_between_two_points(float setpoint_angle, float current_angle)
{
	float error_angle=0.0;
	float error_angle_path2 =0.0;
	
	error_angle = setpoint_angle - current_angle;
	
	// Condition for PI/-PI movement --> find the shortest movement to perform
	if( current_angle>=0.0) error_angle_path2 = setpoint_angle - (current_angle - 2*M_PI);
	else error_angle_path2 = setpoint_angle - (current_angle + 2*M_PI);
				
	if(fabs(error_angle_path2)<fabs(error_angle)) error_angle = error_angle_path2;

	return error_angle;
}

float distance_between_two_points( float x1, float y1, float x2, float y2)
{
	float distance=0.0;
	
	distance= sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
	
	return distance;
}

float scalar_product_between_robot_and_direction (float final_x, float final_y, float robot_x, float robot_y, float robot_angle) 
{
	float scalar_product=0.0;
	
	scalar_product= (final_x - robot_x)*cos(robot_angle) + (final_y - robot_y)*sin(robot_angle); 

	return scalar_product;
}

float vector_product_between_robot_and_direction (float final_x, float final_y, float robot_x, float robot_y, float robot_angle) 
{
	float vector_product=0.0;
	
	vector_product= (final_y - robot_y)*cos(robot_angle) + (final_x - robot_x)*sin(robot_angle); 

	return vector_product;
}

void distance_by_vector_projection_angle_between_robot_and_direction (float final_x, float final_y, float robot_x, float robot_y, float robot_angle, float *distance, float *angle)
{
	float scalar_product=0.0;
	float angle_sign =0.0;
	
	scalar_product = scalar_product_between_robot_and_direction(setpoint.x, setpoint.y, TaskAsser_CurrentPos.x, TaskAsser_CurrentPos.y, TaskAsser_CurrentPos.angle);
	*distance = distance_between_two_points( setpoint.x, setpoint.y, TaskAsser_CurrentPos.x, TaskAsser_CurrentPos.y);
	
	// Calcul de la valeur absolue de l'angle à parcourir avec le produit scalaire
	*angle = acos( scalar_product / *distance );

	// Calcul du sinus de l'angle à parcourir pour avoir le sens de rotation. Avec la produit vectoriel
	angle_sign = vector_product_between_robot_and_direction(setpoint.x, setpoint.y, TaskAsser_CurrentPos.x, TaskAsser_CurrentPos.y, TaskAsser_CurrentPos.angle); // ATTENTION : on avait divisé par error_distance .. normalement ca ne sert à rien mais au cas ou ... / error_distance );

	if ( angle_sign < 0.0 )
	{
		*angle = - *angle;		// Application du signe.
	}
						
	// Détermination si l'on doit reculer plutôt qu'avancer.
	if (*angle <= -M_PI/2 && *angle >= - M_PI)	//quart arrière droit
	{
		*angle = *angle + M_PI;		// on replace l'angle devant le robot
		*distance = - *distance;		// on recule
	}
						
	if (*angle <= M_PI && *angle >= M_PI/2)		// quart arrière gauche
	{
		*angle = *angle - M_PI;		// on replace l'angle devant le robot
		*distance = - *distance;		// on recule
	}
}

// Angle only in theta-alpha control
/// Improvements : speed ratio control
void mode_1_control_motion(struct StructPos *psetpoint, struct StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	float error_angle=0.0;
	float error_distance=0.0;
	float error_filtered_angle=0.0;
	
	float speed_ratio = SPEED_RATIO;
	
	// Compute error
	error_angle=angle_between_two_points(psetpoint->angle, pcurrent->angle);
	
	error_filtered_angle = PID_Computation(&angle_pid_data, error_angle);
	
	// Re-scale errors to fit on expected scale
	error_filtered_angle = error_rescale (error_filtered_angle, ANGLE_VS_DISTANCE_RATIO, speed_ratio);

	// Command merge
	*raw_command_right = error_filtered_angle;
	*raw_command_left = - error_filtered_angle;
}

// Distance only in theta-alpha control
/// Improvements : parameter for the final approach distance
/// Improvements : What is happening when error <10 ??? to check
/// Improvements : Speed control ?
/// Improvements : speed ratio management
void mode_2_control_motion(struct StructPos *psetpoint, struct StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	float error_angle=0.0;
	float error_distance=0.0;
	float error_filtered_distance=0.0;
	
	float speed_ratio = SPEED_RATIO;
	
	// Compute error
	// Compute distance : ABS value for vectorial considerations
	error_distance = distance_between_two_points( psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y);
	if(error_distance>=10) // Final approach
	{
		distance_by_vector_projection_angle_between_robot_and_direction(psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y, pcurrent->angle, &error_distance, &error_angle);
	}
	
	// PID filtering
	error_filtered_distance = PID_Computation(&distance_pid_data, error_distance);

	// Re-scale errors to fit on expected scale
	error_filtered_distance = error_rescale (error_filtered_distance, (1.0 - ANGLE_VS_DISTANCE_RATIO), speed_ratio);

	// Command merge
	*raw_command_right = error_filtered_distance;
	*raw_command_left = error_filtered_distance;
}

// Distance + Angle in theta-alpha control
/// Improvements : parameter for the final approach distance
void mode_3_control_motion(struct StructPos *psetpoint, struct StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	float error_angle=0.0;
	float error_distance=0.0;
	float error_filtered_angle=0.0;
	float error_filtered_distance=0.0;
	
	float speed_ratio = SPEED_RATIO;
	
	// Compute error
	
	// Compute distance : ABS value for vectorial considerations
	error_distance = distance_between_two_points( psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y);
				
	if(error_distance<= DISTANCE_ALPHA_ONLY) // final distance reached
	{
		error_angle=angle_between_two_points(psetpoint->angle, pcurrent->angle);				
		error_distance = scalar_product_between_robot_and_direction(psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y, pcurrent->angle);
	}
	else
	{
		distance_by_vector_projection_angle_between_robot_and_direction(psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y, pcurrent->angle, &error_distance, &error_angle);
	}
	
	// QUADRAMP filter on errors
	error_distance = QUADRAMP_Compute(&distance_quadramp_data, error_distance);
	
	// PID filter on errors
	error_filtered_angle = PID_Computation(&angle_pid_data, error_angle);
	error_filtered_distance = PID_Computation(&distance_pid_data, error_distance);

	// Re-scale errors to fit on expected scale
	error_filtered_distance = error_rescale (error_filtered_distance, (1.0 - ANGLE_VS_DISTANCE_RATIO), speed_ratio);
	error_filtered_angle = error_rescale (error_filtered_angle, ANGLE_VS_DISTANCE_RATIO, speed_ratio);

	// Command merge
	*raw_command_right = error_filtered_distance + error_filtered_angle;
	*raw_command_left = error_filtered_distance - error_filtered_angle;
}

// Pivot control motion in separated wheel control
void mode_4_control_motion(struct StructPos *psetpoint, struct StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	// setpoint.pivot_wheel // 0: left 1: right
	// setpoint.pivot_angle
	// CONVERSION_RAD_TO_MM
	
	// Fonction de conversion à faire par Fifi
	// Donner dans le set point des positions de roues !
	// Calculer la distance à parcourir par chacune des roues et la donner ... en inc ? en mm ? en rad avec un pivot ... à discuter avec Fifi.

	int error_right_wheel=0;
	int error_left_wheel=0;

	int error_filtered_right_wheel=0;
	int error_filtered_left_wheel=0;
	
	error_right_wheel = psetpoint->right_encoder - pcurrent->right_encoder;
	error_left_wheel = psetpoint->left_encoder - pcurrent->left_encoder;
	
	error_filtered_right_wheel = PID_Computation(&wheel_right_pid_data, error_right_wheel);
	error_filtered_left_wheel = PID_Computation(&wheel_left_pid_data, error_right_wheel);	

	*raw_command_right = error_filtered_right_wheel;
	*raw_command_left = error_filtered_left_wheel;
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
	
	// Asser Datas
	float raw_command_left;
	float raw_command_right;
	INT16S command_left;
	INT16S command_right;
	
	int mode_control=0;

//	float speed_ratio = SPEED_RATIO;

	putsUART2("OUFFF TEAM 2011 : Asser online\n");

	init_control_motion();

	while(OS_TRUE)
	{
		OSTimeDlyHMSM(0,0,0,ASSER_SAMPLING);
	
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
					if(!(BOOLEAN)pCurrentMsg->Param1 && !(BOOLEAN)pCurrentMsg->Param2) mode_control =0; // No control
					if(!(BOOLEAN)pCurrentMsg->Param1 && (BOOLEAN)pCurrentMsg->Param2) mode_control =1; // Angle only
					if((BOOLEAN)pCurrentMsg->Param1 && !(BOOLEAN)pCurrentMsg->Param2) mode_control =2; // Distance only
					if((BOOLEAN)pCurrentMsg->Param1 && (BOOLEAN)pCurrentMsg->Param2) mode_control =3; // Mixed mode
					break;
						
				case Msg_Asser_SetSpeed:	// Define new speed 
					if(pCurrentMsg->Param1 > 1)
						pCurrentMsg->Param1 = 1.0;	
					//speed_ratio = pCurrentMsg->Param1;
					//distance_quadramp_data.speed_order = xx;
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

		// Asser mode control
		switch(mode_control)
		{
			case 1: // Angle only
				mode_1_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				break;
				
			case 2: //Distance only
				mode_2_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				
				break;
			case 3:
				mode_3_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				break;
			case 4: // pivot
				mode_4_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				break;
			default:
				break;
		}
		
		// command clipping
		command_right = motor_command_clipping(raw_command_right);
		command_left = motor_command_clipping(raw_command_left);

		// Motor drive
		right_motor_control (command_right);
		left_motor_control (command_left);
	}
}
