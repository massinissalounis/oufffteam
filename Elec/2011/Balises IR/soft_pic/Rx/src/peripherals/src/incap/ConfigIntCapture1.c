#include <incap.h>

#ifdef _IC1IF

/********************************************************************
*    Function Name:  ConfigIntCapture1                              *
*    Description:    Set the Enable Interrupts and Interrupt        *
*                    Priorites  to the Interrupt Control and        *
*                    Interrupt Priority Register respectively       *
*    Parameters:     unsigned int config                            *
*    Return Value:   None                                           *
********************************************************************/

void ConfigIntCapture1(unsigned int config)
{
    _IC1IF = 0;                    /* Clear IF bit */
    _IC1IP = (config &0x0007);     /*assigning Interrupt Priority
                                                    to IPC Register */
    _IC1IE = (config &0x0008) >> 3;/*assiging Interrupt Enable/
                                                        Disable.   */   
}

#else
#warning "Does not build on this target"
#endif
