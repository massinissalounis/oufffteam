#include <incap.h>

#ifdef _IC15IF

/********************************************************************
*    Function Name:  ConfigIntCapture15                             *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture15(unsigned int config)
{
    _IC15IF = 0;                    /* Clear IF bit */
    _IC15IP = (config & 0x0007);    /*assigning Interrupt  Priority
                                                              to IPC*/
    _IC15IE = (config & 0x0008)>>3; /*assign Interrupt Enable/
                                                            Disable */
}

#else
#warning "Does not build on this target"
#endif

