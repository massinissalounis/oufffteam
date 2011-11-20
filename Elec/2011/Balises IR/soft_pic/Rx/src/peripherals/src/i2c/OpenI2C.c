/******************************************************************************
*    Function Name:  OpenI2C
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

#ifdef _MI2CIF

void OpenI2C(unsigned int config1, unsigned int config2)
{
    I2CBRG = config2;
    I2CCON = config1;
}

#else
#warning "Does not build on this target"
#endif
