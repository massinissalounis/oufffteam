#include "AppIncludes.h"
#include "TurbineControl.h"

// TURBINE ---------------------------------------------------------------------------------
void TURBINE_InitReg(void)
{

}

void TURBINE_On(void)
{
	SERVO_0_Write_Pulse (0x48); // Between 0x00 and 0xFF. Nominal value 0x30
}

void TURBINE_Off(void)
{
	SERVO_0_Write_Pulse (0x00);
}
