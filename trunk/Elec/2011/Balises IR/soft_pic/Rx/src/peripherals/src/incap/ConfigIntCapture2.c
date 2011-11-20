#include <incap.h>

#ifdef _IC2IF

/********************************************************************
*    Function Name:  ConfigIntCapture2                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture2(unsigned int config)
{
    _IC2IF = 0;                     /* Clear IF bit */
    _IC2IP = (config &0x0007);      /* assigning Interrupt Priority
                                             to IPC Control REgister */
    _IC2IE = (config &0x0008) >> 3; /* assiging InputCapture Enable/
                                              Disable bit of IEC Register*/
}

#else
#warning "Does not build on this target"
#endif
