#include <reset.h>

/********************************************************************
* Function Name     : isWU
* Description       : Checks whether wake up from SLEEP 
*                     is due to MCLR or Interrupt or WDTO or BOR 
* Parameters        : None
* Return Value      : Returns 2 for MCLR, 1 for interrupt, 
*                     3 for WDTO,4 for BOR.
*                     Returns 0 if was not SLEEP
*********************************************************************/
#define MASK_SLEEP_BIT 0x0008
#define MASK_EXTR_BIT  0x0080
#define MASK_BOR_BIT   0x0002
#define MASK_WDTO_BIT  0x0010

char isWU(void)
{
   unsigned int tmp_rcon = RCON;
   char status = 0;
   if((tmp_rcon & MASK_SLEEP_BIT) == MASK_SLEEP_BIT )
   {
       /* clear sleep bit */
       RCONbits.SLEEP = 0;
       
       status = 1;             /* wakeup is due to interrupt. */       
       
       if((tmp_rcon & MASK_EXTR_BIT) == MASK_EXTR_BIT)
       {
           /* clear corresponding bit */
           RCONbits.EXTR = 0;
           
           status = 2;        /* wakeup is due to MCLR */
       }

       if((tmp_rcon & MASK_WDTO_BIT) == MASK_WDTO_BIT)
       {
		   /* clear corresponding bit */
		   RCONbits.WDTO = 0;
		   
		   status = 3;        /* wakeup is due to WDTO */
       } 

#ifdef _BOR
	   /* POR also generates BOR, make sure POR is cleared
	    immediately after POR event */
       if((tmp_rcon & MASK_BOR_BIT) == MASK_BOR_BIT)
       {   
           RCONbits.BOR = 0;
           
           status = 4; /* wakeup is due to BOR */
       }
#endif
   }
   return status;       
}
