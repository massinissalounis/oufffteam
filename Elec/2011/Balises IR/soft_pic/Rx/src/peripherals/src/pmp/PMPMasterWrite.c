#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)


/******************************************************************************
 * Function:        PMPMasterWrite
 *
 * PreCondition:    None
 *
 * Input:           value to write to external device
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        dsPIC33F: if 8-bit data mode is selected, the data appears on 8
 *	                data lines.  If 16-bit data mode, the lower 8 bits of data
 *			are written first, followed by the upper 8 bits of data.
 * 					
 * Note:			Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11 
 *****************************************************************************/
void PMPMasterWrite(WORD value)
{
	while(PMMODEbits.BUSY);
   	
	PMDIN1 = (WORD) value;
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
