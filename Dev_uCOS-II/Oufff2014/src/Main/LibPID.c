#include "AppIncludes.h"
#include "LibPID.h"

/////////////////////////////////////////////////////////////
// FILTERS
/////////////////////////////////////////////////////////////
void QUADRAMP_Initialization(QUADRAMP_data *data, float acc, float speed, float approach)
{
	data->acceleration_order=acc;
	data->speed_order=speed;
	
	data->final_approach_limit=approach;

	data->origin=0.0;
	data->acc_distance=0.0;

	data->speed=0.0;

	data->state=0;
}

float QUADRAMP_Compute(QUADRAMP_data *data, float dist2dest)
{
	float dist2dest_abs = abs(dist2dest);

	switch(data->state)
	{
		case 0:
			data->origin=dist2dest_abs; // Update the origin for the next movement
			data->speed=data->speed_order; // Speed at the limit to ensure a good reactivity

			if(dist2dest_abs > data->final_approach_limit)
			{
				data->speed=0; // Initialize the speed of the new movement
				data->state=1; // Go into acc state
			}
			break;

		case 1:
			data->speed+=data->acceleration_order;

			if(dist2dest_abs <= (data->origin - data->final_approach_limit/2) / 2)
			{
				data->state=3; // Go to decc state
			}

			if(data->speed>=data->speed_order)
			{
				data->speed=data->speed_order; // Limit the speed
				data->acc_distance = data->origin - dist2dest_abs - data->final_approach_limit/2; // Store the distance requirement for the next decelleration
				data->state=2; // Go to cte speed state
			}
			break;
				
		case 2:
			data->speed=data->speed_order; // Update the speed

			if(dist2dest_abs <= data->acc_distance)
			{
				data->state=3;
			}
			break;

		case 3:
			data->speed-=data->acceleration_order;

			if(dist2dest_abs<=data->final_approach_limit)
			{
				data->state=0;
			}
			break;
				
		default:
			break;	
	}	

	Debug_AsserRampState = data->state;
	return data->speed;
}

void PID_Initialization(PID_data * pid_data, float Kp, float Ki, float Kd, float IMax)
{
	int i;

	pid_data->Kp = Kp;
	pid_data->Ki = Ki;
	pid_data->Kd = Kd;
	pid_data->IMax = IMax;

	for(i=0; i<PID_SUM_NB_SAMPLES; i++)
		pid_data->error_old[i]=0.0;

	pid_data->current_error_old = 0;
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
