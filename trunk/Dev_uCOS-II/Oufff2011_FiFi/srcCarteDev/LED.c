/*****************************************************************************
 *  Module for the LEDs of Sure Electronics Storage Project
 *****************************************************************************
 * FileName:        LED.c
 * Dependencies:    See the #include files below
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Sure Electronics
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vivian Zhao  		02/25/10	Original
 *****************************************************************************/
#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined (__PIC32MX__)
    #include <p32xxxx.h>
#else
    #error No processor header file.
#endif
#include "LED.h"
#include "main.h"

 //****************************************************************************
//*****************************************************************************
// Local Prototypes
//*****************************************************************************
//*****************************************************************************

 /****************************************************************************
  Function:
    void	LEDInit(void)

  Description:
    Initialize the LEDs

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
void LEDInit(void)
{
//Set LED Output
	TRIS_SD_LED = OUTPUT;
	TRIS_FLASH_LED = OUTPUT;
	TRIS_USB_LED = OUTPUT;
	TRIS_ERROR_LED = OUTPUT;	

//Turn off LED
	SD_LED = LED_TURN_OFF;
	FLASH_LED = LED_TURN_OFF;
	USB_LED = LED_TURN_OFF;
	ERROR_LED = LED_TURN_OFF;

	return;
}
