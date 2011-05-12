/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskSensors.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
* 2009-04-01 | PBE | Mise à jour pour la coupe 2011
*********************************************************************************************************
*/

#include "TaskSensors.h"

// ------------------------------------------------------------------------------------------------
BOOLEAN TaskSensors_IsStartButtonPressed()
{
#ifdef _TARGET_440H
	if(CLIC_state(SW1) == 1)
		return OS_TRUE;
	else
		return OS_FALSE;
#else
	if(START_State()==0) return OS_TRUE;
	else return OS_FALSE;
#endif
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_CheckBumpers()
{
	char uart_buffer[8];
	char * buffer_ptr;
	INT8U	Err = 0;						// Var to get error status
	CPU_INT16U  GP2Data;

/* Todo
	//GP2_1 : Front *************************************************
	GP2Data  = ADC_GetVal (GP2_1);
	//putsUART2("GP2_1 : ");
	//buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) GP2Data, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	//putsUART2(buffer_ptr);
	//putsUART2("  ");

	// Check Value
#ifdef APP_GP2D2_LIMIT_FRONT
	if(GP2Data > APP_GP2D2_LIMIT_FRONT)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2D2_FRONT, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2D2_FRONT, OS_FLAG_CLR, &Err); 
#endif

	//GP2_2 : Back **************************************************
	GP2Data  = ADC_GetVal (GP2_2);
//	putsUART2("GP2_2 : ");
//	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) GP2Data, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
//	putsUART2(buffer_ptr);
//	putsUART2("  ");

	// Check Value
#ifdef APP_GP2D2_LIMIT_BACK
	if(GP2Data > APP_GP2D2_LIMIT_BACK)
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2D2_BACK, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_GP2D2_BACK, OS_FLAG_CLR, &Err); 
#endif

	//GP2_3 : Not Used **********************************************
	//GP2Data  = ADC_GetVal (GP2_3);
	//putsUART2("GP2_3 : ");
	//buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) GP2Data, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	//putsUART2(buffer_ptr);
	//putsUART2("  ");
	
	//GP2_4 : Not Used **********************************************
	//GP2Data  = ADC_GetVal (GP2_4);
	//putsUART2("GP2_4 : ");
	//buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) GP2Data, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	//putsUART2(buffer_ptr);
	//putsUART2("  ");
		
	//GP2_5 : Not Used **********************************************
	//GP2Data  = ADC_GetVal (GP2_5);
	//putsUART2("GP2_5 : ");
	//buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) GP2Data, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	//putsUART2(buffer_ptr);
	//putsUART2("\n");
*/
	return;
}

void TaskSensors_CheckSW()
{
	INT8U	Err = 0;						// Var to get error status

#ifdef _TARGET_440H

#else
	// CLIC_1 : Front Left ******************************************
	if(CLIC_state(CLIC_1))	
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC1, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC1, OS_FLAG_CLR, &Err); 

	// CLIC_2 : Front Right *****************************************
	if(CLIC_state(CLIC_2))
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC2, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC2, OS_FLAG_CLR, &Err); 

	// CLIC_3 : Front Center ****************************************
	if(CLIC_state(CLIC_3))		
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC3, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC3, OS_FLAG_CLR, &Err); 

	// CLIC_4 : Back Center *****************************************
	if(CLIC_state(CLIC_4))		
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC4, OS_FLAG_SET, &Err); 
	else
		OSFlagPost(AppFlags, APP_PARAM_APPFLAG_BUMPER_CLIC4, OS_FLAG_CLR, &Err); 
#endif
}

// ------------------------------------------------------------------------------------------------
void TaskSensors_ReadColor()
{
	#ifdef _TARGET_440H
		if(CLIC_state(SW2) == 1)
		{
			AppCurrentColor = c_ColorA;	
		}
		else
		{
			AppCurrentColor = c_ColorB;	
		}
	#else
	// Todo
		// Read current color
//		if(COLOR_Read() == 0)
//			AppCurrentColor = c_Blue;
//		else	
//			AppCurrentColor = c_Yellow;
	#endif

	return;
}

// ------------------------------------------------------------------------------------------------
// TaskSensors_Main()
// ------------------------------------------------------------------------------------------------
void TaskSensors_Main(void *p_arg)
{
	INT8U	Err = 0;				// Var to get error status
	CPU_INT16U  GP2Data;

	putsUART2("OUFFF TEAM 2011 : Sensors online\n");

	if(APP_INIT_USE_START_BUTTON == OS_TRUE)
	{
		// We're waiting for Start button release
		while(OS_FALSE == TaskSensors_IsStartButtonPressed())
		{
			TaskSensors_ReadColor();
			OSTimeDly(1);	// Release proc
		}

		// We're waiting for start button activation
		while(OS_TRUE == TaskSensors_IsStartButtonPressed())
		{
			TaskSensors_ReadColor();
			OSTimeDly(1);	// Release proc
		}
	}

	TaskSensors_ReadColor();

	// StartButton has been pressed
	OSFlagPost(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_SET, &Err); 

	while(OS_TRUE)	// Main task: we check all other sensors
	{
		OSTimeDlyHMSM(0, 0, 0, 10);	
	}
}
