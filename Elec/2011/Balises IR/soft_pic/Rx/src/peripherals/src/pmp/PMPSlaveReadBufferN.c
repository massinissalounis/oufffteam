#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPSlaveReadBufferN
 *
 * PreCondition:    None
 *
 * Input:           buffer(0..3)
 *
 * Output:          The value in selected buffer.
 *
 * Side Effects:    Reading PMDATA buffer clears status bit.
 *
 * Overview:        Reads the value in PMDATA register written by a master device.
 * 					
 * Note:            Use in SLAVE BUFFERED mode, MODE[1:0] = 00 and INCM[1:0]=11              
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01.
                    If MODE[1:0]=00 and INCM[1:0]?01,then buf-(0).
 *****************************************************************************/
unsigned char PMPSlaveReadBufferN(BUFFER buf)
{

	WORD_VAL reg1, reg2;
	BYTE value;

	reg2.Val = PMDIN2;					// copy contents of input buffers PMDIN2
	reg1.Val = PMDIN1;					// copy contents of input buffers PMDIN1
	
	switch(buf)
	{
	case 0:
		value =reg1.v[0];				// get copy of PMDIN1[7:0]
		break;
	case 1:
		value = reg1.v[1];				// get copy of PMDIN1[15:8]
		break;
	case 2:
		value = reg2.v[0];				// get copy of PMDIN2[7:0]
		break;
	case 3:	
		value = reg2.v[1];				// get copy of PMDIN2[15:8]
		break;
	}

	return(value);						// return to caller
}

/* end of file */
#else
#warning "Does not build on this target"
#endif
