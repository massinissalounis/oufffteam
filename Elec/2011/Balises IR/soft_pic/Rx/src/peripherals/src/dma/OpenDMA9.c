#include "dma.h"


/*********************************************************************
* Function Name     : OpenDMA9
* Description       : Configures the DMA9. This includes :
                    · Data size			 // DMA9CON<14> SIZE bit
		    . Data transfer direction       // DMA9CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA9CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA9CON<11> NULLW bit
                    · DMA9 addressing mode select bit	//DMA9CON<5:4> AMODE<1:0> bits
                    . DMA9 operating mode select bit	//DMA9CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA9REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA9REQ<15> FORCE bit
		    . DMA9 start address for register A		//DMA9STA<7:0> STA<7:0> bits
		    . DMA9 start address for register B		//DMA9STB<7:0> STB<7:0> bits
		    . DMA9 peripheral address register		// DMA9PAD register
		    . DMA9 transfer count register		//DMA9CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA9IF

void OpenDMA9(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA9REQ = irq;

	/* set the start address for buffer A */
	DMA9STAL = sta_address & 0xFFFF;
	DMA9STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA9STBL = stb_address & 0xFFFF;
	DMA9STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA9PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA9CNT = count;
	
    /* configures the DMA9 CONTROL register */

    DMA9CON = config;
	/* enable the DMA9 */

	DMA9CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
