#include <incap.h>

#ifdef _IC9IF

/********************************************************************
*    Function Name:  ConfigIntCapture9                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture9(unsigned int config)
{
    _IC9IF = 0;                    /* Clear IF bit */
    _IC9IP = (config & 0x0007);    /*assigning Interrupt  Priority
                                                              to IPC*/
    _IC9IE = (config & 0x0008)>>3; /*assign Interrupt Enable/
                                                            Disable */
}

#else
#warning "Does not build on this target"
#endif
