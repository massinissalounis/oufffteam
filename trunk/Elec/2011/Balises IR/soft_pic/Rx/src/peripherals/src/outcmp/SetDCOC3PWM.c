#include <outcompare.h>

#ifdef _OC3IF

/********************************************************************
*    Function Name:  SetDCOC3PWM                                    *
*    Description:    This routine writes the duty cycle and period    *
*    Parameters:     unsigned int duty cycle, *
*	unsigned int period (dsPIC33E/PIC24E only) *
*    Return Value:   None                                           *
********************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC3PWM (unsigned int dutycycle, unsigned int period)
{   
    /* check if OC is in PWM Mode */
    if((OC3CON1bits.OCM & 0x06) == 0x06) 
    {
       OC3R = dutycycle;   /* assign to OCRS */
       OC3RS = period;
       return 1;
    }   
    else
       return -1;  
}
#else
char SetDCOC3PWM (unsigned int dutycycle)
{
 /* check if OC is in PWM Mode */
    if((OC3CONbits.OCM & 0x06) == 0x06) 
    {
       OC3RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
}
#endif

#else
#warning "Does not build on this target"
#endif
