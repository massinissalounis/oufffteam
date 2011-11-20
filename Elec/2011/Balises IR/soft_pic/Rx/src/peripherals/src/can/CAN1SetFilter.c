#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C1IF

/*********************************************************************
* Function Name     : CAN1SetFilter
* Description       : This function sets the acceptance filter values 
*                     (SID and EID) for the specified filter
* Parameters        : char: filter_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
*********************************************************************/

void CAN1SetFilter(char filter_no, unsigned int sid, unsigned long eid)
{  
    unsigned int uppereid = eid >>16; 
    switch(filter_no)
    {
    case 0:
      C1RXF0SID = sid;
      C1RXF0EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF0EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 1:
      C1RXF1SID = sid;
      C1RXF1EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF1EIDL = eid;        /*lower 16 to EIDH */
      break;
    case 2:
      C1RXF2SID = sid;
      C1RXF2EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF2EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 3:
      C1RXF3SID = sid;
      C1RXF3EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF3EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 4:
      C1RXF4SID = sid;
      C1RXF4EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF4EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 5:
      C1RXF5SID = sid;
      C1RXF5EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF5EIDL = eid;        /*lower 16 to EIDL */
      break;
    default:
      C1RXF0SID = sid;
      C1RXF0EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C1RXF0EIDL = eid;        /*lower 16 to EIDL */
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif

