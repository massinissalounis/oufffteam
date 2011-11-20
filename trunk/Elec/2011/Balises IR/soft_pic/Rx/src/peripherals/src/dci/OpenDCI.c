#include "dci.h"

#ifdef _DCIIF

/*******************************************************************************
*    Function Name : OpenDCI
*    Description   : This routine configures: the DCICON1 register which 
*                    contains information about Enable bit, Frame Sync mode, 
*                    Data Justification, Sample Clock Direction, Sample Clock 
*                    Edge Control, Output Frame Synchronization Directions 
*                    Control, Continuous Transmit/Receive mode, Underflow mode.
*
*                    DCICON2 register which contains the Frame Sync Generator 
*                    Control, Data Word Size bits, Buffer Length control bits.
*
*                    DCICON3 which contains the clock generator control bits.
*
*                    TSCON which contains the  transmit time slot enable 
*                    control bit.
*
*                    RSCON which contains the receive time slot enable 
*                    control bit .
*
*    Parameters   :  unsigned int : config1
*                    unsigned int : config2
*                    unsigned int : config3
*                    unsigned int : trans_mask
*                    unsigned int : recv_mask
*    Return Value :  None
*******************************************************************************/

void OpenDCI(unsigned int config1, unsigned int config2,
             unsigned int config3, unsigned int trans_mask,
             unsigned int recv_mask)
{
     DCICON3 = config3;
     DCICON1 = config1;
     DCICON2 = config2;
     TSCON = trans_mask;
     RSCON = recv_mask;
}

#else
#warning "Does not build on this target"
#endif
