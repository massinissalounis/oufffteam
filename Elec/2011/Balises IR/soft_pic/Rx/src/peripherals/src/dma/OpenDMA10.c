#include "dma.h"


/*********************************************************************
* Function Name     : OpenDMA10
* Description       : Configures the DMA10. This includes :
                    · Data size			 // DMA10CON<14> SIZE bit
		    . Data transfer direction       // DMA10CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA10CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA10CON<11> NULLW bit
                    · DMA10 addressing mode select bit	//DMA10CON<5:4> AMODE<1:0> bits
                    . DMA10 operating mode select bit	//DMA10CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA10REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA10REQ<15> FORCE bit
		    . DMA10 start address for register A		//DMA10STA<7:0> STA<7:0> bits
		    . DMA10 start address for register B		//DMA10STB<7:0> STB<7:0> bits
		    . DMA10 peripheral address register		// DMA10PAD register
		    . DMA10 transfer count register		//DMA10CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA10IF

void OpenDMA10(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA10REQ = irq;

	/* set the start address for buffer A */
	DMA10STAL = sta_address & 0xFFFF;
	DMA10STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA10STBL = stb_address & 0xFFFF;
	DMA10STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA10PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA10CNT = count;
	
    /* configures the DMA10 CONTROL register */

    DMA10CON = config;
	/* enable the DMA10 */

	DMA10CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
