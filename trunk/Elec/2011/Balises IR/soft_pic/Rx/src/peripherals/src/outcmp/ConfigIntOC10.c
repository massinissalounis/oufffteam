#include <outcompare.h>

#ifdef _OC10IF

/************************************************************************
*    Function Name:  ConfigIntOC10                                   	*
*    Description:    This Function Configures Interrupt and sets        *
*                    Interrupt Priority                                 *
*    Parameters:     unsigned int config                                *
*    Return Value:   None                                               *
************************************************************************/

void ConfigIntOC10(unsigned int config)
{
    _OC10IF = 0;                   /* Clear IF bit */
    _OC10IP = (config &0x0007);    /* Assign Interrupt Priority */
    _OC10IE = (config &0x0008)>>3; /* Enable/disable Interrupt */
}

#else
#warning "Does not build on this target"
#endif
