#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPSetAddress
 *
 * PreCondition:    None
 *
 * Input:           16-bit value to be written to external device
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        
 * 					
 * Note:	    Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11 
 *****************************************************************************/
void PMPSetAddress(WORD address)
{
#ifdef _PPI_PMP_V2
	static const unsigned int addrsMask[]={0x0000FFFF, 0x0000BFFF, 0x00003FFF};
	if(PMCONbits.CSF == 2)
		address = address & addrsMask[2];	
	else if(PMCONbits.CSF == 1)
		address = address & addrsMask[1];	
	else
		address = address & addrsMask[0];	
	PMADDR = (PMADDR & BIT_CS1_ON & BIT_CS2_ON) + address;
#else
	static const unsigned int addrsMask[]={0x0000FFFF, 0x0000BFFF};
	unsigned int cs;
	
	cs =  (PMADDR & BIT_CS1_ON) >> 14;
	address = address & addrsMask[cs];	
	PMADDR = (PMADDR & BIT_CS1_ON) + address;
#endif
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
