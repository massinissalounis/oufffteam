#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*************************************************************************
* Function Name     : CAN2Initialize
* Description       : This function configures Sync jump width, Baud Rate
*                     Pre-scaler, Phase Buffer Segment 1 and 2, and 
*                     Propogation time segment.
* Parameters        : unsigned int: config1, unsigned int: config2
* Return Value      : None
**************************************************************************/

void CAN2Initialize(unsigned int config1, unsigned int config2)
{
    C2CFG1 = config1; /* configure SJWand BRP */
    C2CFG2 = config2; /* configure PHSEG2 and PHSEG1 and PROPSEG */
}

#else
#warning "Does not build on this target"
#endif

#endif

