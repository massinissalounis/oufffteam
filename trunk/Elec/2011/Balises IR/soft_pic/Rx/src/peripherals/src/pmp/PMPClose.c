#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPClose
 *
 * PreCondition:    None
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:	PMCON.PMPEN, IEC2.PMPIE, IFS2.PMPIF are cleared.
 *
 * Overview:    	disables PMP module, disables interrupt
 * 					
 * Note:            
 *****************************************************************************/
 void PMPClose(void)
 {
	IEC2bits.PMPIE = 0;
	PMCONbits.PMPEN = 0;
	IFS2bits.PMPIF = 0;
 }

/* end of file */
#else
#warning "Does not build on this target"
#endif
