#include "pmp.h"

#if defined(_PPI_PMP_V1) || defined(_PPI_PMP_V2)

/******************************************************************************
 * Function:        PMPOpen
 *
 * PreCondition:    None
 *
 * Input:           control -- Control register settings
 *                  mode    -- Parallel port mode register setting
 *                  port    -- Parallel port enable register setting
 *                  addrs   -- Parrrel port address rgister content
 *                  interrupt -- intereupt setting for PMP
 *                              bit 0 -  bit 2 --> priority setting
 *                                       bit 3 --> Interrupt Enable/Disable
 *                              bit 4 -  bit 7 --> unsused
 *
 * Output:          None
 *
 * Side Effects:    Configures the PMP module as per the input data
 *
 * Overview:        Provides method for setting PMP registers using bit masks
 *                  provided in this header file.
 * Note:            
 *****************************************************************************/
void PMPOpen(UINT control, UINT mode, UINT port, UINT addrs, BYTE interrupt)
{
    PMSTAT = 0;
    IEC2bits.PMPIE = 0;
    IFS2bits.PMPIF = 0;
    IPC11bits.PMPIP = 0;
    PMCON = control;
    PMMODE = mode;
    PMAEN = port;
    PMADDR = addrs;
    
    IPC11bits.PMPIP = interrupt & 0x07;     // mask just the pmp priority bits  
    IEC2bits.PMPIE = (interrupt & 0x08)>>3;         // mask just the pmp interrupt enable bit
    PMCONbits.PMPEN = 1;        // last, enable the module
}



/* end of file */
#else
#warning "Does not build on this target"
#endif
