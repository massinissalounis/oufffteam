#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*************************************************************************
* Function Name     : CAN2SetMask
* Description       : This function sets the values for the acceptance 
*                     filter mask registers (SID and EID)
* Parameters        : char: mask_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
**************************************************************************/

void CAN2SetMask(char mask_no, unsigned int sid, unsigned long eid)
{ 
    unsigned int uppereid = eid >>16; 
    switch(mask_no)
    {
    case 0:
      C2RXM0SID = sid;
      C2RXM0EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C2RXM0EIDL = eid;          /*lower 16 to EIDL */
      break;
    case 1:
      C2RXM1SID = sid;
      C2RXM1EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C2RXM1EIDL = eid;          /*lower 16 to EIDL */
      break;
    default:
      C2RXM0SID = sid;
      C2RXM0EIDH = uppereid;     /*upper 16 to the EIDH reg */
      C2RXM0EIDL = eid;          /*lower 16 to EIDL */
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

