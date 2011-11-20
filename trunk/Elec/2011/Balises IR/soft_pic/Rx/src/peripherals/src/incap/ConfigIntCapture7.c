#include <incap.h>

#ifdef _IC7IF

/********************************************************************
*    Function Name:  ConfigIntCapture7                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture7(unsigned int config)
{
    _IC7IF = 0;                    /* Clear IF bit */
    _IC7IP = (config & 0x0007);    /*assigning Interrupt Priority
                                                              to IPC*/
    _IC7IE = (config & 0x0008)>>3; /*assigns Interrupt Enable/
                                                            Disable */
}

#else
#warning "Does not build on this target"
#endif
