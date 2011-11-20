#include <outcompare.h>

#ifdef _OC5IF

/********************************************************************
*    Function Name:  SetDCOC5PWM                                    *
*    Description:    This routine writes the duty cycle and period  *
*    Parameters:     unsigned int duty cycle, *
*	unsigned int period (dsPIC33E/PIC24E only) *
*    Return Value:   None                                           *
********************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC5PWM (unsigned int dutycycle, unsigned int period)
{   
    /* check if OC is in PWM Mode */
    if((OC5CON1bits.OCM & 0x06) == 0x06) 
    {
       OC5R = dutycycle;   /* assign to OCRS */
       OC5RS = period;
       return 1;
    }   
    else
       return -1;  
}
#else
char SetDCOC5PWM (unsigned int dutycycle)
{
 /* check if OC is in PWM Mode */
    if((OC5CONbits.OCM & 0x06) == 0x06) 
    {
       OC5RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
}
#endif

#else
#warning "Does not build on this target"
#endif
