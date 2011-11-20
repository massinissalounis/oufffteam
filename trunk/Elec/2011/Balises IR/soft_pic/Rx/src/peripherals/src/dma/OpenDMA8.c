#include "dma.h"

/*********************************************************************
* Function Name     : OpenDMA8
* Description       : Configures the DMA8. This includes :
                    · Data size			 // DMA8CON<14> SIZE bit
		    . Data transfer direction       // DMA8CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA8CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA8CON<11> NULLW bit
                    · DMA8 addressing mode select bit	//DMA8CON<5:4> AMODE<1:0> bits
                    . DMA8 operating mode select bit	//DMA8CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA8REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA8REQ<15> FORCE bit
		    . DMA8 start address for register A		//DMA8STA<7:0> STA<7:0> bits
		    . DMA8 start address for register B		//DMA8STB<7:0> STB<7:0> bits
		    . DMA8 peripheral address register		// DMA8PAD register
		    . DMA8 transfer count register		//DMA8CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if (defined (__dsPIC33E__) || defined (__PIC24E__)) && defined _DMA8IF

void OpenDMA8(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA8REQ = irq;

	/* set the start address for buffer A */
	DMA8STAL = sta_address & 0xFFFF;
	DMA8STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA8STBL = stb_address & 0xFFFF;
	DMA8STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA8PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA8CNT = count;
	
    /* configures the DMA8 CONTROL register */

    DMA8CON = config;
	/* enable the DMA8 */

	DMA8CONbits.CHEN = 1;


}
#else
#warning "Does not build on this target"
#endif
