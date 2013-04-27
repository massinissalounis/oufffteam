#include "AppIncludes.h"
#include "TurbineControl.h"

// TURBINE ---------------------------------------------------------------------------------
void TURBINE_InitReg(void)
{

}

void TURBINE_On(void)
{
	SERVO_0_Write_Pulse (0x80);
}

void TURBINE_Off(void)
{
	SERVO_0_Write_Pulse (0x00);
}
