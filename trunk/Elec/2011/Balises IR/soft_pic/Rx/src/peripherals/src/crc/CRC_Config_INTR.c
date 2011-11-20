#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif
#include "crc.h"

#ifdef _CRC_PROG_V1

/******************************************************************************
 * Function:        void CRC_Config_INTR(UINT8 intr_byte)
 *
 * PreCondition:    None   
 *
 * Input:           intr_byte - Interrupt priority/State
 *                              bit 0 -  bit 2 --> priority setting
 *                                       bit 3 --> Interrupt Enable/Disable
 *                              bit 4 -  bit 7 --> unsused
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function configures interrupts of CRC module
 *
 * Note:            None
 *****************************************************************************/

void CRC_Config_INTR(UINT8 intr_byte)
{
   IFS4bits.CRCIF = 0;                       /* clear the CRC Interrupts */

   IPC16bits.CRCIP = (intr_byte & 0x07);
   IEC4bits.CRCIE = (intr_byte & 0x08)>>3;
}

#else
#warning "Does not build on this target"
#endif
