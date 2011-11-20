#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/*************************************************************************
* Function Name     : CAN1SetMask
* Description       : This function sets the values for the acceptance 
*                     filter mask registers (SID and EID)
* Parameters        : char: mask_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
**************************************************************************/

void CAN1SetMask(char mask_no, unsigned int sid, unsigned long eid)
{ 
    unsigned int uppereid = eid >>16; 
    switch(mask_no)
    {
    case 0:
      C1RXM0SID = sid;
      C1RXM0EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C1RXM0EIDL = eid;          /*lower 16 to EIDL */
      break;
    case 1:
      C1RXM1SID = sid;
      C1RXM1EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C1RXM1EIDL = eid;          /*lower 16 to EIDL */
      break;
    default:
      C1RXM0SID = sid;
      C1RXM0EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C1RXM0EIDL = eid;          /*lower 16 to EIDL */
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

