#if defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#elif defined(__PIC24H__)
#include <p24Hxxxx.h>
#endif

#include "crc.h"

#ifdef _CRC_PROG_V1

#define WRITE_CRC_DATA_WORD(data)         (CRCDAT= data)
#define WRITE_CRC_DATA_BYTE(data)         (*(UINT8*)&CRCDAT = data)

#define GET_CRC_RESULT()                  (CRCWDAT)
#define SET_CRC_RESULT(data)              (CRCWDAT = data)


/******************************************************************************
 * Function:        UINT16 CRC_Calc_ChecksumWord(UINT16* data, UINT16 Number_of_words,
 *                                       UINT16 prev_CRC)
 *
 * PreCondition:    CRC Module must be configured   
 *
 * Input:           data - Pointer to the first data word for which CRC needs to be 
 *                         calculated.
 *                  Number_of_words - Total number of words for which CRC needs to be 
 *                         calculated.
 *                  prev_CRC - previous CRC result. Note*
 *                  
 * Output:          Returns Two Byte CRC checksum based on the set polynomial
 *
 * Side Effects:    None
 *
 * Overview:        This function calculates CRC checksum for the data provide by the user,
 *                  based on the polynomial set in the CRCXOR Register.
 *
 * Note:            This input parameter is provided as a provision to allow continuation
 *                  of previously computed checksum. In case the checksum is being calculated
 *                  for a fresh set of data then the input value for prev_CRC should be '0'.
 *****************************************************************************/

UINT16 CRC_Calc_ChecksumWord(UINT16* data, UINT16 Number_of_words, UINT16 prev_CRC)
{
   SET_CRC_RESULT(prev_CRC);
   Start_CRC_Calculation();
   do
   {
       while(1 != Get_CRC_FIFO_EMPTY_STATUS());
      
       while((0 == Get_CRC_FIFO_FULL_STATUS() && (0 < Number_of_words)))
       {
          WRITE_CRC_DATA_WORD(*data);
          data++;
          Number_of_words--;
       }
    }while (0 < Number_of_words);

   while(CRCCONbits.CRCFUL==1);	
   CRCDAT = 0x0000;	/* Do this to shift the last word out of the 	*/
			/* CRC shift register		        	*/

   while(1 != Get_CRC_FIFO_EMPTY_STATUS());
   Stop_CRC_Calculation();
   Nop(); 
   return(GET_CRC_RESULT());
}



/******************************************************************************
 * Function:        UINT16 CRC_Calc_ChecksumByte(UINT8* data, UINT16 Number_of_bytes,
 *                                       UINT16 prev_CRC)
 *
 * PreCondition:    CRC Module must be configured   
 *
 * Input:           data - Pointer to the first byte word for which CRC needs  
 *                         to be calculated.
 *                  Number_of_bytes - Total number of bytes for which CRC needs 
 *                         to be calculated.
 *                  prev_CRC - previous CRC result. Note*
 *                  
 * Output:          Returns One Byte CRC checksum based on the set polynomial
 *
 * Side Effects:    None
 *
 * Overview:        This function calculates CRC checksum for the data provide by ,
 *                  the user based on the polynomil set in the CRCXOR Register.
 *
 * Note:            This input parameter is provided as a provision to allow continuation
 *                  of previously computed checksum. In case the checksum is being calculated
 *                  for a fresh set of data then the input value for prev_CRC should be '0'.
 *****************************************************************************/

UINT16 CRC_Calc_ChecksumByte(UINT8* data, UINT16 Number_of_bytes, UINT16 prev_CRC)
{
   SET_CRC_RESULT(prev_CRC);
   Start_CRC_Calculation();
   do
   {
       while(1 != Get_CRC_FIFO_EMPTY_STATUS());
       
       while((0 == Get_CRC_FIFO_FULL_STATUS() && (0 < Number_of_bytes)))
       {
          WRITE_CRC_DATA_BYTE(*data);
          data++;
          Number_of_bytes--;
       }
   }while (0 < Number_of_bytes);

    while(CRCCONbits.CRCFUL==1);
    CRCDAT = 0x0000;	/* Do this to shift the last word out of the 	*/
			/* CRC shift register			        */

   while(1 != Get_CRC_FIFO_EMPTY_STATUS());
   Stop_CRC_Calculation();     
   Nop();
   return(GET_CRC_RESULT());
}

#else
#warning "Does not build on this target"
#endif
