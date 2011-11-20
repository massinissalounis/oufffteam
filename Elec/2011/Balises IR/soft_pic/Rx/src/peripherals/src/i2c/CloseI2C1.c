/*********************************************************************
*    Function Name:  CloseI2C1
*    Description:    This routine disables the I2C1 module by 
*                    clearing the I2CEN bit in I2C1CON register.
*                    The MI2C1 and SI2C1 interrupts are disabled and 
*                    the corresponding IF flags are cleared
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void CloseI2C1(void)
{
	/* clear the I2CEN bit */
	I2C1CONbits.I2CEN = 0;

	/* clear the SI2C & MI2C Interrupt enable bits */
	_SI2C1IE = 0;
	_MI2C1IE = 0;

	/* clear the SI2C & MI2C Interrupt flag bits */
	_SI2C1IF = 0;
	_MI2C1IF = 0;
}

#else
#warning "Does not build on this target"
#endif
