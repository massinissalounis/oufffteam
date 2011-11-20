#include <ecan.h>

#ifdef _C2TXIF

/*************************************************************************
* Function Name     : CAN2SetMask
* Description       : This function sets the values for the acceptance 
*                     filter mask registers (SID and EID)
* Parameters        : unsigned char: mask_no
*                     unsigned int: sid register value  
*                     unsigned long: eid registers value
* Return Value      : None 
**************************************************************************/

void CAN2SetMask(unsigned char mask_no, unsigned int sid, unsigned long eid)
{ 
    unsigned short eidh, temp1, temp2;
    eidh = (unsigned short) (((eid & 0x30000) >> 16)| 0xFFE8);
    temp1 = sid & eidh;
    temp2 = (unsigned short)eid;      
 
    switch(mask_no)
    {
        case 0:
              C2RXM0SID = sid & eidh;
              C2RXM0EID = (unsigned short)eid;         
              break;
        case 1:
              C2RXM1SID = sid & eidh;
              C2RXM1EID = (unsigned short)eid;         
              break;
        case 2:
              C2RXM2SID = sid & eidh;
              C2RXM2EID = (unsigned short)eid;         
              break;
        default:
              C2RXM0SID = sid & eidh;
              C2RXM0EID = (unsigned short)eid;         
              break;
    }
}

#else
#warning "Does not build on this target"
#endif
