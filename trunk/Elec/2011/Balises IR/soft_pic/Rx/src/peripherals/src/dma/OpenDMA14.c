#include "dma.h"


/*********************************************************************
* Function Name     : OpenDMA14
* Description       : Configures the DMA14. This includes :
                    · Data size			 // DMA14CON<14> SIZE bit
		    . Data transfer direction       // DMA14CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA14CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA14CON<11> NULLW bit
                    · DMA14 addressing mode select bit	//DMA14CON<5:4> AMODE<1:0> bits
                    . DMA14 operating mode select bit	//DMA14CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA14REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA14REQ<15> FORCE bit
		    . DMA14 start address for register A		//DMA14STA<7:0> STA<7:0> bits
		    . DMA14 start address for register B		//DMA14STB<7:0> STB<7:0> bits
		    . DMA14 peripheral address register		// DMA14PAD register
		    . DMA14 transfer count register		//DMA14CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA14IF

void OpenDMA14(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA14REQ = irq;

	/* set the start address for buffer A */
	DMA14STAL = sta_address & 0xFFFF;
	DMA14STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA14STBL = stb_address & 0xFFFF;
	DMA14STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA14PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA14CNT = count;
	
    /* configures the DMA14 CONTROL register */

    DMA14CON = config;
	/* enable the DMA14 */

	DMA14CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
