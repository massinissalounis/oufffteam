#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPIsBufferNEmpty
 *
 * PreCondition:    None
 *
 * Input:           buffer(0..3)
 *
 * Output:          TRUE/FALSE
 *
 * Side Effects:    None
 *
 * Overview:        Returns state of PMSTAT.OBnE (output buffer(s) empty bit)
 * 					
 * Note:            Use in SLAVE BUFFERED mode, MODE[1:0] = 00
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01  and INCM[1:0]=11            
 *****************************************************************************/
BOOL PMPIsBufferNEmpty(BUFFER buf)
{
	BOOL status = FALSE;
	
	switch(buf)
	{
	case 0:
		status = PMSTATbits.OB0E;
	break;
	case 1:
		status = PMSTATbits.OB1E;
	break;
	case 2:
		status = PMSTATbits.OB2E;
	break;
	case 3:
		status = PMSTATbits.OB3E;
	break;	
	}	
	return(status);
}


/* end of file */
#else
#warning "Does not build on this target"
#endif
