/******************************************************************************
*    Function Name:  OpenI2C1
*    Description:    This function configures the I2C module for enable bit, 
*                    disable slew rate, SM bus input levels, SCL release,
*                    Intelligent Peripheral Management Interface enable, 
*                    sleep mode, general call enable,acknowledge data bit, 
*                    acknowledge sequence enable, receive enable, stop 
*                    condition enable, restart condition enable and start
*                    condition enable. The Baud rate value is also configured
*    Parameters:     unsigned int : config1
*                    unsigned int : config2
*    Return Value:   void
*******************************************************************************/

#include "i2c.h"

#if defined(_MI2C1IF)

void OpenI2C1(unsigned int config1, unsigned int config2)
{
    I2C1BRG = config2;
    I2C1CON = config1;
}

#else
#warning "Does not build on this target"
#endif
