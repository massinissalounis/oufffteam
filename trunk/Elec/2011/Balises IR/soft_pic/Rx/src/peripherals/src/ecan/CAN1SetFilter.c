#include <ecan.h>

#ifdef _C1TXIF

/*********************************************************************
* Function Name     : CAN1SetFilter
* Description       : This function sets the acceptance filter values 
*                     (SID and EID) for the specified filter
* Parameters        : unsigned char: filter_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
*********************************************************************/

void CAN1SetFilter(unsigned char filter_no, unsigned int sid, unsigned long eid)
{  
    unsigned short eidh, temp1, temp2;
    eidh = (unsigned short) (((eid & 0x30000) >> 16)| 0xFFE8);
    temp1 = sid & eidh;
    temp2 = (unsigned short)eid;      
    switch(filter_no)
    {
    case 0:
      C1RXF0SID = sid & eidh;
      C1RXF0EID = (unsigned short)eid;       
      break;
    case 1:
      C1RXF1SID = sid & eidh;
      C1RXF1EID = (unsigned short)eid;       
      break;

    case 2:
      C1RXF2SID = sid & eidh;
      C1RXF2EID = (unsigned short)eid;       
      break;

    case 3:
      C1RXF3SID = sid & eidh;
      C1RXF3EID = (unsigned short)eid;       
      break;

    case 4:
      C1RXF4SID = sid & eidh;
      C1RXF4EID = (unsigned short)eid;       
      break;

    case 5:
      C1RXF5SID = sid & eidh;
      C1RXF5EID = (unsigned short)eid;       
      break;

    case 6:
      C1RXF6SID = sid & eidh;
      C1RXF6EID = (unsigned short)eid;       
      break;

    case 7:
      C1RXF7SID = sid & eidh;
      C1RXF7EID = (unsigned short)eid;       
      break;

    case 8:
      C1RXF8SID = sid & eidh;
      C1RXF8EID = (unsigned short)eid;       
      break;

    case 9:
      C1RXF9SID = sid & eidh;
      C1RXF9EID = (unsigned short)eid;       
      break;

    case 10:
      C1RXF10SID = sid & eidh;
      C1RXF10EID = (unsigned short)eid;       
      break;

    case 11:
      C1RXF11SID = sid & eidh;
      C1RXF11EID = (unsigned short)eid;       
      break;

    case 12:
      C1RXF12SID = sid & eidh;
      C1RXF12EID = (unsigned short)eid;       
      break;

    case 13:
      C1RXF13SID = sid & eidh;
      C1RXF13EID = (unsigned short)eid;       
      break;

    case 14:
      C1RXF14SID = sid & eidh;
      C1RXF14EID = (unsigned short)eid;       
      break;

    case 15:
      C1RXF15SID = sid & eidh;
      C1RXF15EID = (unsigned short)eid;       
      break;

    default:
      C1RXF0SID = sid & eidh;
      C1RXF0EID = (unsigned short)eid;        
      break;
    }
}

#else
#warning "Does not build on this target"
#endif
