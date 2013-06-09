// Basic PIC control functions - Oufffteam 2014
// Pierre - Emmanuel GAILLARDON

#ifndef  LIBPID_H
#define  LIBPID_H

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/   

//////////////////////////////////////////////
// Local structures
//////////////////////////////////////////////
typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float IMax;
	float error_old[PID_SUM_NB_SAMPLES];
	int current_error_old;
	float error_sum;
}PID_data;

typedef struct {
	float acceleration_order;
	float speed_order;
	
	float final_approach_limit;
	float origin;
	float acc_distance;

	float speed;

	int state;  // 0: final, 1: acc, 2: Vcte, 3: Decell
}QUADRAMP_data;

//////////////////////////////////////////////
// Function definitions
//////////////////////////////////////////////
void QUADRAMP_Initialization(QUADRAMP_data *data, float acc, float speed, float approach);
float QUADRAMP_Compute(QUADRAMP_data *data, float dist2dest);

void PID_Initialization(void);
float PID_Computation(PID_data * pid_data, float error);




#endif // LIBPID_H
