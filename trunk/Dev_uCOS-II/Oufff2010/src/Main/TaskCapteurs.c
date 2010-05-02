/*
*********************************************************************************************************
*                                         Association OufffTEAM
*                                     Coupe de France de Robotique
*
*
* File : TaskCapteurs.c
*
* Suivi de version :
* 2009-02-11 | PBE | Creation de la version de base pour la coupe 2010
*********************************************************************************************************
*/

#include "TaskCapteurs.h"
#include "AppGlobalVars.h"

// ------------------------------------------------------------------------------------------------
BOOLEAN TaskCapteurs_IsStartButtonPressed()
{
	if(START_State()==0) return OS_TRUE;
	else return OS_FALSE;
}

// ------------------------------------------------------------------------------------------------
void TaskCapteurs_CheckBumpers()
{
	return;
}

// ------------------------------------------------------------------------------------------------
void TaskCapteurs_ReadColor()
{
	#ifdef _TARGET_STARTER_KIT
		AppCurrentColor = c_Blue;	
	#else
		// Read current color
		if(COLOR_Read() == 0)
			AppCurrentColor = c_Blue;
		else	
			AppCurrentColor = c_Yellow;
	#endif

	return;
}

// ------------------------------------------------------------------------------------------------
// TaskCapteurs_Main()
// ------------------------------------------------------------------------------------------------
void TaskCapteurs_Main(void *p_arg)
{
	INT8U	Err = 0;				/* Var to get error status								*/

	putsUART2("OUFFF TEAM 2010 : Capteurs online\n");

	#ifdef _TARGET_STARTER_KIT
		OSTimeDlyHMSM(0, 0, 0, 500);	LED_Off(1);	
		OSTimeDlyHMSM(0, 0, 0, 500);	LED_Off(2);	
		OSTimeDlyHMSM(0, 0, 0, 500);	LED_Off(3);
	#else
	// Comment this part to disable start button detection
		// We're waiting for Start button release
		while(OS_FALSE == TaskCapteurs_IsStartButtonPressed())
			OSTimeDly(1);	// Release proc

		// We're waiting for start button activation
		while(OS_TRUE == TaskCapteurs_IsStartButtonPressed())
			OSTimeDly(1);	// Release proc 
	#endif

	// StartButton has been pressed
	// We set the current color
	TaskCapteurs_ReadColor();
	
	OSFlagPost(AppFlags, APP_PARAM_APPFLAG_START_BUTTON, OS_FLAG_SET, &Err); 

	while(OS_TRUE)	// Main task: we check all other sensors
	{
		TaskCapteurs_CheckBumpers();			// Check for bumpers status

	CPU_INT16U  toto;
	char uart_buffer[8];
	char * buffer_ptr;
		// test adc CBE
		//GP2_1
		toto  = ADC_GetVal (GP2_1);
//		putsUART2("GP2_1 : ");
//		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) toto, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
//		putsUART2(buffer_ptr);
//		putsUART2("  ");
		OSTimeDly(100);
		
		//GP2_2
		toto  = ADC_GetVal (GP2_2);
//		putsUART2("GP2_2 : ");
//		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) toto, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
//		putsUART2(buffer_ptr);
//		putsUART2("  ");
		OSTimeDly(100);
		
		//GP2_3
		toto  = ADC_GetVal (GP2_3);
//		putsUART2("GP2_3 : ");
//		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) toto, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
//		putsUART2(buffer_ptr);
//		putsUART2("  ");
		OSTimeDly(100);

		//GP2_4
		toto  = ADC_GetVal (GP2_4);
//		putsUART2("GP2_4 : ");
//		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) toto, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
//		putsUART2(buffer_ptr);
//		putsUART2("  ");
		OSTimeDly(100);

		//GP2_5
		toto  = ADC_GetVal (GP2_5);
//		putsUART2("GP2_5 : ");
//		buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) toto, (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
//		putsUART2(buffer_ptr);
//		putsUART2("\n");
	}
}
