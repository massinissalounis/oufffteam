#include <incap.h>

#ifdef _IC4IF

/********************************************************************
*    Function Name:  ConfigIntCapture4                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture4(unsigned int config)
{
    _IC4IF = 0;                   /* Clear IF bit */
    _IC4IP = (config &0x0007);    /* assigning Interrupt Priority
                                             to IPC Register             */
    _IC4IE = (config &0x0008) >> 3;/* assiging Interrupt Enable/
                                              Disable Register           */
}

#else
#warning "Does not build on this target"
#endif
