#include <outcompare.h>

#ifdef _OC15IF

/********************************************************************
*    Function Name:  SetDCOC15PWM                                    *
*    Description:    This routine writes the duty cycle and period    *
*    Parameters:     unsigned int duty cycle                        *
*    Return Value:   None                                           *
********************************************************************/

char  SetDCOC15PWM(unsigned int dutycycle,unsigned int period)
{   
    /* check if OC is in PWM Mode */
#if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in PWM Mode */
    if((OC15CON1bits.OCM & 0x06) == 0x06) 
    {
       OC15R = dutycycle;   /* assign to OCRS */
       OC15RS = period;
       return 1;
    }   
    else
       return -1;  

#else

 /* check if OC is in PWM Mode */
    if((OC15CONbits.OCM & 0x06) == 0x06) 
    {
       OC15RS = dutycycle;   /* assign to OCRS */
       return 1;
    }
    else
       return -1;
#endif

}
#else
#warning "Does not build on this target"
#endif
