/*********************************************************************
*    Function Name:  CloseI2C
*    Description:    This routine disables the I2C module by 
*                    clearing the I2CEN bit in I2CCON register.
*                    The MI2C and SI2C interrupts are disabled and 
*                    the corresponding IF flags are cleared
*    Parameters:     void
*    Return Value:   void
*********************************************************************/

#include "i2c.h"

#ifdef _MI2CIF

void CloseI2C(void)
{
	/* clear the I2CEN bit */
	I2CCONbits.I2CEN = 0;

	/* clear the SI2C & MI2C Interrupt enable bits */
	_SI2CIE = 0;
	_MI2CIE = 0;

	/* clear the SI2C & MI2C Interrupt flag bits */
	_SI2CIF = 0;
	_MI2CIF = 0;
}

#else
#warning "Does not build on this target"
#endif
