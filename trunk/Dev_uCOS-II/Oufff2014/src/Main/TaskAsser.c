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
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************


*/

#include "TaskAsser.h"
#include "TaskOdo.h"
#include "LibPID.h"

INT8U	Debug_AsserRampState = 0;

//////////////////////////////////////////////
// Global Vars Coefficients
//////////////////////////////////////////////

// General robot control datas
StructPos setpoint;
StructPos TaskAsser_CurrentPos;							// Local var to read current pos

/////////////////////////////////////////////////////////////
// DATAS
/////////////////////////////////////////////////////////////

// PID datas
PID_data angle_pid_data;
PID_data distance_pid_data;
PID_data wheel_right_pid_data;
PID_data wheel_left_pid_data;

QUADRAMP_data distance_quadramp_data;

// Loop datas
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
		IO_M0_SetDirection(0); // MOTOR REAR DIRECTION
		abs_value = - value;
	}
	else
	{
		IO_M0_SetDirection(1); // MOTOR FRONT DIRECTION
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
		IO_M1_SetDirection(0); // MOTOR REAR DIRECTION
		abs_value = - value;
	}
	else
	{ 
		IO_M1_SetDirection(1); // MOTOR FRONT DIRECTION
		abs_value = value;
	}

	abs_value = abs_value <<1; // full scale data

	PWM_M1_SetDC(abs_value);
}

INT16S motor_command_clipping(float command)
{
	if(command >= MAX_MOTOR_COMMAND)
	{
		command = MAX_MOTOR_COMMAND;
	}
	else if(command <= -MAX_MOTOR_COMMAND )
	{
		command = -MAX_MOTOR_COMMAND;
	}

	return (INT16S) command;
}

/////////////////////////////////////////////////////////////
// MOTION CONTROL
/////////////////////////////////////////////////////////////

void PIDs_Initialization()
{
	int i;
	PID_Initialization(&angle_pid_data, KP_ANGLE, KI_ANGLE, KD_ANGLE, IMAX_ANGLE);
	PID_Initialization(&distance_pid_data, KP_DISTANCE, KI_DISTANCE, KD_DISTANCE, IMAX_DISTANCE);
	PID_Initialization(&wheel_left_pid_data, KP_WHEEL_L, KI_WHEEL_L, KD_WHEEL_L, IMAX_WHEEL_L);
	PID_Initialization(&wheel_right_pid_data, KP_WHEEL_R, KI_WHEEL_R, KD_WHEEL_R, IMAX_WHEEL_R);
}

void init_control_motion()
{
	// init structures
	setpoint.x=0.0;
	setpoint.y=0.0;
	setpoint.angle=0.0;
	setpoint.right_encoder=0;
	setpoint.left_encoder=0;

	memset(&TaskAsser_CurrentPos, 0, sizeof(StructPos));

	// init PID
	PIDs_Initialization();
	
	QUADRAMP_Initialization(&distance_quadramp_data, DEFAULT_ACC_DISTANCE, DEFAULT_SPEED_DISTANCE, DISTANCE_ALPHA_ONLY);
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
		if(error <= -1.0 * (float) MAX_MOTOR_COMMAND * scaling_factor * speed)
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
	
	vector_product= (final_y - robot_y)*cos(robot_angle) - (final_x - robot_x)*sin(robot_angle); 

	return vector_product;
}

void distance_by_vector_projection_angle_between_robot_and_direction (float final_x, float final_y, float robot_x, float robot_y, float robot_angle, float *distance, float *angle)
{
	float scalar_product=0.0;
	float angle_sign =0.0;
	
	scalar_product = scalar_product_between_robot_and_direction(final_x, final_y, robot_x, robot_y, robot_angle);
	*distance = distance_between_two_points( final_x, final_y, robot_x, robot_y);

	// Calcul de la valeur absolue de l'angle à parcourir avec le produit scalaire
	*angle = acos( scalar_product / *distance );

	// Calcul du sinus de l'angle à parcourir pour avoir le sens de rotation. Avec la produit vectoriel
	angle_sign = vector_product_between_robot_and_direction(final_x, final_y, robot_x, robot_y, robot_angle); // ATTENTION : on avait divisé par error_distance .. normalement ca ne sert à rien mais au cas ou ... / error_distance );

	// Détermination si l'on doit reculer plutôt qu'avancer.
	if (*angle >= M_PI/2)		// quart arrière gauche
	{
		*angle = *angle - M_PI;					// on replace l'angle devant le robot
		*distance = (*distance) * (-1);		// on recule
	}

	if ( angle_sign < 0.0 )
	{
		*angle = (*angle) * (-1);		// Application du signe.
	}
}

// Angle only in theta-alpha control
unsigned char mode_1_control_motion(StructPos *psetpoint, StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	float error_angle=0.0;
	float error_distance=0.0;
	float error_filtered_angle=0.0;

	unsigned char end_movement_flag=0;
	
	// Compute error
	error_angle=angle_between_two_points(psetpoint->angle, pcurrent->angle);

	if(error_angle<=ANGLE_APPROACH_PRECISION) end_movement_flag=1;
	
	error_filtered_angle = PID_Computation(&angle_pid_data, error_angle);
	
	// Re-scale errors to fit on expected scale
	error_filtered_angle = error_rescale (error_filtered_angle, ANGLE_VS_DISTANCE_RATIO, SPEED_ANGLE);

	// Command merge
	*raw_command_right = error_filtered_angle;
	*raw_command_left = - error_filtered_angle;

	return end_movement_flag;
}

// Distance only in theta-alpha control
unsigned char mode_2_control_motion(StructPos *psetpoint, StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	float error_angle=0.0;
	float error_distance=0.0;
	float error_filtered_distance=0.0;

	unsigned char end_movement_flag=0;
	
	float speed_ratio_distance = DEFAULT_SPEED_DISTANCE; // To check !!!
	
	// Compute error
	error_distance = scalar_product_between_robot_and_direction(psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y, pcurrent->angle);

	if(abs(error_distance)<= DISTANCE_ALPHA_ONLY) // final distance reached
	{
		end_movement_flag=1;
	}

	// QUADRAMP filter on errors
	speed_ratio_distance = QUADRAMP_Compute(&distance_quadramp_data, error_distance);
	
	// PID filtering
	error_filtered_distance = PID_Computation(&distance_pid_data, error_distance);

	// Re-scale errors to fit on expected scale
	error_filtered_distance = error_rescale (error_filtered_distance, (1.0 - ANGLE_VS_DISTANCE_RATIO), speed_ratio_distance);

	// Command merge
	*raw_command_right = error_filtered_distance;
	*raw_command_left = error_filtered_distance;

	return end_movement_flag;
}

// Distance + Angle in theta-alpha control
/// Improvements : parameter for the final approach distance
unsigned char mode_3_control_motion(StructPos *psetpoint, StructPos *pcurrent, float *raw_command_right, float *raw_command_left)
{
	float error_angle=0.0;
	float error_distance=0.0;
	float error_filtered_angle=0.0;
	float error_filtered_distance=0.0;
	
	float speed_ratio_distance = DEFAULT_SPEED_DISTANCE;

	unsigned char end_movement_flag=0;
	
	// Compute error
	
	// Compute distance : ABS value for vectorial considerations
	error_distance = distance_between_two_points( psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y);

	if(error_distance<= DISTANCE_ALPHA_ONLY) // final distance reached
	{
		error_angle=angle_between_two_points(psetpoint->angle, pcurrent->angle);
		if(error_angle<=ANGLE_APPROACH_PRECISION) end_movement_flag=1;
		error_distance = scalar_product_between_robot_and_direction(psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y, pcurrent->angle);
	}
	else
	{
		distance_by_vector_projection_angle_between_robot_and_direction(psetpoint->x, psetpoint->y, pcurrent->x, pcurrent->y, pcurrent->angle, &error_distance, &error_angle);
	}

	// QUADRAMP filter on errors
	speed_ratio_distance = QUADRAMP_Compute(&distance_quadramp_data, error_distance);
	
	// PID filter on errors
	error_filtered_angle = PID_Computation(&angle_pid_data, error_angle);
	error_filtered_distance = PID_Computation(&distance_pid_data, error_distance);

	// Re-scale errors to fit on expected scale
	error_filtered_distance = error_rescale (error_filtered_distance, (1.0 - ANGLE_VS_DISTANCE_RATIO), speed_ratio_distance);
	error_filtered_angle = error_rescale (error_filtered_angle, ANGLE_VS_DISTANCE_RATIO, SPEED_ANGLE);

	// Command merge
	*raw_command_right = error_filtered_distance + error_filtered_angle;
	*raw_command_left = error_filtered_distance - error_filtered_angle;

	return end_movement_flag;
}

// Pivot control motion in separated wheel control
unsigned char mode_4_control_motion(StructPos *psetpoint, StructPos *pcurrent, float speed, float *raw_command_right, float *raw_command_left)
{
	// setpoint.pivot_wheel // 0: left 1: right
	// setpoint.pivot_angle

	CPU_INT16S error_right_wheel=0;
	CPU_INT16S error_left_wheel=0;

	float error_filtered_right_wheel=0.0;
	float error_filtered_left_wheel=0.0;
	
	unsigned char end_movement_flag=0;
	

	error_right_wheel = psetpoint->right_encoder - pcurrent->right_encoder;
	error_left_wheel = -(psetpoint->left_encoder - pcurrent->left_encoder);

	if(abs(error_right_wheel)<=PIVOT_RIGHT_APPROACH_PRECISION && abs(error_left_wheel)<=PIVOT_LEFT_APPROACH_PRECISION)
	{
		end_movement_flag=1;
	}

	error_filtered_right_wheel = PID_Computation(&wheel_right_pid_data, (float) error_right_wheel);
	error_filtered_left_wheel = PID_Computation(&wheel_left_pid_data, (float) error_left_wheel);

	error_filtered_right_wheel = error_rescale (error_filtered_right_wheel, 1.0, speed);
	error_filtered_left_wheel = error_rescale (error_filtered_left_wheel, 1.0, speed);	

	*raw_command_right = error_filtered_right_wheel;
	*raw_command_left = error_filtered_left_wheel;

	return end_movement_flag;
}

void pivot_setpoint_computation(StructPos *current, char pivot_wheel, StructPos *setpoint)
{
	float pivot_setpoint=0;

	pivot_setpoint=setpoint->angle-current->angle;

	if(pivot_setpoint>M_PI)
		pivot_setpoint=pivot_setpoint-2*M_PI;
	else
	{
		if(pivot_setpoint<-M_PI)
			pivot_setpoint=pivot_setpoint+2*M_PI;
	}

	if(RIGHT_WHEEL == pivot_wheel)		// We lock the right wheel
	{
		setpoint->right_encoder	= current->right_encoder;
		setpoint->left_encoder	= current->left_encoder + (CPU_INT16U)(pivot_setpoint * CONVERSION_RAD_TO_MM * CONVERSION_MM_TO_INC_LEFT);
	}
	else if (LEFT_WHEEL == pivot_wheel)	// We lock the left wheel
	{
		setpoint->left_encoder	= current->left_encoder;
		setpoint->right_encoder	= current->right_encoder + (CPU_INT16U)(pivot_setpoint * CONVERSION_RAD_TO_MM * CONVERSION_MM_TO_INC_RIGHT);
	}
	else
	{
		AppDebugMsg("Ta mere suce des bites en enfer!\n");
	}
}


// ------------------------------------------------------------------------------------------------
// TaskAsser_Main()
// ------------------------------------------------------------------------------------------------
void TaskAsser_Main(void *p_arg)
{
//	INT8U command = 0;
	INT8U Err;
	char uart_buffer[13];
	char * buffer_ptr;
	
	// Asser Datas
	float raw_command_left;
	float raw_command_right;
	INT16S command_left;
	INT16S command_right;
	
	int mode_control=0;

	unsigned char end_movement_flag = 1;

	// Var from TaskMvt
	unsigned int	LastTaskAsserCmdId		= 0;			// ID used for detecting new msg from TaskMvt
    StructCmd       CurrentCmd;                             // Data for storing current order from TaskMvt (to be done)


//	float speed_ratio = SPEED_RATIO;

	AppDebugMsg("OUFFF TEAM 2014 : Asser online\n");

	init_control_motion();
	
	TaskOdo_GetCurrentPos(&TaskAsser_CurrentPos);
	mode_control	= 3;	// Use Mixed Mode
	setpoint.angle	= TaskAsser_CurrentPos.angle;
	setpoint.x		= TaskAsser_CurrentPos.x;
	setpoint.y		= TaskAsser_CurrentPos.y;

	while(OS_TRUE)
	{
		OSTimeDlyHMSM(0,0,0,ASSER_SAMPLING);
	
		// Read CurrentPos
		TaskOdo_GetCurrentPos(&TaskAsser_CurrentPos);

		// Check Last CmdID received from TaskMvt, if a new msg is ready, we use it
		if(App_CmdToTaskAsserId > LastTaskAsserCmdId)										
		{
            // Ask for Mutex
            OSMutexPend(App_MutexCmdToTaskAsser, WAIT_FOREVER, &Err);
            {	
                // Get current Cmd
                memcpy(&CurrentCmd, &App_CmdToTaskAsser, sizeof(StructCmd));
            }	
            OSMutexPost(App_MutexCmdToTaskAsser);

            // Update last CmdID used
            LastTaskAsserCmdId = App_CmdToTaskAsserId;

            // Cmd Analysis
            switch(CurrentCmd.Cmd)
            {
			// -------------------------------------------------------------
			case App_SetNewPos:
				// Change robot position
				mode_control						= 3;	// Use Mixed Mode
				setpoint.angle						= CurrentCmd.Param4;
				setpoint.x							= CurrentCmd.Param2;
				setpoint.y							= CurrentCmd.Param3;

				TaskOdo_SetCurrentPos(&setpoint);
				break;

			// -------------------------------------------------------------
            case Mvt_UseAngleOnly:
				mode_control						= 1;	// Use Angle Mode
				setpoint.angle						= CurrentCmd.Param4;
				distance_quadramp_data.speed_order	= CurrentCmd.Param1 * 0.01;
				break;

			// -------------------------------------------------------------
            case Mvt_UseDistOnly:
				mode_control						= 2;	// Use Dist Mode
				setpoint.x							= CurrentCmd.Param2;
				setpoint.y							= CurrentCmd.Param3;
				distance_quadramp_data.speed_order	= CurrentCmd.Param1 * 0.01;
				break;

			// -------------------------------------------------------------
		    case MvtSimple_RotateInDeg:
			case MvtSimple_MoveInMM:
			case MvtSimple_RotateToAngleInDeg:
            case Mvt_UseMixedMode:
			case Mvt_UseSpline:
				mode_control						= 3;	// Use Mixed Mode
				setpoint.angle						= CurrentCmd.Param4;
				setpoint.x							= CurrentCmd.Param2;
				setpoint.y							= CurrentCmd.Param3;
				distance_quadramp_data.speed_order	= CurrentCmd.Param1 * 0.01;
				break;

			// -------------------------------------------------------------
            case Mvt_Stop:
				TaskOdo_GetCurrentPos(&TaskAsser_CurrentPos);

				mode_control						= 3;	// Use Mixed Mode
				setpoint.angle						= TaskAsser_CurrentPos.angle;
				setpoint.x							= TaskAsser_CurrentPos.x;
				setpoint.y							= TaskAsser_CurrentPos.y;
				distance_quadramp_data.speed_order	= CurrentCmd.Param1 * 0.01;
				break;

			// -------------------------------------------------------------
            case Mvt_UsePivotMode:
				mode_control						= 4;	// Use Pivot Mode

				setpoint.angle=CurrentCmd.Param4;
				pivot_setpoint_computation(&TaskAsser_CurrentPos, CurrentCmd.Param2, &setpoint);
				distance_quadramp_data.speed_order	= CurrentCmd.Param1 * 0.01;
				break;

			// -------------------------------------------------------------
            default:
                break;
            }


		}

		// MOTION CONTROL LOOP

		// Reset_datas
		command_left =0;
		command_right =0;

		TaskOdo_GetCurrentPos(&TaskAsser_CurrentPos);

		// Asser mode control
		switch(mode_control)
		{
			case 1: // Angle only
				end_movement_flag=mode_1_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				break;
			case 2: //Distance only
				end_movement_flag=mode_2_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				break;
			case 3:
				end_movement_flag=mode_3_control_motion(&setpoint, &TaskAsser_CurrentPos, &raw_command_right, &raw_command_left);
				break;
			case 4: // pivot
				end_movement_flag=mode_4_control_motion(&setpoint, &TaskAsser_CurrentPos, distance_quadramp_data.speed_order, &raw_command_right, &raw_command_left);
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
