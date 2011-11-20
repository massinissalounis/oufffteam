#include <outcompare.h>

#ifdef _OC9IF

/********************************************************************
*    Function Name:  SetDCOC9PWM                                    *
*    Description:    This routine writes the duty cycle and period  *
*    Parameters:     unsigned int duty cycle and period             *
*    Return Value:   None                                           *
********************************************************************/

char SetDCOC9PWM(unsigned int dutycycle,unsigned int period)
{   
    /* check if OC is in PWM Mode */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in PWM Mode */
    if((OC9CON1bits.OCM & 0x06) == 0x06) 
    {
       OC9R = dutycycle;   /* assign to OCRS */
       OC9RS = period;
       return 1;
    }   
    else
       return -1;  

#else

 /* check if OC is in PWM Mode */
    if((OC9CONbits.OCM & 0x06) == 0x06) 
    {
       OC9RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
#endif

}
#else
#warning "Does not build on this target"
#endif
