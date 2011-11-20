#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPSlaveWriteBufferN
 *
 * PreCondition:    None
 *
 * Input:           buffer(0..3), value to be written
 *
 * Output:          Returns the state of PMSTAT.OBE prior to the write operation.
 *
 * Side Effects:    None
 *
 * Overview:        writes the desired value into the selected output buffer
 * 					
 * Note:            Use in SLAVE BUFFERED mode, MODE[1:0] = 00
 *			or SLAVE ENHANCED mode, MODE[1:0] = 01  and INCM[1:0]=11.
                    If MODE[1:0]=00 and INCM[1:0]?01,then buf-(0).           
 *****************************************************************************/
BOOL PMPSlaveWriteBufferN(BUFFER buf, BYTE value)
{

	WORD_VAL reg;
	BOOL status;
	reg.Val = 0;
	
	if(PMSTATbits.OBE)	
		status = TRUE;

	switch(buf)
	{
	case 0:
		reg.Val = PMADDR;				// copy upper/lower bytes of PMDATAOUT1 into temp
		reg.v[0] = value;				// update lower byte only
		PMADDR = reg.Val;				// write it back to PMDATAOUT1
		break;

	case 1:
		reg.Val = PMADDR;				// copy upper/lower bytes of PMDATAOUT1 into temp
		reg.v[1] = value;				// update upper byte only
		PMADDR = reg.Val;				// write it back to PMDATAOUT1
		break;

	case 2:
		reg.Val = PMDOUT2;				// copy upper/lower bytes of PMDATAOUT2 into temp
		reg.v[0] = value;					// update lower byte only
		PMDOUT2 = reg.Val;				// write it back to PMDATAOUT2
		break;
		
	case 3:
		reg.Val = PMDOUT2;				// copy upper/lower bytes of PMDATAOUT2 into temp
		reg.v[1] = value;					// update upper byte only
		PMDOUT2 = reg.Val;				// write it back to PMDATAOUT2
		break;
	}
	return(status);
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
