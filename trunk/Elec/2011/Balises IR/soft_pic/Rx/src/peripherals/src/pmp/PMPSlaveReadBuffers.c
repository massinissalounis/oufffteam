#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPSlaveReadBuffers
 *
 * PreCondition:    None
 *
 * Input:           BYTE pointer
 *
 * Output:          The contents of the 4 8-bit slave buffer registers.
 *
 * Side Effects:    Reading any of these buffers clears the IBF status bit as
 *					well as the individual IBnF status bits.
 *
 * Overview:        Copies 4 bytes from DATAIN buffers to a starting location
 *					pointed to by input parameter.
 * 					
 * Note:            Use in SLAVE BUFFERED mode, MODE[1:0] = 00 and INCM[1:0]=11              
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01
 *****************************************************************************/
void PMPSlaveReadBuffers(BYTE* ref)
{
	WORD_VAL reg1, reg2;
	
	reg1.Val = PMDIN1;					// copy contents of input buffers PMDIN1
	reg2.Val = PMDIN2;					// copy contents of input buffers PMDIN2		
	*ref++ = reg1.v[0];
	*ref++ = reg1.v[1];
	*ref++ = reg2.v[0];
	*ref   = reg2.v[1];

}

/* end of file */
#else
#warning "Does not build on this target"
#endif
