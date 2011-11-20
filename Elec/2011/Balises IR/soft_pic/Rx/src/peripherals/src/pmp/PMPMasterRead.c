#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)


/******************************************************************************
 * Function:        PMPMasterRead
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          8-bit value read from external device
 *
 * Side Effects:    None
 *
 * Overview:        
 * 					
 * Note:	    Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11 
 *****************************************************************************/
WORD PMPMasterRead(void)
{
	//while(!PMMODEbits.BUSY) {} ??????????????????????????
	while(PMMODEbits.BUSY);
	return(PMDIN1);
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
