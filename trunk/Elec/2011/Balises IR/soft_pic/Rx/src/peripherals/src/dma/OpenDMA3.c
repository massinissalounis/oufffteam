#include "dma.h"

#ifdef _DMA3IF

/*********************************************************************
* Function Name     : OpenDMA3
* Description       : Configures the DMA3. This includes :
                    · Data size			 // DMA3CON<14> SIZE bit
		    . Data transfer direction       // DMA3CON<13> DIR bit
                    · Transfer complete interrupt select	//DMA3CON<12> HALF bit
                    · Null data peripheral write mode select bit  // DMA3CON<11> NULLW bit
                    · DMA3 addressing mode select bit	//DMA3CON<5:4> AMODE<1:0> bits
                    . DMA3 operating mode select bit	//DMA3CON<1:0> MODE<1:0> bits 
                    . Peripheral IRQ select			//DMA3REQ<6:0> IRQSEL<6:0> bits
		    . Force a manual transfer			//DMA3REQ<15> FORCE bit
		    . DMA3 start address for register A		//DMA3STA<7:0> STA<7:0> bits
		    . DMA3 start address for register B		//DMA3STB<7:0> STB<7:0> bits
		    . DMA3 peripheral address register		// DMA3PAD register
		    . DMA3 transfer count register		//DMA3CNT
* Parameters        : config,irq,sta_address, stb_address, pad_adress, count 
* Return Value      : None
*********************************************************************/
#if defined (__dsPIC33E__) || defined (__PIC24E__)

void OpenDMA3(unsigned int config,unsigned int irq,unsigned long int sta_address, 
        unsigned long int stb_address,unsigned int pad_adress,unsigned int count ) 
{

	/* Set the peripheral IRQ number*/
	DMA3REQ = irq;

	/* set the start address for buffer A */
	DMA3STAL = sta_address & 0xFFFF;
	DMA3STAH = sta_address >> 16;

	/* set the start address for buffer B */
	DMA3STBL = stb_address & 0xFFFF;
	DMA3STBH = stb_address >> 16;

	/* set the peripheral address*/
	DMA3PAD = pad_adress;

	/* set the number of bytes/words to be tranfered*/
	DMA3CNT = count;
	
    /* configures the DMA3 CONTROL register */

    DMA3CON = config;
	/* enable the DMA3 */

	DMA3CONbits.CHEN = 1;


}
#else

void OpenDMA3(unsigned int config, unsigned int irq, unsigned int sta_address,
              unsigned int stb_address, unsigned int pad_address,
              unsigned int count )
{


    /* Set the peripheral IRQ number*/
    DMA3REQ = irq;

    /* set the start address for buffer A */
    DMA3STA = sta_address;

    /* set the start address for buffer B */
    DMA3STB = stb_address;

    /* set the peripheral address*/
    DMA3PAD = pad_address;

    /* set the number of bytes/words to be tranfered*/
    DMA3CNT = count;
	
    /* configures the DMA3 CONTROL register */
    DMA3CON = config;
    /* enable the DMA3 */
    DMA3CONbits.CHEN = 1;
}
#endif
#else
#warning "Does not build on this target"
#endif
