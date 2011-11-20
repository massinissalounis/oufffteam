#include <outcompare.h>

#ifdef _OC8IF

/********************************************************************
*    Function Name:  SetDCOC8PWM                                    *
*    Description:    This routine writes the duty cycle and period  *
*    Parameters:     unsigned int duty cycle, *
*	unsigned int period (dsPIC33E/PIC24E only) *
*    Return Value:   None                                           *
********************************************************************/

#if defined(__dsPIC33E__) || defined(__PIC24E__) 
char SetDCOC8PWM (unsigned int dutycycle, unsigned int period)
{   
    /* check if OC is in PWM Mode */
    if((OC8CON1bits.OCM & 0x06) == 0x06) 
    {
       OC8R = dutycycle;   /* assign to OCRS */
       OC8RS = period;
       return 1;
    }   
    else
       return -1;  
}
#else
char SetDCOC8PWM (unsigned int dutycycle)
{
 /* check if OC is in PWM Mode */
    if((OC8CONbits.OCM & 0x06) == 0x06) 
    {
       OC8RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
}
#endif

#else
#warning "Does not build on this target"
#endif
