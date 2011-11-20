#include <ecan.h>

#ifdef _C2TXIF

/*********************************************************************
* Function Name     : CAN2SetFilter
* Description       : This function sets the acceptance filter values 
*                     (SID and EID) for the specified filter
* Parameters        : unsigned char: filter_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
*********************************************************************/

void CAN2SetFilter(unsigned char filter_no, unsigned int sid, unsigned long eid)
{  
    unsigned short eidh, temp1, temp2;
    eidh = (unsigned short) (((eid & 0x30000) >> 16)| 0xFFE8);
    temp1 = sid & eidh;
    temp2 = (unsigned short)eid;         
    switch(filter_no)
    {
    case 0:
      C2RXF0SID = sid & eidh;
      C2RXF0EID = (unsigned short)eid;       
      break;
    case 1:
      C2RXF1SID = sid & eidh;
      C2RXF1EID = (unsigned short)eid;       
      break;

    case 2:
      C2RXF2SID = sid & eidh;
      C2RXF2EID = (unsigned short)eid;       
      break;

    case 3:
      C2RXF3SID = sid & eidh;
      C2RXF3EID = (unsigned short)eid;       
      break;

    case 4:
      C2RXF4SID = sid & eidh;
      C2RXF4EID = (unsigned short)eid;       
      break;

    case 5:
      C2RXF5SID = sid & eidh;
      C2RXF5EID = (unsigned short)eid;       
      break;

    case 6:
      C2RXF6SID = sid & eidh;
      C2RXF6EID = (unsigned short)eid;       
      break;

    case 7:
      C2RXF7SID = sid & eidh;
      C2RXF7EID = (unsigned short)eid;       
      break;

    case 8:
      C2RXF8SID = sid & eidh;
      C2RXF8EID = (unsigned short)eid;       
      break;

    case 9:
      C2RXF9SID = sid & eidh;
      C2RXF9EID = (unsigned short)eid;       
      break;

    case 10:
      C2RXF10SID = sid & eidh;
      C2RXF10EID = (unsigned short)eid;       
      break;

    case 11:
      C2RXF11SID = sid & eidh;
      C2RXF11EID = (unsigned short)eid;       
      break;

    case 12:
      C2RXF12SID = sid & eidh;
      C2RXF12EID = (unsigned short)eid;       
      break;

    case 13:
      C2RXF13SID = sid & eidh;
      C2RXF13EID = (unsigned short)eid;       
      break;

    case 14:
      C2RXF14SID = sid & eidh;
      C2RXF14EID = (unsigned short)eid;       
      break;

    case 15:
      C2RXF15SID = sid & eidh;
      C2RXF15EID = (unsigned short)eid;       
      break;

    default:
      C2RXF0SID = sid & eidh;
      C2RXF0EID = (unsigned short)eid;        
      break;
    }
}

#else
#warning "Does not build on this target"
#endif
