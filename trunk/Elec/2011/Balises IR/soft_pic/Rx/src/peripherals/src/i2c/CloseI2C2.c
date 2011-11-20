/*********************************************************************
*    Function Name:  CloseI2C2
*    Description:    This routine disables the I2C2 module by 
*                    clearing the I2CEN bit in I2C2CON register.
*                    The MI2C2 and SI2C2 interrupts are disabled and 
*                    the corresponding IF flags are cleared
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C2IF)

void CloseI2C2(void)
{
	/* clear the I2CEN bit */
	I2C2CONbits.I2CEN = 0;

	/* clear the SI2C2 & MI2C2 Interrupt enable bits */
	_SI2C2IE = 0;
	_MI2C2IE = 0;

	/* clear the SI2C2 & MI2C2 Interrupt flag bits */
	_SI2C2IF = 0;
	_MI2C2IF = 0;
}

#else
#warning "Does not build on this target"
#endif
