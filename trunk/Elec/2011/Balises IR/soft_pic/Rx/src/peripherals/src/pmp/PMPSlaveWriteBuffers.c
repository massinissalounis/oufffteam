#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPSlaveWriteBuffers
 *
 * PreCondition:    None
 *
 * Input:           BYTE pointer
 *
 * Output:          Returns the state of PMSTAT.OBE prior to the write operation.
 *
 * Side Effects:    None
 *
 * Overview:        Copies 4 bytes, addressed by the pointer/ref argument, into
 *			the corresponding output registers. Byte[0] -> OUT1[7:0],
 *			byte[1] -> OUT1[15:8], ... etc. If entire buffer is empty,
 *			(IBF = 0) function returns TRUE, else the bytes are not
 *			copied and returns FALSE.
 * 					
 * Note:            Use in SLAVE BUFFERED mode, MODE[1:0] = 00
 *			or SLAVE ENHANCED mode, MODE[1:0] = 01  and INCM[1:0]=11              
 *****************************************************************************/
BOOL PMPSlaveWriteBuffers(BYTE* ref)
{
	WORD_VAL reg1, reg2;
	BOOL status;
	
	if(PMSTATbits.OBE)
		status = TRUE;

	reg1.v[0] = *ref++;
	reg1.v[1] = *ref++;
	reg2.v[0] = *ref++;
	reg2.v[1] = *ref;

	PMDOUT1 = reg1.Val;
	PMDOUT2 = reg2.Val;
	
	return(status);
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
