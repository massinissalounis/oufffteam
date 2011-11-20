#include <outcompare.h>

#ifdef _OC16IF

/********************************************************************
*    Function Name:  SetDCOC16PWM                                    *
*    Description:    This routine writes the duty cycle and period   *
*    Parameters:     unsigned int duty cycle                        *
*    Return Value:   None                                           *
********************************************************************/

char  SetDCOC16PWM(unsigned int dutycycle,unsigned int period)
{   
    /* check if OC is in PWM Mode */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in PWM Mode */
    if((OC16CON1bits.OCM & 0x06) == 0x06) 
    {
       OC16R = dutycycle;   /* assign to OCRS */
       OC16RS = period;
       return 1;
    }   
    else
       return -1;  

#else

 /* check if OC is in PWM Mode */
    if((OC16CONbits.OCM & 0x06) == 0x06) 
    {
       OC16RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
#endif

}
#else
#warning "Does not build on this target"
#endif
