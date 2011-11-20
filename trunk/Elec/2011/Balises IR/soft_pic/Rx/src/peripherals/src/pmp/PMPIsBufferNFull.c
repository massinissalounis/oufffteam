#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPIsInputBufferNFull
 *
 * PreCondition:    None
 *
 * Input:           buffer(0..3)
 *
 * Output:          TRUE/FALSE
 *
 * Side Effects:    None
 *
 * Overview:        Returns state of PMSTAT.IBxF (input buffer(s) full bit)
 * 					
 * Note:            Use in SLAVE BUFFERED mode, MODE[1:0] = 00
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01  and INCM[1:0]=11
 *****************************************************************************/
BOOL PMPIsBufferNFull(BUFFER buf)
{
	BOOL status = FALSE;
	
	switch(buf)
	{
	case 0:
		status = PMSTATbits.IB0F;
		break;
	case 1:
		status = PMSTATbits.IB1F;
		break;
	case 2:
		status = PMSTATbits.IB2F;
		break;
	case 3:
		status = PMSTATbits.IB3F;
		break;	
	}	
	return(status);
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
