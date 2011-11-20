#include <incap.h>

#ifdef _IC6IF

/********************************************************************
*    Function Name:  ConfigIntCapture6                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture6(unsigned int config)
{
    _IC6IF = 0;                     /* Clear IF bit */
    _IC6IP = (config & 0x0007);     /* assigning Interrupt Priority to IPC */
    _IC6IE = (config & 0x0008)>>3;  /* assiging Interrupt Enable/ Disable */
}

#else
#warning "Does not build on this target"
#endif
