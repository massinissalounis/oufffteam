#include <incap.h>

#ifdef _IC8IF

/********************************************************************
*    Function Name:  ConfigIntCapture8                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture8(unsigned int config)
{
    _IC8IF = 0;                    /* Clear IF bit */
    _IC8IP = (config & 0x0007);    /*assigning Interrupt  Priority
                                                              to IPC*/
    _IC8IE = (config & 0x0008)>>3; /*assign Interrupt Enable/
                                                            Disable */
}

#else
#warning "Does not build on this target"
#endif
