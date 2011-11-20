#include <outcompare.h>

#ifdef _OC11IF

/********************************************************************
*    Function Name:  SetDCOC11PWM                                    *
*    Description:    This routine writes the duty cycle and period    *
*    Parameters:     unsigned int duty cycle                        *
*    Return Value:   None                                           *
********************************************************************/

char  SetDCOC11PWM(unsigned int dutycycle,unsigned int period)
{   
    /* check if OC is in PWM Mode */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in PWM Mode */
    if((OC11CON1bits.OCM & 0x06) == 0x06) 
    {
       OC11R = dutycycle;   /* assign to OCRS */
       OC11RS = period;
       return 1;
    }   
    else
       return -1;  

#else

 /* check if OC is in PWM Mode */
    if((OC11CONbits.OCM & 0x06) == 0x06) 
    {
       OC11RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
#endif

}
#else
#warning "Does not build on this target"
#endif
