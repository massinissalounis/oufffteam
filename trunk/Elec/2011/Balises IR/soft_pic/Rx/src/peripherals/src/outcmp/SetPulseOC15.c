#include <outcompare.h>

#ifdef _OC15IF

/*************************************************************************
*    Function Name:  SetPulseOC15                                        *
*    Description:    This routine writes the pulse_start to Main register*
*                    and pulse_stop to Secondary register                *
*    Parameters:     unsigned int pulse_start,unsigned int pulse_stop    *
*    Return Value:   None                                                *
*************************************************************************/

void SetPulseOC15(unsigned int pulse_start, unsigned int pulse_stop)
{   
  #if defined(__dsPIC33E__) || defined(__PIC24E__) 

    /* check if OC is in NON PWM Mode */
    if( (OC15CON1bits.OCM & 0x06) != 0x06) 
    {
        OC15R = pulse_start; /* assign pulse_start to Main Register */
        OC15RS = pulse_stop; /* assign pulse_stop to Secondary Register */
    }

#else

    /* check if OC is in NON PWM Mode */
    if( (OC15CONbits.OCM & 0x06) != 0x06) 
    {
        OC15R = pulse_start; /* assign pulse_start to Main Register */
        OC15RS = pulse_stop; /* assign pulse_stop to Secondary Register */
    }

#endif
}

#else
#warning "Does not build on this target"
#endif
