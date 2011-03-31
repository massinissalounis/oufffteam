/*****************************************************************************
 *  Module for the buttons of Sure Electronics Storage Project
 *****************************************************************************
 * FileName:        Button.c
 * Dependencies:    See the #include files below
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Sure Electronics
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vivian Zhao  		12/08/09	Original
 *****************************************************************************/
#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined (__PIC32MX__)
    #include <p32xxxx.h>
#else
    #error No processor header file.
#endif
#include "Button.h"
#include "main.h"


//******************************************************************************
//******************************************************************************
// Data Structures
//******************************************************************************
//******************************************************************************

typedef union
{
    struct
    {
        unsigned    BTN_R:1;
        unsigned    BTN_L:1;
        unsigned    BTN_M:1;
    };
    WORD            val;
} MANUALBUTTONS;


 //****************************************************************************
//*****************************************************************************
// Variables
//*****************************************************************************
//*****************************************************************************
unsigned char	buttonIndex;	// Index of what TOUCHPAD is being checked.
MANUALBUTTONS	buttons;
MANUALBUTTONS	buttonsPrevious;

//*****************************************************************************
//*****************************************************************************
// Constants and Enumerations
//*****************************************************************************
//*****************************************************************************
typedef enum {
    Button_R = 0,
    Button_L,
    Button_M,
	Button_NONE
} Button;

 //****************************************************************************
//*****************************************************************************
// Local Prototypes
//*****************************************************************************
//*****************************************************************************

 /****************************************************************************
  Function:
    void	ButtonInit(void)

  Description:
    Initialize the Buttons to choose the functions.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
void	ButtonInit(void)
{
//Set PORTB Input
	TRIS_R_BUTTON = 1;
	TRIS_L_BUTTON = 1;
	TRIS_M_BUTTON = 1;

// Set up the ADC	
	AD1PCFG	= 0xFFFF;	//change AN2\AN3\AN4 to digital

	return;
}

 /****************************************************************************
  Function:
    void ReadButton( void )

  Description:
    It takes the measurement; determines if the button under test is pressed or not,
    setting a flag accordingly; and averages the new reading appropriately.
    This is done for all buttons sequentially.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
  ***************************************************************************/
void ReadButton()
{ 
	if(PORTBbits.RB4 == 1)	//Right Button
	{
		buttons.BTN_R  = 0;	
	}
	else
	{
		buttons.BTN_R  = 1;	//Low Voltage, the button is pressed
	}

	if(PORTBbits.RB3 == 1)	//Left Button
	{
		buttons.BTN_L  = 0;
	}
	else
	{
		buttons.BTN_L  = 1;
	}

	if(PORTBbits.RB2 == 1)	//Middle Button
	{
        buttons.BTN_M  = 0;	
	}
	else
	{
        buttons.BTN_M  = 1;	
	}
	return;
}
 
/****************************************************************************
  Function:
    void ButtonsMsg()

  Description:
    This routine creates approprite messages for button presses & releases.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  ***************************************************************************/

void ButtonsMsg()
{
	if (buttons.BTN_R != buttonsPrevious.BTN_R)
	{
		if (buttons.BTN_R)
		{
			buttonPress = 1;
		}
		buttonsPrevious.BTN_R = buttons.BTN_R;
        return;
    }
	if (buttons.BTN_L != buttonsPrevious.BTN_L)
	{
		if (buttons.BTN_L)
		{
			buttonPress = 2;
		}
		buttonsPrevious.BTN_L = buttons.BTN_L;
        return;
    }
	if (buttons.BTN_M != buttonsPrevious.BTN_M)
	{
		if (buttons.BTN_M)
		{
			buttonPress = 3;
		}
		buttonsPrevious.BTN_M = buttons.BTN_M;
        return;
    }
	buttonPress = 0;
	return;
}

