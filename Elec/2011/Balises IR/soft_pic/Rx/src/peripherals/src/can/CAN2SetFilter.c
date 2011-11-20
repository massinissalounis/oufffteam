#include "can.h"

#if defined(__dsPIC30F__)

#ifdef _C2IF

/*********************************************************************
* Function Name     : CAN2SetFilter
* Description       : This function sets the acceptance filter values 
*                     (SID and EID) for the specified filter
* Parameters        : char: filter_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
*********************************************************************/

void CAN2SetFilter(char filter_no, unsigned int sid, unsigned long eid)
{  
    unsigned int uppereid = eid >>16; 
    switch(filter_no)
    {
    case 0:
      C2RXF0SID = sid;
      C2RXF0EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF0EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 1:
      C2RXF1SID = sid;
      C2RXF1EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF1EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 2:
      C2RXF2SID = sid;
      C2RXF2EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF2EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 3:
      C2RXF3SID = sid;
      C2RXF3EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF3EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 4:
      C2RXF4SID = sid;
      C2RXF4EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF4EIDL = eid;        /*lower 16 to EIDL */
      break;
    case 5:
      C2RXF5SID = sid;
      C2RXF5EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF5EIDL = eid;        /*lower 16 to EIDL */
      break;
    default:
      C2RXF0SID = sid;
      C2RXF0EIDH = uppereid;   /*upper 16 to the EIDH reg */
      C2RXF0EIDL = eid;        /*lower 16 to EIDL */
      break;
    }
}

#else
#warning "Does not build on this target"
#endif

#endif
