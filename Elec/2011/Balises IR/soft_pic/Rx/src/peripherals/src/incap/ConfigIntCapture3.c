#include <incap.h>

#ifdef _IC3IF

/********************************************************************
*    Function Name:  ConfigIntCapture3                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture3(unsigned int config)
{
    _IC3IF = 0;                   /* Clear IF bit */
    _IC3IP = (config &0x0007);    /* assigning Interrupt Priority 
                                             to IPC Register              */
    _IC3IE = (config &0x0008) >> 3;/* assiging Interrupt Enable/
                                              Disable to IEC Register    */
}

#else
#warning "Does not build on this target"
#endif
