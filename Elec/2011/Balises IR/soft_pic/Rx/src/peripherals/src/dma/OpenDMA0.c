#include "dma.h"

#ifdef _DMA0IF

/*********************************************************************
* Function Name     : OpenDMA0
* Description       : Configures the DMA0. This includes :
                    · Data size			 // DMA0CON<14> SIZE bit
		    . Data transfer direction       // DMA0CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA0CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA0CON<11> NULLW bit
                    · DMA0 addressing mode select bit	//DMA0CON<5:4> AMODE<1:0> bits
                    . DMA0 operating mode select bit	//DMA0CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA0REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA0REQ<15> FORCE bit
		    . DMA0 start address for register A		//DMA0STA<7:0> STA<7:0> bits
		    . DMA0 start address for register B		//DMA0STB<7:0> STB<7:0> bits
		    . DMA0 peripheral address register		// DMA0PAD register
		    . DMA0 transfer count register		//DMA0CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/

#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA0(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{


	/* Set the peripheral IRQ number*/
	DMA0REQ = irq;

	/* set the start address for buffer A */
	DMA0STAL = sta_address & 0xFFFF;
	DMA0STAH = sta_address >> 16;


	/* set the start address for buffer B */
	DMA0STBL = stb_address & 0xFFFF;
	DMA0STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA0PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA0CNT = count;
    
    /* configures the DMA0 CONTROL register */
    DMA0CON = config;
	
	/* enable the DMA0 */

	DMA0CONbits.CHEN = 1;


}
#else

void OpenDMA0(unsigned int config,unsigned int irq,unsigned int sta_address,
		unsigned int stb_address,unsigned int pad_adress,unsigned int count )
{
    


	/* Set the peripheral IRQ number*/
	DMA0REQ = irq;

	/* set the start address for buffer A */
	DMA0STA = sta_address;

	/* set the start address for buffer B */
	DMA0STB = stb_address;

	/* set the peripheral address*/
	DMA0PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA0CNT = count;
	
    /* configures the DMA0 CONTROL register */

    DMA0CON = config;
	/* enable the DMA0 */

	DMA0CONbits.CHEN = 1;

}

#endif

#else
#warning "Does not build on this target"
#endif
