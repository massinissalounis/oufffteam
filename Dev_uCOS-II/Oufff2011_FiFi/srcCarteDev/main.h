/******************************************************************************

main.h

This is the main header file for the PIC24F Storage.  It gathers all the
necessary include files used by the various files of the demo project.  It also
defines constants and data types that are used by multiple files.

******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <plib.h>
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "LED.h"
#include "uart2.h"
#include "FSIO.h"
#include "usb.h"
#include "usb_host_msd.h"
#include "usb_host_msd_scsi.h"
#include "Compiler.h"
#include "usb_config.h"
#include "usb_device.h"
#include "SD-SPI.h"	
#include "usb_host.h"
#include "Internal Flash.h"
#include "usb_function_msd.h"

//*****************************************************************************
//*****************************************************************************
// Constants and Enumerations
//*****************************************************************************
//*****************************************************************************
typedef enum
{
    SCREEN_MAIN = 0          		    ,
    SCREEN_MENU_SD_CARD                 ,
	SCREEN_MENU_INTERNAL_FLASH               ,
    SCREEN_MENU_SD_TO_UART              ,
    SCREEN_MENU_USB_TO_UART             ,
    SCREEN_SD_CARD_INFORMATION          ,
    SCREEN_SPI_INFORMATION              ,
    SCREEN_SD_UART_INFORMATION          ,
    SCREEN_USB_INFORMATION
} SCREEN_STATES;

//*****************************************************************************
//*****************************************************************************
// Frequently Used Global Variables
//*****************************************************************************
//*****************************************************************************
extern  int buttonPress;
