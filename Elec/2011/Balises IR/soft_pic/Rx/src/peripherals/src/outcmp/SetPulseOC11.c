#include <outcompare.h>

#ifdef _OC11IF

/*************************************************************************
*    Function Name:  SetPulseOC11                                        *
*    Description:    This routine writes the pulse_start to Main register*
*                    and pulse_stop to Secondary register                *
*    Parameters:     unsigned int pulse_start,unsigned int pulse_stop    *
*    Return Value:   None                                                *
*************************************************************************/

void SetPulseOC11(unsigned int pulse_start, unsigned int pulse_stop)
{   
  #if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in NON PWM Mode */
    if( (OC11CON1bits.OCM & 0x06) != 0x06) 
    {
        OC11R = pulse_start; /* assign pulse_start to Main Register */
        OC11RS = pulse_stop; /* assign pulse_stop to Secondary Register */
    }

#else

    /* check if OC is in NON PWM Mode */
    if( (OC11CONbits.OCM & 0x06) != 0x06) 
    {
        OC11R = pulse_start; /* assign pulse_start to Main Register */
        OC11RS = pulse_stop; /* assign pulse_stop to Secondary Register */
    }

#endif
}

#else
#warning "Does not build on this target"
#endif
