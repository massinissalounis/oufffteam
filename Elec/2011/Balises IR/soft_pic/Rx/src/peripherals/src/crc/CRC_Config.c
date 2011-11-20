#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif

#include "crc.h"

#ifdef _CRC_PROG_V1

/******************************************************************************
 * Function:        void CRC_Config(UINT16 poly , UINT16 config)
 *
 * PreCondition:    None   
 *
 * Input:           poly - Polynomial to calculate CRC
 *                  config - CRC Control reg value
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function configures CRC module
 *
 * Note:            None
 *****************************************************************************/

void CRC_Config(UINT16 poly , UINT16 config)
{
   CRCXOR = poly;
   CRCCON = config;
}

#else
#warning "Does not build on this target"
#endif
