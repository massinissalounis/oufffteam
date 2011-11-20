#include <outcompare.h>

#ifdef _OC4IF

/********************************************************************
*    Function Name:  SetDCOC4PWM                                    *
*    Description:    This routine writes the duty cycle and period  *
*    Parameters:     unsigned int duty cycle, *
*	unsigned int period (dsPIC33E/PIC24E only) *
*    Return Value:   None                                           *
********************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC4PWM (unsigned int dutycycle, unsigned int period)
{   
    /* check if OC is in PWM Mode */
    if((OC4CON1bits.OCM & 0x06) == 0x06) 
    {
       OC4R = dutycycle;   /* assign to OCRS */
       OC4RS = period;
       return 1;
    }   
    else
       return -1;  
}
#else
char SetDCOC4PWM (unsigned int dutycycle)
{
 /* check if OC is in PWM Mode */
    if((OC4CONbits.OCM & 0x06) == 0x06) 
    {
       OC4RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
}
#endif

#else
#warning "Does not build on this target"
#endif
