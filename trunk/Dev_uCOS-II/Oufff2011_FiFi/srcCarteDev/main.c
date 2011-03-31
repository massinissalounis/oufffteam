/******************************************************************************
   
PIC32MX440F512H Storage Demo

  Author          Date         Comments
--------------------------------------------------------------------------------
* Vivian          03/12/10  Version1.0

*******************************************************************************/
//DOM-IGNORE-END
#include "main.h"

// *****************************************************************************
// *****************************************************************************
// Constants
// *****************************************************************************
// *****************************************************************************

#if defined( __C30__)
    #define ADC_READING_POTENTIOMETER       ADC1BUF1
    #define ADC_READING_TEMPERATURE         ADC1BUF0
    #define ADC_READING_VBUS                ADC1BUF2
    #define SCAN_MASK                   0x0130      // Mask for AN4, AN5, and AN8
#elif defined( __PIC32MX__ )
    #define ADC_READING_POTENTIOMETER   ADC1BUF0
    #define ADC_READING_TEMPERATURE     ADC1BUF1
    #define ADC_READING_VBUS            ADC1BUF2
    #define SCAN_MASK               0x0114      // Mask for AN2, AN5 and AN8
#else
    #error Unsupported Processor
#endif
#define COPY_BUFFER_SIZE                512         // Increase to improve copy efficiency
#define MAX_ALLOWED_CURRENT             500         // Maximum power we can supply in mA
#define MAX_BUFFERED_COMMANDS           8           // Must be a power of 2
#define MAX_COMMAND_LENGTH              50
#define MAX_LOG_BUFFER_SIZE             512
#define NUM_LOG_BUFFERS                 2
#define VERSION                         "v1.0"

#if defined (__PIC32MX__ )
    #define PIC32MX_TIMER2_INTERRUPT    0x00000100
    #define PIC32MX_TIMER3_INTERRUPT    0x00001000
    #define PIC32MX_TIMER4_INTERRUPT    0x00010000
    
    #define DEFAULT_DATE                0x10040104	//20YY-MM-DD-WW
    #define DEFAULT_TIME                0x10100000 	//HH-MM-SS

    #define INDEX_HOURS                 3
    #define INDEX_MINUTES               2
    #define INDEX_SECONDS               1
    #define INDEX_YEAR                  3
    #define INDEX_MONTH                 2
    #define INDEX_DAY                   1
#endif
// RTCC Format Correlation Constants
// The 16-bit and 32-bit architectures use two different formats for the RTCC.
// These constants can be used to access the byte in a four-byte date or time
// array.  Note: No constant is given for the weekday, because the weekday is
// stored in a different byte.  This is done to flag the user to take special
// care when writing code that utilizes the weekday.

#if defined( __C30__ )
    #define INDEX_HOURS                 2
    #define INDEX_MINUTES               1
    #define INDEX_SECONDS               0
    #define INDEX_YEAR                  2
    #define INDEX_MONTH                 1
    #define INDEX_DAY                   0
#elif defined (__PIC32MX__ )
    #define INDEX_HOURS                 3
    #define INDEX_MINUTES               2
    #define INDEX_SECONDS               1
    #define INDEX_YEAR                  3
    #define INDEX_MONTH                 2
    #define INDEX_DAY                   1
#else
    #error Cannot set up RTCC constants
#endif

// We are taking Timer 3 for an acquisition timer.

// NOTE - The datasheet doesn't state this, but the timer does get reset to 0
// after a period register match.  So we don't have to worry about resetting
// the timer manually.

#define STOP_TIMER_IN_IDLE_MODE         0x2000
#define TIMER_SOURCE_INTERNAL           0x0000
#define TIMER_ON                        0x8000
#define GATED_TIME_DISABLED             0x0000
#define TIMER_16BIT_MODE                0x0000

#if defined( __C30__ )
    #define TIMER_PRESCALER_1               0x0000
    #define TIMER_PRESCALER_8               0x0010
    #define TIMER_PRESCALER_64              0x0020
    #define TIMER_PRESCALER_256             0x0030
    #define TIMER_INTERRUPT_PRIORITY        0x0002
#elif defined( __PIC32MX__ )
    #define TIMER_PRESCALER_1               0x0000
    #define TIMER_PRESCALER_2               0x0010
    #define TIMER_PRESCALER_4               0x0020
    #define TIMER_PRESCALER_8               0x0030
    #define TIMER_PRESCALER_16              0x0040
    #define TIMER_PRESCALER_32              0x0050
    #define TIMER_PRESCALER_64              0x0060
    #define TIMER_PRESCALER_256             0x0070
#else
    #error No timer constants
#endif

// *****************************************************************************
// *****************************************************************************
// Data Structures
// *****************************************************************************
// *****************************************************************************

typedef struct _COMMAND
{
    char        buffer[MAX_COMMAND_LENGTH];
    BYTE        index;
    BYTE        command;
    BYTE        escFirstChar;
    struct
    {
        BYTE    reading             : 1;
        BYTE    escNeedFirstChar    : 1;
        BYTE    escNeedSecondChar   : 1;
    };
} COMMAND;


typedef enum _COMMANDS
{
    COMMAND_NO_COMMAND,
    COMMAND_ATTRIB,
    COMMAND_CD,
    COMMAND_COPY,
    COMMAND_DATE,
    COMMAND_DEL,
    COMMAND_DIR,
    COMMAND_HELP,
    COMMAND_MD,
    COMMAND_RD,
    COMMAND_REN,
    COMMAND_TIME,
    COMMAND_TYPE,
    COMMAND_UNKNOWN
} COMMANDS;


typedef struct _LOG_DATA
{
    BYTE        buffer[MAX_LOG_BUFFER_SIZE];
    WORD        index;
    BOOL        bufferFull;
} LOG_DATA;


typedef struct _LOGGER_STATUS
{
    #if defined( __PIC32MX__ )
        // PIC32 does not have atomic bit-field set/clear instructions, so 
        // flags that are modified in both an ISR and main-line code must be
        // separate variables or we risk inadvertantly changing other flags
        // in the same byte.
        BOOL                mediaPresent;
        union
        {
            BYTE    value;
            struct
            {
                BYTE        readingPotentiometer    : 1;
                BYTE        readingTemperature      : 1;
            };
        };
    #else
    union
    {
        BYTE    value;
        struct
        {
            BYTE        mediaPresent            : 1;
            BYTE        readingPotentiometer    : 1;
            BYTE        readingTemperature      : 1;
        };
    };
    #endif
} LOGGER_STATUS;


typedef struct _OLD_COMMANDS
{
    char        lines[MAX_BUFFERED_COMMANDS][MAX_COMMAND_LENGTH];
    BYTE        oldest;
    BYTE        newest;
    BYTE        showing;
} OLD_COMMANDS;


#if defined( __C30__ )

    // PIC24 RTCC Structure
    typedef union
    {
        struct
        {
            unsigned char   mday;       // BCD codification for day of the month, 01-31
            unsigned char   mon;        // BCD codification for month, 01-12
            unsigned char   year;       // BCD codification for years, 00-99
            unsigned char   reserved;   // reserved for future use. should be 0
        };                              // field access
        unsigned char       b[4];       // byte access
        unsigned short      w[2];       // 16 bits access
        unsigned long       l;          // 32 bits access
    } PIC24_RTCC_DATE;

    // PIC24 RTCC Structure
    typedef union
    {
        struct
        {
            unsigned char   sec;        // BCD codification for seconds, 00-59
            unsigned char   min;        // BCD codification for minutes, 00-59
            unsigned char   hour;       // BCD codification for hours, 00-24
            unsigned char   weekday;    // BCD codification for day of the week, 00-06
        };                              // field access
        unsigned char       b[4];       // byte access
        unsigned short      w[2];       // 16 bits access
        unsigned long       l;          // 32 bits access
    } PIC24_RTCC_TIME;

#endif


typedef struct _VOLUME_INFO
{
    char        label[12];
    BYTE        valid;
} VOLUME_INFO;

#pragma udata

#if defined(__C30__) || defined(__C32__)  
	#if defined(USE_INTERNAL_FLASH)
	LUN_FUNCTIONS LUN[MAX_LUN + 1] = 
	{
	    {
	        &MDD_IntFlash_MediaInitialize,
	        &MDD_IntFlash_ReadCapacity,
	        &MDD_IntFlash_ReadSectorSize,
	        &MDD_IntFlash_MediaDetect,
	        &MDD_IntFlash_SectorRead,
	        &MDD_IntFlash_WriteProtectState,
	        &MDD_IntFlash_SectorWrite
	    }
	};

	#else
	LUN_FUNCTIONS LUN[MAX_LUN + 1] = 
	{
	    {
	        &MDD_SDSPI_MediaInitialize,
	        &MDD_SDSPI_ReadCapacity,
	        &MDD_SDSPI_ReadSectorSize,
	        &MDD_SDSPI_MediaDetect,
	        &MDD_SDSPI_SectorRead,
	        &MDD_SDSPI_WriteProtectState,
	        &MDD_SDSPI_SectorWrite
	    }
	};
	#endif

#endif

/* Standard Response to INQUIRY command stored in ROM 	*/
#if defined(USE_INTERNAL_FLASH)
const ROM InquiryResponse inq_resp = {
	0x00,		// peripheral device is connected, direct access block device
	0x80,           // removable
	0x04,	 	// version = 00=> does not conform to any standard, 4=> SPC-2
	0x02,		// response is in format specified by SPC-2
	0x20,		// n-4 = 36-4=32= 0x20
	0x00,		// sccs etc.
	0x00,		// bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
			// but as in case of other device, we are just using 00
	0x00,		// 00 obsolete, 0x80 for basic task queueing
	{//'M','i','c','r','o','c','h','p'
	   'S','r','u','e',' ',' ',' ',' '
    },
	// this is the T10 assigned Vendor ID
	{'I','n',' ',' ','F','l','a','s','h'
    },
	{'0','0','0','1'
    }
};
#else
const ROM InquiryResponse inq_resp = {
	0x00,		// peripheral device is connected, direct access block device
	0x80,           // removable
	0x04,	 	// version = 00=> does not conform to any standard, 4=> SPC-2
	0x02,		// response is in format specified by SPC-2
	0x20,		// n-4 = 36-4=32= 0x20
	0x00,		// sccs etc.
	0x00,		// bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
			// but as in case of other device, we are just using 00
	0x00,		// 00 obsolete, 0x80 for basic task queueing
	{//'M','i','c','r','o','c','h','p'
	'S','D',' ','C','a','r','d',' '
    },
	// this is the T10 assigned Vendor ID
	{'M','a','s','s',' ','S','t','o','r','a','g','e',' ',' ',' ',' '
    },
	{'0','0','0','1'
    }
};
#endif

FS_DISK_PROPERTIES disk_properties;

// *****************************************************************************
// *****************************************************************************
// Internal Function Prototypes
// *****************************************************************************
// *****************************************************************************

BYTE    GetCommand( void );
DWORD   GetCurrentTick( void );
void    GetOneWord( char *buffer );
DWORD   GetUserDate( void );
DWORD   GetUserTime( void );
void    InitializeAnalogMonitor( void );
void    InitializeClock( void );
void    InitializeCommand( void );
void    MonitorMedia( void );
void    MonitorUser( void );
void    PrintFileInformation( SearchRec searchRecord );
void    RedoCommandPrompt( void );
void    ReplaceCommandLine( void );
void    WriteOneBuffer( FSFILE *fptr, BYTE *data, WORD size );
void 	DisplayLCD();
void 	TickInit( void );
void	showStorageInformation(char volumExist, int volumType);

//USB\SD To UART
void	USBSDTOUARTFunction( void );
void	InitializeUSBMiniA( void );
void	CloseUSBMiniA( void );
void	USBTOUARTShutdown( void );
void	SDTOUARTShutdown( void );
void	InitializeSPISDCard( void );

//SD Card Reader
static void InitializeSystem(void);
void	USBDeviceTasks(void);
void	ProcessIO(void);
void	YourHighPriorityISRCode(void);
void	YourLowPriorityISRCode(void);
void	InitializeSDCardReader( void );
void	SDCardReaderInternalFlashFunction( void );
void	SDCardReaderShutdown( void );
void	InitializeUSBMiniB( void );

#if defined( __C30__ )
    DWORD   PIC24RTCCGetTime( void );
    DWORD   PIC24RTCCGetDate( void );
    void    PIC24RTCCSetTime( WORD weekDay_hours, WORD minutes_seconds );
    void    PIC24RTCCSetDate( WORD xx_year, WORD month_day );
    void    UnlockRTCC( void );
#endif

// *****************************************************************************
// *****************************************************************************
// Macros
// *****************************************************************************
// *****************************************************************************

#define IsNum(c)            ((('0' <= c) && (c <= '9')) ? TRUE : FALSE)
#define UpperCase(c)        (('a'<= c) && (c <= 'z') ? c - 0x20 : c)
#define SkipWhiteSpace()    { while (commandInfo.buffer[commandInfo.index] == ' ') commandInfo.index++; }
#define DISK_SIZE_B	0
#define	DISK_SIZE_KB 1
#define	DISK_SIZE_MB 2
#define	DISK_SIZE_GB 3		
#define	DISK_SIZE_SYSTEM 1024
#define	DISK_SIZE_SYSTEM_SHOW 9999

// *****************************************************************************
// *****************************************************************************
// Global Variables
// *****************************************************************************
// *****************************************************************************

    OLD_COMMANDS        commandBuffer;
    COMMAND             commandInfo;
    volatile BYTE       logBufferReading;
    BYTE                logBufferWriting;
    LOGGER_STATUS       loggerStatus;
    volatile DWORD      currentTick;
    volatile LOG_DATA   logData[NUM_LOG_BUFFERS];
    VOLUME_INFO         volume;
    
    int buttonPress = 0;								//Indicate which button is pressed
	SCREEN_STATES  screenStateCur = SCREEN_MAIN;	//Which Screen is now

	char previousMinute;							//minute whether changed
    rtccDate        currentDate;
    rtccTime        currentTime;
	char _rtcc_str[16] = "                ";

	int usb_sd_to_uart = 0;		//0,disable sd to uart;1,enable sd to uart
	int usb_sd_card = 0;		//0, disable sd card reader;1,enable sd card reader
	int usb_master = 0;			//0,disable usb to uart;1,enable usb to uart
	int	usb_flash = 0;			//0,disable Internal Flash;1,enable Internal Flash
	char MassStorageName[FILE_NAME_SIZE+2] = {0};
	unsigned long   MassStorageSize = 0;

//******************************************************************************
//******************************************************************************
// Configuration Bits
//******************************************************************************
//******************************************************************************

#define PLL_96MHZ_OFF   0xFFFF
#define PLL_96MHZ_ON    0xF7FF

#if defined( __PIC24FJ256GB106__ )
	_CONFIG2(IESO_OFF & PLL_96MHZ_ON & PLLDIV_DIV5 & FNOSC_PRIPLL & POSCMOD_HS)   // Primary HS OSC with PLL, USBPLL /3
	_CONFIG1(JTAGEN_OFF & ICS_PGx2 & FWDTEN_OFF)        // JTAG off, watchdog timer off
#elif defined( __PIC32MX__ )
    #pragma config UPLLEN   = ON        // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_5         // USB PLL Input Divider
    #pragma config FPLLIDIV = DIV_5         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable
#else
    #error Code just to PIC24F256GB106 and PIC32MX440F512H
#endif


//******************************************************************************
//******************************************************************************
// Main Application
//******************************************************************************
//******************************************************************************

int main( void )
{
//******************************Varies******************************************

//******************************Oscillator Setting******************************
	int  value;

	mJTAGPortEnable(0);
    
	value = SYSTEMConfigWaitStatesAndPB( GetSystemClock() );
    
 	// Enable the cache for the best performance
	CheKseg0CacheOn();
    
	INTEnableSystemMultiVectoredInt();
    
	value = OSCCON;
	while (!(value & 0x00000020))
	{
		value = OSCCON;    // Wait for PLL lock to stabilize
	}
		
	INTEnableInterrupts();


//****************************** Functions  **********************************
// Initialize the RTCC
    InitializeClock();

//Light LCD
	LightLCD();

//Inilitialize LCD
	InitLCDPins();
	InitByInstru();

//Inilitialize Buttons
	ButtonInit();

// Initialize the reference timer.
	TickInit();

//Initialize LED
	LEDInit();

//LCD Output
	while(1)
	{	
		ButtonsMsg();
		DisplayLCD();
	}

	return 0;
}

//******************************************************************************
//******************************************************************************
// Function
//******************************************************************************
//******************************************************************************

/****************************************************************************
  Function:
    void DisplayLCD( void )

  Description:
    This function display current LCD information and store previous LCD 
information.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:

  ***************************************************************************/
void DisplayLCD( void )
{
	char lcd_line1[17]={0};
	char lcd_line2[17]={0};
	char rtccFlag = 0;

	rtccFlag = RTCCProcessEvents();
	switch(screenStateCur)
	{
		case SCREEN_MAIN:
			strcpy(lcd_line1,"OufffTeam 2011  ");
			strcpy(lcd_line2,"Carte de dev    ");
			Set_Line_Information(1,0,lcd_line1,16);
			Set_Line_Information(2,0,lcd_line2,16);
			DelayMs(2000);

			screenStateCur=SCREEN_MENU_SD_CARD;

			strcpy(lcd_line2,"1.SD Card       ");
			Set_Line_Information(2,0,lcd_line2,16);
			LCD_check_busy();
			WriteAdress(0x4F);
			WriteData(0x7E);		//->
			break;
			
		case SCREEN_MENU_SD_CARD:
			if(buttonPress == 1)								//Right Button Pressed
			{
				buttonPress = 0;

				screenStateCur = SCREEN_MENU_INTERNAL_FLASH;

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"2.In Flash      ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4E);
				WriteData(0x7F);	//<-
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);	//->
			}
			else if(buttonPress == 3)							//Middle Button Pressed
			{
				buttonPress = 0;

			#if defined(USE_SD_INTERFACE_WITH_SPI)

				buttonPress = 0;
				usb_sd_card = 1;
				SD_LED = LED_TURN_ON;
				SDCardReaderInternalFlashFunction();
				SD_LED = LED_TURN_OFF;

			#else
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"Module Disabled!");
				Set_Line_Information(2,0,lcd_line2,16);

				while(1)
				{
					ButtonsMsg();
					if(buttonPress == 3)
						break;
				}
			#endif

				//Quit from "SD Card Reader"
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"1.SD Card       ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);		//->
			}
			else												//No Button Presses,Refresh Time
			{	
				if(rtccFlag)
				{
					strcpy(lcd_line1,_rtcc_str);
					Set_Line_Information(1,0,lcd_line1,16);
				}
			}

			break;

		case SCREEN_MENU_INTERNAL_FLASH:
			if(buttonPress == 1)								//Right Button Pressed
			{
				buttonPress = 0;

				screenStateCur = SCREEN_MENU_SD_TO_UART;

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);

				strcpy(lcd_line2,"3.SD To UART    ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4E);
				WriteData(0x7F);	//<-
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);	//->
			}
			else if(buttonPress == 2)							//Left Button Pressed
			{
				buttonPress = 0;

				screenStateCur = SCREEN_MENU_SD_CARD;

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);

				strcpy(lcd_line2,"1.SD Card       ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);		//->		
			}
			else if(buttonPress == 3)							//Middle Button Pressed
			{
				buttonPress = 0;

			#if defined(USE_INTERNAL_FLASH)
				strcpy(lcd_line1,"Name:In Flash   ");
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"Size:512KB      ");
				Set_Line_Information(2,0,lcd_line2,16);

				usb_flash = 1;
				FLASH_LED = LED_TURN_ON;
				SDCardReaderInternalFlashFunction();
				FLASH_LED = LED_TURN_OFF;

			#else
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"Module Disabled!");
				Set_Line_Information(2,0,lcd_line2,16);

				while(1)
				{
					ButtonsMsg();
					if(buttonPress == 3)
						break;
				}
			#endif

				//Quit from "Internal Flash"
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"2.In Flash      ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4E);
				WriteData(0x7F);	//<-
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);	//->
			}
			else											//No Button Presses,Refresh Time
			{
				if(rtccFlag)
				{
					strcpy(lcd_line1,_rtcc_str);
					Set_Line_Information(1,0,lcd_line1,16);
				}
			}

			break;

		case SCREEN_MENU_SD_TO_UART:
			if(buttonPress == 1)								//Right Button Pressed
			{
				buttonPress = 0;

				screenStateCur = SCREEN_MENU_USB_TO_UART;

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);

				strcpy(lcd_line2,"4.USB To UART   ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4F);		//<-
				WriteData(0x7F);
			}
			else if(buttonPress == 2)							//Left Button Pressed
			{
				buttonPress = 0;

				screenStateCur = SCREEN_MENU_INTERNAL_FLASH;

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);

				strcpy(lcd_line2,"2.In Flash      ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4E);
				WriteData(0x7F);	//<-
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);	//->		
			}
			else if(buttonPress == 3)							//Middle Button Pressed
			{
				buttonPress = 0;

			#if defined(USE_SD_INTERFACE_WITH_SPI)
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"Reading ......  ");
				Set_Line_Information(2,0,lcd_line2,16);

				usb_sd_to_uart = 1;
				SD_LED = LED_TURN_ON;
				USBSDTOUARTFunction();
				SD_LED = LED_TURN_OFF;

			#else
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"Module Disabled!");
				Set_Line_Information(2,0,lcd_line2,16);

				while(1)
				{
					ButtonsMsg();
					if(buttonPress == 3)
						break;
				}
			#endif

				//Quit from "SD Card Reader"
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"3.SD To UART    ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4E);
				WriteData(0x7F);	//<-
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);	//->
			}
			else											//No Button Presses,Refresh Time
			{
				if(rtccFlag)
				{
					strcpy(lcd_line1,_rtcc_str);
					Set_Line_Information(1,0,lcd_line1,16);
				}
			}

			break;

		case SCREEN_MENU_USB_TO_UART:
			if(buttonPress == 2)								//Left Button Pressed
			{
				buttonPress = 0;

				screenStateCur = SCREEN_MENU_SD_TO_UART;

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);

				strcpy(lcd_line2,"3.SD To UART    ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4E);
				WriteData(0x7F);	//<-
				LCD_check_busy();
				WriteAdress(0x4F);
				WriteData(0x7E);	//->
			}
			else if(buttonPress == 3)							//Middle Button Pressed
			{
				buttonPress = 0;

			#if defined(USE_USB_INTERFACE)

				usb_master = 1;
				USB_LED = LED_TURN_ON;
				USBSDTOUARTFunction();
				USB_LED = LED_TURN_OFF;

			#else

				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"Module Disabled!");
				Set_Line_Information(2,0,lcd_line2,16);

				while(1)
				{
					ButtonsMsg();
					if(buttonPress == 3)
						break;
				}
			#endif

				//Quit from "USB To UART" Function 
				strcpy(lcd_line1,_rtcc_str);
				Set_Line_Information(1,0,lcd_line1,16);
				strcpy(lcd_line2,"4.USB To UART   ");
				Set_Line_Information(2,0,lcd_line2,16);
				LCD_check_busy();
				WriteAdress(0x4F);		//<-
				WriteData(0x7F);
			}
			else												//No Button Presses,Refresh Time
			{
				if(rtccFlag)
				{
					strcpy(lcd_line1,_rtcc_str);
					Set_Line_Information(1,0,lcd_line1,16);
				}
			}

			break;

		default:
			break;
	}

	buttonPress = 0;

	return;
}


/****************************************************************************
  Function:
    void TickInit( void )

  Description:
    This function sets up Timer 4 to generate an interrupt every 10 ms.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    The timer period and prescaler values are defined in HardwareProfile.h,
    since they are dependent on the oscillator speed.
  ***************************************************************************/

/////////////////////////////////////T4CON////////////////////////////////////
void TickInit( void )
{
#if defined( __C30__ )
	T4CON = 0; 						//Stops the Timer4 and reset control reg.
    TMR4 = 0;						//Clear contents of the timer register
    PR4 = TIMER_PERIOD;				//Load the Period register with the value 20000(10ms)
    T4CON = TIMER_ON | STOP_TIMER_IN_IDLE_MODE | TIMER_SOURCE_INTERNAL |
            GATED_TIME_DISABLED | TIMER_16BIT_MODE | TIMER_PRESCALER;
	IPC6bits.T4IP = 0x01;			//Setup Timer4 interrupt for desired priority level 1,low
    IFS1bits.T4IF = 0;              //Clear Timer4 Interrupt flag
    IEC1bits.T4IE = 1;              //Enable Timer4 interrupt
    T4CONbits.TON = 1;              //Run timer4
#elif defined( __PIC32MX__ )
    OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_16, TIMER_PERIOD);
    ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_7);

#endif
}

/****************************************************************************
  Function:
    void	USBSDTOUARTFunction( void )

  Description:
    This function is USB To UART

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
  ***************************************************************************/
void	USBSDTOUARTFunction( void )
{
	FSFILE              *filePointer1;
	FSFILE              *filePointer2;
	char                oneChar;
	char                param1[MAX_COMMAND_LENGTH];
	char                param2[MAX_COMMAND_LENGTH];
	unsigned char       setAttribute, checkAttribute;
	SearchRec           searchRecord;

	if(usb_sd_to_uart == 1)
	{
		InitializeSPISDCard();
	}
	if(usb_master == 1)
	{
		InitializeUSBMiniA();
		USBInitialize( 0 );
	}

	UART2Init();
	if(usb_master == 1)
	{
		UART2PrintString( "\r\n\r\n***** Sure Electronics USB To UART " );
	}
	if(usb_sd_to_uart == 1)
	{
		UART2PrintString( "\r\n\r\n***** Sure Electronics SD To UART " );
	}
	UART2PrintString( VERSION );
	UART2PrintString( " *****\r\n\r\n" );


	commandBuffer.newest    = MAX_BUFFERED_COMMANDS;
	commandBuffer.oldest    = MAX_BUFFERED_COMMANDS;
	commandBuffer.showing   = MAX_BUFFERED_COMMANDS;
	loggerStatus.value      = 0;
	volume.valid            = FALSE;
	InitializeCommand();

        while (1)
        {

            MonitorMedia();
            MonitorUser();

            if (GetCommand())
            {
                SkipWhiteSpace();
                switch ( commandInfo.command )
                {
                    case COMMAND_NO_COMMAND:
                        break;

                    case COMMAND_ATTRIB:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString ("No media present.\r\n");
                            break;
                        }

                        checkAttribute = ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_ARCHIVE;
                        setAttribute = 0x00;

                        GetOneWord (param1);

                        while ((param1[0] == '+' || param1[0] == '-') && setAttribute != 0xFF)
                        {
                            switch (param1[1])
                            {
                                case 'R':
                                    if (((checkAttribute & ATTR_READ_ONLY) == 0) || (param1[2] != 0)) 
                                    {
                                        UART2PrintString( "Invalid switch - " );
                                        UART2PutChar(param1[0]);
                                        UART2PrintString("R\r\n");
                                        setAttribute = 0xFF;
                                    }
                                    else
                                    {
                                        checkAttribute &= ~ATTR_READ_ONLY;
                                        if (param1[0] == '+')
                                            setAttribute |= ATTR_READ_ONLY;
                                    }
                                    break;
                                case 'A':
                                    if (((checkAttribute & ATTR_ARCHIVE) == 0) || (param1[2] != 0))
                                    {
                                        UART2PrintString( "Invalid switch - " );
                                        UART2PutChar(param1[0]);
                                        UART2PrintString("A\r\n");
                                        setAttribute = 0xFF;
                                    }
                                    else
                                    {
                                        checkAttribute &= ~ATTR_ARCHIVE;
                                        if (param1[0] == '+')
                                            setAttribute |= ATTR_ARCHIVE;
                                    }
                                    break;
                                case 'H':
                                    if (((checkAttribute & ATTR_HIDDEN) == 0) || (param1[2] != 0))
                                    {
                                        UART2PrintString( "Invalid switch - " );
                                        UART2PutChar(param1[0]);
                                        UART2PrintString("H\r\n");
                                        setAttribute = 0xFF;
                                    }
                                    else
                                    {
                                        checkAttribute &= ~ATTR_HIDDEN;
                                        if (param1[0] == '+')
                                            setAttribute |= ATTR_HIDDEN;
                                    }
                                    break;
                                case 'S':
                                    if (((checkAttribute & ATTR_SYSTEM) == 0) || (param1[2] != 0))
                                    {
                                        UART2PrintString( "Invalid switch - " );
                                        UART2PutChar(param1[0]);
                                        UART2PrintString("S\r\n");
                                        setAttribute = 0xFF;
                                    }
                                    else
                                    {
                                        checkAttribute &= ~ATTR_SYSTEM;
                                        if (param1[0] == '+')
                                            setAttribute |= ATTR_SYSTEM;
                                    }
                                    break;
                                default:
                                    UART2PrintString( "Invalid switch - " );
                                    UART2PutChar(param1[0]);
                                    UART2PutChar(param1[1]);
                                    UART2PrintString("\r\n");
                                    setAttribute = 0xFF;
                                    break;
                            }
                            GetOneWord (param1);
                        }

                        if (param1[0] == 0)
                        {
                            UART2PrintString ("Please enter a target file or directory.\r\n");
                            break;
                        }

                        if (setAttribute != 0xFF)
                        {
                            if (!FindFirst (param1, ATTR_MASK & ~ATTR_VOLUME, &searchRecord))
                            {
                                if ((setAttribute == 0x00) && (checkAttribute == 0x27))
                                {
                                    char buffer[50];
                                    sprintf( buffer, "       %.42s", searchRecord.filename );
                                    if (searchRecord.attributes &     ATTR_READ_ONLY           )
                                    {
                                        buffer[0] = 'R';
                                    }
                                    if (searchRecord.attributes &     ATTR_HIDDEN           )
                                    {
                                        buffer[1] = 'H';
                                    }
                                    if (searchRecord.attributes &     ATTR_SYSTEM           )
                                    {
                                        buffer[2] = 'S';
                                    }
                                    if (searchRecord.attributes &     ATTR_ARCHIVE           )
                                    {
                                        buffer[3] = 'A';
                                    }
                                    UART2PrintString (buffer);
                                    UART2PrintString ("\r\n");
                                }
                                else
                                {
                                    if ((filePointer2 = FSfopen( param1, "r" )) == NULL)
                                    {
                                        UART2PrintString( " - Error opening file\r\n" );
                                        break;
                                    }

                                    if (checkAttribute & ATTR_READ_ONLY)
                                        setAttribute |= (searchRecord.attributes & ATTR_READ_ONLY);
                                    if (checkAttribute & ATTR_ARCHIVE)
                                        setAttribute |= (searchRecord.attributes & ATTR_ARCHIVE);
                                    if (checkAttribute & ATTR_SYSTEM)
                                        setAttribute |= (searchRecord.attributes & ATTR_SYSTEM);
                                    if (checkAttribute & ATTR_HIDDEN)
                                        setAttribute |= (searchRecord.attributes & ATTR_HIDDEN);
                                    if (FSattrib (filePointer2, setAttribute))
                                    {
                                        UART2PrintString ("Could not set attributes\r\n");
                                    }
                                    else
                                    {
                                        if (FSfclose (filePointer2))
                                        {
                                            UART2PrintString ("Could not set attributes\r\n");
                                        }
                                    }
                            }
                            }
                        }

                        break;

                    case COMMAND_CD:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            UART2PrintString( " - Parameter required\r\n" );
                        }
                        else
                        {
                            if (FSchdir( &(commandInfo.buffer[commandInfo.index]) ))
                            {
                                UART2PrintString( " - Error performing command\r\n" );
                            }
                        }
                        break;

                    case COMMAND_COPY:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        GetOneWord( param1 );
                        GetOneWord( param2 );
                        if ((param1[0] == 0) || (param2[0] == 0))
                        {
                            UART2PrintString( " - Two parameters required\r\n" );
                        }
                        else
                        {
                            if (!strcmp( "CON", param1 ))
                            {
                                // Create the file from the console.  This is just a quick example.  A better one
                                // would be to take in an entire line, and then write the line.  That way, line
                                // editing would be supported.
                                if ((filePointer2 = FSfopen( param2, "w" )) == NULL)
                                {
                                    UART2PrintString( " - Error creating file\r\n" );
                                }
                                else
                                {
                                    UART2PrintString( "Creating file from console. Enter Control-Z to terminate...\r\n" );
                                    oneChar = 0;
                                    do
                                    {
                                        MonitorMedia();
                                        if (U2STAbits.URXDA)  //UART2IsPressed())
                                        {
                                            oneChar = UART2GetChar();
                                            if (oneChar != 0x1A) // Control-Z
                                            {
                                                UART2PutChar( oneChar );
                                                if (FSfwrite( &oneChar, 1, 1, filePointer2) != 1)
                                                {
                                                    UART2PrintString( " - Error writing file\r\n" );
                                                    break;
                                                }
                                                if (oneChar == 0x0D)
                                                {
                                                    oneChar = 0x0A;
                                                    UART2PutChar( oneChar );
                                                    FSfwrite( &oneChar, 1, 1, filePointer2 );
                                                }
                                            }
                                            else
                                            {
                                                UART2PrintString( "\r\n" );
                                            }
                                        }
                                    } while (oneChar != 0x1A);
                                    FSfclose( filePointer2 );
                                }
                            }
                            else
                            {
                                if (FindFirst( param1,
                                        ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN, &searchRecord ))
                                {
                                    UART2PrintString( " - File not found\r\n" );
                                }
                                else if ((filePointer1 = FSfopen( param1, "r" )) == NULL)
                                {
                                    UART2PrintString( " - Error opening file\r\n" );
                                }
                                else
                                {
                                    if ((filePointer2 = FSfopen( param2, "w" )) == NULL)
                                    {
                                        UART2PrintString( " - Error creating file\r\n" );
                                    }
                                    else
                                    {
                                        size_t  charsRead;
                                        BYTE    readBuffer[COPY_BUFFER_SIZE];

                                        while (!FSfeof( filePointer1 ))
                                        {
                                            charsRead = FSfread( readBuffer, 1, COPY_BUFFER_SIZE, filePointer1 );
                                            if (charsRead)
                                            {
                                                if (FSfwrite( readBuffer, 1, charsRead, filePointer2) != charsRead)
                                                {
                                                    UART2PrintString( " - Error writing file\r\n" );
                                                    break;
                                                }
                                            }
                                        }
                                        FSfclose( filePointer2 );
                                    }
                                    FSfclose( filePointer1 );
                                }
                            }
                        }
                        break;

                    case COMMAND_DATE:
                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            UART2PrintString( "Current date: " );

                            #if defined( __C30__)
                                currentDate.l = PIC24RTCCGetDate();
                            #elif defined( __PIC32MX__ )
                                currentDate.l   = RtccGetDate();
                            #else
                                #error Need DATE implementation.
                            #endif

                            UART2PutChar( '2' );
                            UART2PutChar( '0' );
                            UART2PutHex( currentDate.year );
                            UART2PutChar( '-' );
                            UART2PutHex( currentDate.mon );
                            UART2PutChar( '-' );
                            UART2PutHex( currentDate.mday );
                            UART2PrintString( "\r\n" );
                        }
                        else
                        {
                            // Set the current date.
                            DWORD_VAL   date;

                            date.Val = GetUserDate();

                            if (date.Val)
                            {
                                #if defined( __C30__)
                                    PIC24RTCCSetDate( date.w[1], date.w[0] );
                                #elif defined( __PIC32MX__ )
                                    RtccSetDate( date.Val );
                                    RtccEnable();
                                #else
                                    #error Need DATE implementation.
                                #endif
                            }
                            else
                            {
                                UART2PrintString( " - Invalid date specified\r\n" );
                            }
                        }
                        break;

                    case COMMAND_DEL:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            UART2PrintString( " - Parameter required\r\n" );
                        }
                        else
                        {
                            if (FindFirst( &(commandInfo.buffer[commandInfo.index]),
                                    ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN, &searchRecord ))
                            {
                                UART2PrintString( " - File not found\r\n" );
                            }
                            else
                            {
                                if (FSremove( &(commandInfo.buffer[commandInfo.index] )))
                                {
                                    UART2PrintString( " - Error performing command\r\n" );
                                }
                            }
                        }
                        break;

                    case COMMAND_DIR:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            strcpy( param1, "*.*" );
                        }
                        else
                        {
                            strcpy( param1, &(commandInfo.buffer[commandInfo.index]) );
                        }
                        if (!FindFirst( param1, ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN, &searchRecord ))
                        {
                            PrintFileInformation( searchRecord );
                            while (!FindNext( &searchRecord ))
                            {
                                PrintFileInformation( searchRecord );
                            }
                        }
                        else
                        {
                            UART2PrintString( "No files found.\r\n" );
                        }
                        break;

                    case COMMAND_HELP:
						if(usb_master == 1)
						{
                        	UART2PrintString( "\r\nSure Electronics USB To UART " );
					    }
					    if(usb_sd_to_uart == 1)
						{
                       		UART2PrintString( "\r\nSure Electronics SD To UART " );
						}              
						UART2PrintString( VERSION );
                        UART2PrintString( "\r\n\r\nAvailable commands:\r\n" );
                        UART2PrintString( "    ATTRIB <+|-><R|S|H|A> <name> - change attributes specified\r\n" );
                        UART2PrintString( "    CD <name>                    - change directory\r\n" );
                        UART2PrintString( "    COPY <file1> <file2>         - copy [file1] to [file2]\r\n" );
                        UART2PrintString( "    COPY CON <file>              - create [file] from console input\r\n" );
                        UART2PrintString( "    DATE [yyyy-mm-dd]            - display or set the date\r\n" );
                        UART2PrintString( "    DEL <file>                   - delete file, current directory only\r\n" );
                        UART2PrintString( "    DIR [file]                   - display directory\r\n" );
                        UART2PrintString( "    HELP or ?                    - display help\r\n" );
                        UART2PrintString( "    MD <name>                    - make directory\r\n" );
                        UART2PrintString( "    RD <name>                    - remove directory\r\n" );
                        UART2PrintString( "    REN <file1> <file2>          - rename [file1] to [file2]\r\n" );
                        UART2PrintString( "    TIME [hh:mm:ss]              - display or set the time (24 hr format)\r\n" );
                        UART2PrintString( "    TYPE <file>                  - print out contents of file\r\n" );
                        break;

                    case COMMAND_MD:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            UART2PrintString( " - Parameter required\r\n" );
                        }
                        else
                        {
                            if (FSmkdir( &(commandInfo.buffer[commandInfo.index])))
                            {
                                UART2PrintString( " - Error performing command\r\n" );
                            }
                        }
                        break;

                    case COMMAND_RD:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            UART2PrintString( " - Parameter required\r\n" );
                        }
                        else
                        {
                            if (FSrmdir( &(commandInfo.buffer[commandInfo.index]), TRUE ))
                            {
                                UART2PrintString( " - Error performing command\r\n" );
                            }
                        }
                        break;

                    case COMMAND_REN:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        GetOneWord( param1 );
                        GetOneWord( param2 );
                        if ((param1[0] == 0) || (param2[0] == 0))
                        {
                            UART2PrintString( " - Two parameters required\r\n" );
                        }
                        else
                        {
                            if ((filePointer1 = FSfopen( param1, "r" )) == NULL)
                            {
                                UART2PrintString( " - Cannot find file\r\n" );
                            }
                            else
                            {
                                if (FSrename( param2, filePointer1 ))
                                {
                                    UART2PrintString( " - Error performing command\r\n" );
                                }
                                FSfclose( filePointer1 );
                            }
                        }
                        break;

                    case COMMAND_TIME:
                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            // Display the current time.
                            UART2PrintString( "Current time: " );

                            #if defined( __C30__)
                                currentTime.l = PIC24RTCCGetTime();
                            #elif defined( __PIC32MX__ )
                                currentTime.l = RtccGetTime();
                            #else
                                #error Need TIME implementation.
                            #endif

                            UART2PutHex( currentTime.hour );
                            UART2PutChar( ':' );
                            UART2PutHex( currentTime.min );
                            UART2PutChar( ':' );
                            UART2PutHex( currentTime.sec );
                            UART2PrintString( "\r\n" );
                        }
                        else
                        {
                            // Set the current date.
                            DWORD_VAL   time;

                            time.Val = GetUserTime();

                            if (time.Val)
                            {
                                #if defined( __C30__)
                                    PIC24RTCCSetTime( time.w[1], time.w[0] );
                                #elif defined( __PIC32MX__ )
                                    RtccSetTime( time.Val );
                                    RtccEnable();
                                #else
                                    #error Need TIME implementation.
                                #endif
                            }
                            else
                            {
                                UART2PrintString( " - Invalid time specified\r\n" );
                            }
                        }
                        break;

                    case COMMAND_TYPE:
                        if (!loggerStatus.mediaPresent)
                        {
                            UART2PrintString( "No media present.\r\n" );
                            break;
                        }

                        if (commandInfo.buffer[commandInfo.index] == 0)
                        {
                            UART2PrintString( " - Parameter required\r\n" );
                        }
                        else
                        {
                            if (FindFirst( &(commandInfo.buffer[commandInfo.index]),
                                    ATTR_DIRECTORY | ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN, &searchRecord ))
                            {
                                UART2PrintString( " - File not found\r\n" );
                            }
                            else if ((filePointer1 = FSfopen( &(commandInfo.buffer[commandInfo.index]), "r" )) == NULL)
                            {
                                UART2PrintString( " - Error opening file\r\n" );
                            }
                            else
                            {
                                while (!FSfeof( filePointer1 ))
                                {
                                    // This is just a quick example.  It's not very efficient to
                                    // read only one byte at a time!
                                    if (FSfread( &oneChar, 1, 1, filePointer1 ) == 1)
                                    {
                                        UART2PutChar( oneChar );
                                    }
                                    else
                                    {
                                        UART2PrintString( "\r\n - Error reading file\r\n" );
                                        break;
                                    }
                                }
                                UART2PrintString( "\r\n" );
                                FSfclose( filePointer1 );
                            }
                        }
                        break;

                    default:
                        UART2PrintString( "Unsupported command\r\n" );
                        break;
                }
                InitializeCommand();
            }

			ButtonsMsg();
			if(buttonPress==3)
			{
	            loggerStatus.mediaPresent   = FALSE;
	            volume.valid                = FALSE;

				if(usb_master == 1)
				{
					usb_master = 0;
					USBTOUARTShutdown();
				}
				if(usb_sd_to_uart == 1)
				{
					usb_sd_to_uart = 0;
					SDTOUARTShutdown();
				}
				break;
			}
        }
	return;
}

/****************************************************************************
  Function:
    void USBTOUARTShutdown( void )

  Description:
    This function close the USB TO UART

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void USBTOUARTShutdown( void )
{
//Close UART
	UART2Close();

//Disable USB MiniA
	CloseUSBMiniA();

//Disable USB Interrupt
	USBMaskInterrupts();
}

/****************************************************************************
  Function:
    void InitializeSPISDCard( void )

  Description:
    This function initializes the SPI SD Card

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitializeSPISDCard( void )
{
	#if defined( __C30__ )
//Digital Output
	AD1PCFG = 0xFFFF;

//SPI SD Card initialize
	__asm__ ("MOV #OSCCON,w1");
	__asm__ ("MOV.b #0x02, w0");
	__asm__ ("MOV #0x46, w2");
	__asm__ ("MOV #0x57, w3");
	__asm__ ("MOV.b w2, [w1]");
	__asm__ ("MOV.b w3, [w1]");
	__asm__ ("MOV.b w0, [w1]");

    RPINR20bits.SDI1R = 26; //SPI1 Data Input,SPIIN		Now:26;RG7/RP26
    RPOR9bits.RP19R = 7;	//SPI1 Data Output,SPIOUT	Now:RP19/RG8,RPOR9bits.RP19R=7
    RPOR10bits.RP21R = 8;   //SPI1 Clock Output,SPICLK	Now:RP21/RG6,RPOR10bits.RP21R=8
	#endif

	return;
}

/****************************************************************************
  Function:
    void SDTOUARTShutdown( void )

  Description:
    This function close the USB TO UART

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void SDTOUARTShutdown( void )
{
//Close UART
	UART2Close();

//Close SPI SD Card
	MDD_SDSPI_ShutdownMedia();

	return;
}

/****************************************************************************
  Function:
    void EraseCommandLine( void )

  Description:
    This function erases the current command line.  It works by sending a
    backspace-space-backspace combination for each character on the line.

  Precondition:
    commandInfo.index must be valid.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void EraseCommandLine( void )
{
    BYTE    i;
    BYTE    lineLength;

    lineLength = commandInfo.index;
    for (i=0; i<lineLength; i++)
    {
        UART2PutChar( 0x08 );
        UART2PutChar( ' ' );
        UART2PutChar( 0x08 );
    }
    commandInfo.index = 0;
}
/****************************************************************************
  Function:
    BYTE GetCommand( void )

  Description:
    This function returns whether or not the user has finished entering a
    command.  If so, then the command entered by the user is determined and
    placed in commandInfo.command.  The command line index
    (commandInfo.index) is set to the first non-space character after the
    command.

  Precondition:
    commandInfo.reading must be valid.

  Parameters:
    None

  Return Values:
    TRUE    - The user has entered a command.  The command is in
                  commandInfo.command.
    FALSE   - The user has not finished entering a command.

  Remarks:
    None
  ***************************************************************************/

BYTE GetCommand( void )
{
    char    firstWord[MAX_COMMAND_LENGTH];

    if (commandInfo.reading)
    {
        return FALSE;
    }
    else
    {
        commandInfo.index = 0;

        commandInfo.index = 0;
        GetOneWord( firstWord );
        SkipWhiteSpace();

        if (firstWord[0] == 0)
        {
            commandInfo.command = COMMAND_NO_COMMAND;
            return TRUE;
        }

        if (!strncmp( firstWord, "ATTRIB", 6 ) && (strlen(firstWord) == 6))
        {
            commandInfo.command = COMMAND_ATTRIB;
            return TRUE;
        }
        if (!strncmp( firstWord, "CD", 2 ) && (strlen(firstWord) == 2))
        {
            commandInfo.command = COMMAND_CD;
            return TRUE;
        }
        if (!strncmp( firstWord, "COPY", 4 ) && (strlen(firstWord) == 4))
        {
            commandInfo.command = COMMAND_COPY;
            return TRUE;
        }
        if (!strncmp( firstWord, "DATE", 4 ) && (strlen(firstWord) == 4))
        {
            commandInfo.command = COMMAND_DATE;
            return TRUE;
        }
        if (!strncmp( firstWord, "DEL", 3 ) && (strlen(firstWord) == 3))
        {
            commandInfo.command = COMMAND_DEL;
            return TRUE;
        }
        if (!strncmp( firstWord, "DIR", 3 ) && (strlen(firstWord) == 3))
        {
            commandInfo.command = COMMAND_DIR;
            return TRUE;
        }
        if ((!strncmp( firstWord, "HELP", 4 )  && (strlen(firstWord) == 4)) ||
            (!strncmp( firstWord, "?", 1 ) && (strlen(firstWord) == 1)))
        {
            commandInfo.command = COMMAND_HELP;
            return TRUE;
        }
        if (!strncmp( firstWord, "MD", 2 ) && (strlen(firstWord) == 2))
        {
            commandInfo.command = COMMAND_MD;
            return TRUE;
        }
        if (!strncmp( firstWord, "RD", 2 ) && (strlen(firstWord) == 2))
        {
            commandInfo.command = COMMAND_RD;
            return TRUE;
        }
        if (!strncmp( firstWord, "REN", 3 ) && (strlen(firstWord) == 3))
        {
            commandInfo.command = COMMAND_REN;
            return TRUE;
        }
        if (!strncmp( firstWord, "TIME", 4 ) && (strlen(firstWord) == 4))
        {
            commandInfo.command = COMMAND_TIME;
            return TRUE;
        }
        if (!strncmp( firstWord, "TYPE", 4 ) && (strlen(firstWord) == 4))
        {
            commandInfo.command = COMMAND_TYPE;
            return TRUE;
        }
        commandInfo.command = COMMAND_UNKNOWN;
        return TRUE;
    }
}

/****************************************************************************
  Function:
    void GetOneWord( char *buffer )

  Description:
    This function copies the next word in the command line to the specified
    buffer.  Word deliniation is marked by a space character.  The returned
    word is null terminated.

  Precondition:
    commandInfo.buffer and commandInfo.index are valid

  Parameters:
    *buffer - Pointer to where the word is to be stored.

  Returns:
    None

  Remarks:

  ***************************************************************************/
void GetOneWord( char *buffer )
{
    SkipWhiteSpace();

    while ((commandInfo.buffer[commandInfo.index] != 0) &&
           (commandInfo.buffer[commandInfo.index] != ' '))
    {
        *buffer++ = commandInfo.buffer[commandInfo.index++];
    }
    *buffer = 0;
}
/****************************************************************************
  Function:
    DWORD GetUserDate( void )

  Description:
    This function extracts a user entered date from the command line and
    places it in a DWORD that matches the format required for the RTCC.
    The required format is:
                        YYYY-MM-DD
    where YY is between 2000 and 2099.  If the date is not in a valid format,
    0 is returned.

  Precondition:
    commandInfo.buffer and commandInfo.index are valid, and
    commandInfo.index points to the first character of the date

  Parameters:


  Returns:
    If the project is built for a PIC24F, this function returns a DWORD in
    the format <00><YY><MM><DD>.  If it is built for a PIC32MX, this function
    returns a DWORD in the format <YY><MM><DD><00>.

  Remarks:
    Range checks are not comprehensive.  The day is not qualified based on
    how many days are in the specified month.

    The values from the RTCC are assumed to be in BCD format.

    The two architectures have different formats for the date.  The index
    values are set above accordingly.
  ***************************************************************************/

DWORD GetUserDate( void )
{
    DWORD_VAL   date;

    date.Val = 0;

    // Get the year.
    if (commandInfo.buffer[commandInfo.index++] != '2')                     return 0;
    if (commandInfo.buffer[commandInfo.index++] != '0')                     return 0;

    if (!IsNum( commandInfo.buffer[commandInfo.index] ))                    return 0;
    date.v[INDEX_YEAR] =  (commandInfo.buffer[commandInfo.index++] - '0') << 4;
    if (!IsNum( commandInfo.buffer[commandInfo.index] ))                    return 0;
    date.v[INDEX_YEAR] |= (commandInfo.buffer[commandInfo.index++] - '0');

    if (commandInfo.buffer[commandInfo.index++] != '-')                     return 0;

    // Get the month.
    if (!IsNum( commandInfo.buffer[commandInfo.index] ))                    return 0;
    date.v[INDEX_MONTH] =  (commandInfo.buffer[commandInfo.index++] - '0') << 4;
    if (!IsNum( commandInfo.buffer[commandInfo.index] ))                    return 0;
    date.v[INDEX_MONTH] |= (commandInfo.buffer[commandInfo.index++] - '0');
    if (!((0x01 <= date.v[INDEX_MONTH]) && (date.v[INDEX_MONTH] <= 0x12)))  return 0;

    if (commandInfo.buffer[commandInfo.index++] != '-')                     return 0;

    // Get the day.
    if (!IsNum( commandInfo.buffer[commandInfo.index] ))                    return 0;
    date.v[INDEX_DAY] =  (commandInfo.buffer[commandInfo.index++] - '0') << 4;
    if (!IsNum( commandInfo.buffer[commandInfo.index] ))                    return 0;
    date.v[INDEX_DAY] |= (commandInfo.buffer[commandInfo.index++] - '0');
    if (!((0x01 <= date.v[INDEX_DAY]) && (date.v[INDEX_DAY] <= 0x31)))      return 0;

    return date.Val;
}



/****************************************************************************
  Function:
    DWORD GetUserTime( void )

  Description:
    This function extracts a user entered time from the command line and
    places it in a DWORD that matches the format required for the RTCC.  The
    required format is:
                        HH:MM:SS
    in 24-hour format.  If the time is not in a valid format, 0 is returned.

  Precondition:
    commandInfo.buffer and commandInfo.index are valid;
    commandInfo.index points to the first character of the time

  Parameters:
    None

  Return Values:
    If the project is built for a PIC24F, this function returns a DWORD in
    the format <00><HH><MM><SS>.  If it is built for a PIC32MX, this function
    returns a DWORD in the format <HH><MM><SS><00>.

  Remarks:
    The values from the RTCC are assumed to be in BCD format.

    The two architectures have different formats for the date. The index
    values are set above accordingly.
  ***************************************************************************/

DWORD GetUserTime( void )
{
    DWORD_VAL   time;

    time.Val = 0;

    // Get the hours.
    if (!IsNum( commandInfo.buffer[commandInfo.index] )) return 0;
    time.v[INDEX_HOURS] |= (commandInfo.buffer[commandInfo.index++] - '0') << 4;
    if (!IsNum( commandInfo.buffer[commandInfo.index] )) return 0;
    time.v[INDEX_HOURS] |= (commandInfo.buffer[commandInfo.index++] - '0');
    if (time.v[INDEX_HOURS] > 0x23)                      return 0;

    if (commandInfo.buffer[commandInfo.index++] != ':')  return 0;

    // Get the minutes.
    if (!IsNum( commandInfo.buffer[commandInfo.index] )) return 0;
    time.v[INDEX_MINUTES] |= (commandInfo.buffer[commandInfo.index++] - '0') << 4;
    if (!IsNum( commandInfo.buffer[commandInfo.index] )) return 0;
    time.v[INDEX_MINUTES] |= (commandInfo.buffer[commandInfo.index++] - '0');
    if (time.v[INDEX_MINUTES] > 0x59)                    return 0;

    if (commandInfo.buffer[commandInfo.index++] != ':')  return 0;

    // Get the seconds.
    if (!IsNum( commandInfo.buffer[commandInfo.index] )) return 0;
    time.v[INDEX_SECONDS] |= (commandInfo.buffer[commandInfo.index++] - '0') << 4;
    if (!IsNum( commandInfo.buffer[commandInfo.index] )) return 0;
    time.v[INDEX_SECONDS] |= (commandInfo.buffer[commandInfo.index++] - '0');
    if (time.v[INDEX_SECONDS] > 0x59)                    return 0;

    return time.Val;
}
/****************************************************************************
  Function:
    void InitializeCommand( void )

  Description:
    This function prints a command prompt and initializes the command line
    information.  If available, the command prompt format is:
                    [Volume label]:[Current directory]>

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void InitializeCommand( void )
{
    char            buffer[50];

    if (loggerStatus.mediaPresent)
    {
        buffer[0] = 0;
        if (volume.valid)
        {
            UART2PrintString( volume.label );
            UART2PutChar( ':' );
        }

        FSgetcwd( buffer, 50 );
        UART2PrintString( buffer );
    }

    UART2PrintString( "> " );

    commandInfo.command     = COMMAND_NO_COMMAND;
    commandInfo.index       = 0;
    commandInfo.reading     = TRUE;

    memset( commandInfo.buffer, 0x00, MAX_COMMAND_LENGTH );
}

/****************************************************************************
  Function:
    void MonitorMedia( void )

  Description:
    This function calls the background tasks necessary to support USB Host
    operation.  Upon initial insertion of the media, it initializes the file
    system support and reads the volume label.  Upon removal of the media,
    the volume label is marked invalid.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void MonitorMedia( void )
{
    BYTE            mediaPresentNow;
    BYTE            mountTries;
    SearchRec       searchRecord;
	int				sizetype = 0;
	char			lcd_line1[17] = {0};
	char			lcd_line2[17] = {0};

	if(usb_master == 1)
	{
		USBTasks();
	}

    mediaPresentNow = MDD_MediaDetect();

    if (mediaPresentNow)
    {
		if(volume.valid == FALSE)
		{
			strcpy(lcd_line1,_rtcc_str);
			Set_Line_Information(1,0,lcd_line1,16);
			strcpy(lcd_line2,"Reading ......  ");
			Set_Line_Information(2,0,lcd_line2,16);

            mountTries = 10;
            while(!FSInit() && mountTries--);
            if (!mountTries)
            {
                UART2PrintString( "APP: Could not mount media\r\n" );
                loggerStatus.mediaPresent = FALSE;
            }
            else
            {
                loggerStatus.mediaPresent = TRUE;

				UART2PrintString( "\r\n ***Reading information for the Storage,Please wait*** \r\n" );

					disk_properties.new_request = TRUE;
				    do
					{
				        FSGetDiskProperties(&disk_properties);
				    } while (disk_properties.properties_status == FS_GET_PROPERTIES_STILL_WORKING);

					if( disk_properties.properties_status != FS_GET_PROPERTIES_NO_ERRORS)
					{
						MassStorageSize = 0;
						ERROR_LED = LED_TURN_ON;
					}
					else
					{
						MassStorageSize = disk_properties.results.sector_size * disk_properties.results.sectors_per_cluster * disk_properties.results.total_clusters;

						while( MassStorageSize >= DISK_SIZE_SYSTEM_SHOW)
						{
							MassStorageSize = MassStorageSize >> 10;
							sizetype++;							
						}

						if( (sizetype < DISK_SIZE_B) || (sizetype > DISK_SIZE_GB))
						{
							ERROR_LED = LED_TURN_ON;
						}
						else
						{
							ERROR_LED = LED_TURN_OFF;
						}

					}


                // Find the volume label.  We need to do this here while we are at the
                // root directory.
                if (!FindFirst( "*.*", ATTR_VOLUME, &searchRecord ))
                {
                    strcpy( volume.label, searchRecord.filename );
					strcpy( MassStorageName , searchRecord.filename );
                    volume.valid = TRUE;
               		RedoCommandPrompt();
					showStorageInformation(1,sizetype);
                }
            }
		}
    }
	else
	{
		if (mediaPresentNow != loggerStatus.mediaPresent)		
		{
            loggerStatus.mediaPresent   = FALSE;
            volume.valid                = FALSE;
		}
		strcpy( MassStorageName , "" );	
		MassStorageSize = 0;
		showStorageInformation(0,0);
	}

	return;
}

/****************************************************************************
  Function:
    void	showStorageInformation(char volumExist, int volumType)

  Description:
    This function displays the information about the name and used space of Storage

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void	showStorageInformation(char volumExist, int volumType)
{
	char lcd_line1[17] = {0};
	char lcd_line2[17] = {0};
	char size_information[4] = {0};
	int invalidflag = 0;
	int  number = 0;
	int  i = 0;

	if( volumExist == 0)
	{
		strcpy(lcd_line1,_rtcc_str);
		Set_Line_Information(1,0,lcd_line1,16);

		if( usb_master == 1)
		{
			strcpy(lcd_line2,"No USB Storage !");
			Set_Line_Information(2,0,lcd_line2,16);
		}
		if( (usb_sd_to_uart == 1) || (usb_sd_card == 1) )
		{
			strcpy(lcd_line2,"No SD Card !    ");
			Set_Line_Information(2,0,lcd_line2,16);
		}
	}
	else
	{

		if((usb_master == 1) || (usb_sd_to_uart == 1))
		{
			number = strlen( MassStorageName );
			strcpy(lcd_line1,"Name:");
	
			if( number <= 11 )
			{
				for( i = 0; i < 16; i++ )
				{
					if( i < number )
					{
						if((MassStorageName[i] >= 32) && (MassStorageName[i] <= 125))
						{
							lcd_line1[5+i] = MassStorageName[i];
						}
						else
						{
							invalidflag = 1;
						}
					}
					else
					{
						lcd_line1[5+i] = ' ';
					}
				}
			}
			else
			{
				for( i = 0; i < 16; i++ )
				{
					if( i < 8 )
					{
						if((MassStorageName[i] >= 32) && (MassStorageName[i] <= 125))
						{
							lcd_line1[5+i] = MassStorageName[i];
						}
						else
						{
							invalidflag = 1;
						}
					}
					else
					{
						lcd_line1[5+i] = '.';
					}
				}
			}

			if( invalidflag == 1)
			{
				strcpy(lcd_line1,"Illegal Name    ");	
			}
	
			strcpy(lcd_line2,"Size:");
			if( MassStorageSize > 0)
			{
				sprintf(size_information,"%lu",MassStorageSize);
				strcat(lcd_line2,size_information);
				number = strlen( lcd_line2 );
				invalidflag = 0;

				switch(volumType)
				{
					case DISK_SIZE_B:
						lcd_line2[number] = 'B';
						number++;
						break;
					case DISK_SIZE_KB:
						lcd_line2[number] = 'K';
						number++;
						lcd_line2[number] = 'B';
						number++;
						break;
					case DISK_SIZE_MB:
						lcd_line2[number] = 'M';
						number++;
						lcd_line2[number] = 'B';
						number++;
						break;
					case DISK_SIZE_GB:
						lcd_line2[number] = 'G';
						number++;
						lcd_line2[number] = 'B';
						number++;
						break;
					default:
						invalidflag = 1;
						strcpy(lcd_line2,"Illegal Size    ");
						break;				
				}
				if( invalidflag == 0 )
				{
					while( number < 16)
					{
						lcd_line2[number] = ' ';
						number++;				
					}
				}
			}
			else
			{
				strcpy(lcd_line2,"Illegal Size    ");
			}

			Set_Line_Information(1,0,lcd_line1,16);	
			Set_Line_Information(2,0,lcd_line2,16);	
		}
	
		if( usb_sd_card == 1 )
		{
			strcpy(lcd_line1,"Detect SD Card ,");
			Set_Line_Information(1,0,lcd_line1,16);

			strcpy(lcd_line2,"Refer To PC !   ");
			Set_Line_Information(2,0,lcd_line2,16);	
		}	
	}

	return;
}



/****************************************************************************
  Function:
    void MonitorUser( void )

  Description:
    This routine monitors command line input from the user.  The
    UART is polled rather than using interrupts.  If the previous
    command line is still being processed, the characters are
    ignored.  All text input is converted to upper case for
    simplification.  When the user presses the Enter or Return key,
    the command line is considered terminated.  Escape sequences are
    captured and checked.  If the up-arrow is pressed, the previous
    buffered command is displayed, until the oldest command is
    reached.  If the down-arrow is pressed, the next buffered
    command is displayed, until the newest command is displayed.
    If the down-arrow is pressed one additional time, the command
    line is erased.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    Currently, blank entries are added to the old command buffer.
  ***************************************************************************/

void MonitorUser( void )
{
    char    oneChar;

    if (U2STAbits.URXDA)
    {
        oneChar = U2RXREG;

        // If we are currently processing a command, throw the character away.
        if (commandInfo.reading)
        {
            if (commandInfo.escNeedSecondChar)
            {
                if (commandInfo.escFirstChar == 0x5B)
                {
                    if (oneChar == 0x41)        // Up arrow
                    {
                        if (commandBuffer.showing != commandBuffer.oldest)
                        {
                            if (commandBuffer.showing == MAX_BUFFERED_COMMANDS)
                            {
                                commandBuffer.showing = commandBuffer.newest;
                            }
                            else
                            {
                                commandBuffer.showing = (commandBuffer.showing - 1) & (MAX_BUFFERED_COMMANDS-1);
                            }
                        }
                        ReplaceCommandLine();
                    }
                    else if (oneChar == 0x42)   // Down arrow
                    {
                        if (commandBuffer.showing != MAX_BUFFERED_COMMANDS)
                        {
                            if (commandBuffer.showing != commandBuffer.newest)
                            {
                                commandBuffer.showing = (commandBuffer.showing + 1) & (MAX_BUFFERED_COMMANDS-1);
                                ReplaceCommandLine();
                            }
                            else
                            {
                                EraseCommandLine();
                                commandBuffer.showing = MAX_BUFFERED_COMMANDS;
                            }
                        }
                        else
                        {
                            EraseCommandLine();
                        }
                    }
                }
                commandInfo.escNeedSecondChar   = FALSE;
            }
            else if (commandInfo.escNeedFirstChar)
            {
                commandInfo.escFirstChar        = oneChar;
                commandInfo.escNeedFirstChar    = FALSE;
                commandInfo.escNeedSecondChar   = TRUE;
            }
            else
            {
                if (oneChar == 0x1B)    // ESC - an escape sequence
                {
                    commandInfo.escNeedFirstChar = TRUE;
                }
                else if (oneChar == 0x08)    // Backspace
                {
                    if (commandInfo.index > 0)
                    {
                        commandInfo.index --;
                        UART2PutChar( 0x08 );
                        UART2PutChar( ' ' );
                        UART2PutChar( 0x08 );
                    }
                }
                else if ((oneChar == 0x0D) || (oneChar == 0x0A))
                {
                    UART2PrintString( "\r\n" );
                    commandInfo.buffer[commandInfo.index]   = 0; // Null terminate the input command
                    commandInfo.reading                     = FALSE;
                    commandInfo.escNeedFirstChar            = FALSE;
                    commandInfo.escNeedSecondChar           = FALSE;

                    // Copy the new command into the command buffer
                    commandBuffer.showing = MAX_BUFFERED_COMMANDS;
                    if (commandBuffer.oldest == MAX_BUFFERED_COMMANDS)
                    {
                        commandBuffer.oldest = 0;
                        commandBuffer.newest = 0;
                    }
                    else
                    {
                        commandBuffer.newest = (commandBuffer.newest + 1) & (MAX_BUFFERED_COMMANDS-1);
                        if (commandBuffer.newest == commandBuffer.oldest)
                        {
                            commandBuffer.oldest = (commandBuffer.oldest + 1) & (MAX_BUFFERED_COMMANDS-1);
                        }
                    }
                    strcpy( &(commandBuffer.lines[commandBuffer.newest][0]), commandInfo.buffer );
                }
                else if ((0x20 <= oneChar) && (oneChar <= 0x7E))
                {
                    oneChar = UpperCase( oneChar ); // To make later processing simpler
                    if (commandInfo.index < MAX_COMMAND_LENGTH)
                    {
                        commandInfo.buffer[commandInfo.index++] = oneChar;
                    }
                    UART2PutChar( oneChar );    // Echo the character
                }
            }
        }
    }
}
/****************************************************************************
  Function:
    DWORD   PIC24RTCCGetDate( void )

  Description:
    This routine reads the date from the RTCC module.

  Precondition:
    The RTCC module has been initialized.


  Parameters:
    None

  Returns:
    DWORD in the format <xx><YY><MM><DD>

  Remarks:
    To catch roll-over, we do two reads.  If the readings match, we return
    that value.  If the two do not match, we read again until we get two
    matching values.

    For the PIC32MX, we use library routines, which return the date in the
    PIC32MX format.
  ***************************************************************************/

#if defined( __C30__ )
DWORD   PIC24RTCCGetDate( void )
{
    DWORD_VAL   date1;
    DWORD_VAL   date2;

    do
    {
        while (RCFGCALbits.RTCSYNC);

        RCFGCALbits.RTCPTR0 = 1;
        RCFGCALbits.RTCPTR1 = 1;
        date1.w[1] = RTCVAL;
        date1.w[0] = RTCVAL;

        RCFGCALbits.RTCPTR0 = 1;
        RCFGCALbits.RTCPTR1 = 1;
        date2.w[1] = RTCVAL;
        date2.w[0] = RTCVAL;

    } while (date1.Val != date2.Val);

    return date1.Val;
}
#endif


/****************************************************************************
  Function:
    DWORD   PIC24RTCCGetTime( void )

  Description:
    This routine reads the time from the RTCC module.

  Precondition:
    The RTCC module has been initialized.

  Parameters:
    None

  Returns:
    DWORD in the format <xx><HH><MM><SS>

  Remarks:
    To catch roll-over, we do two reads.  If the readings match, we return
    that value.  If the two do not match, we read again until we get two
    matching values.

    For the PIC32MX, we use library routines, which return the time in the
    PIC32MX format.
  ***************************************************************************/

#if defined( __C30__ )
DWORD   PIC24RTCCGetTime( void )
{
    DWORD_VAL   time1;
    DWORD_VAL   time2;

    do
    {
        while (RCFGCALbits.RTCSYNC);

        RCFGCALbits.RTCPTR0 = 1;
        RCFGCALbits.RTCPTR1 = 0;
        time1.w[1] = RTCVAL;
        time1.w[0] = RTCVAL;

        RCFGCALbits.RTCPTR0 = 1;
        RCFGCALbits.RTCPTR1 = 0;
        time2.w[1] = RTCVAL;
        time2.w[0] = RTCVAL;

    } while (time1.Val != time2.Val);

    return time1.Val;
}
#endif
/****************************************************************************
  Function:
    void PIC24RTCCSetDate( WORD xx_year, WORD month_day )

  Description:
    This routine sets the RTCC date to the specified value.


  Precondition:
    The RTCC module has been initialized.

  Parameters:
    WORD xx_year    - BCD year in the lower byte
    WORD month_day  - BCD month in the upper byte, BCD day in the lower byte

  Returns:
    None

  Remarks:
    For the PIC32MX, we use library routines.
  ***************************************************************************/

#if defined( __C30__ )
void PIC24RTCCSetDate( WORD xx_year, WORD month_day )
{
    UnlockRTCC();
    RCFGCALbits.RTCPTR0 = 1;
    RCFGCALbits.RTCPTR1 = 1;
    RTCVAL = xx_year;
    RTCVAL = month_day;
}
#endif


/****************************************************************************
  Function:
    void PIC24RTCCSetTime( WORD weekDay_hours, WORD minutes_seconds )

  Description:
    This routine sets the RTCC time to the specified value.

  Precondition:
    The RTCC module has been initialized.

  Parameters:
    WORD weekDay_hours      - BCD weekday in the upper byte, BCD hours in the
                                lower byte
    WORD minutes_seconds    - BCD minutes in the upper byte, BCD seconds in
                                the lower byte

  Returns:
    None

  Remarks:
    For the PIC32MX, we use library routines.
  ***************************************************************************/

#if defined( __C30__ )
void PIC24RTCCSetTime( WORD weekDay_hours, WORD minutes_seconds )
{
    UnlockRTCC();
    RCFGCALbits.RTCPTR0 = 1;
    RCFGCALbits.RTCPTR1 = 0;
    RTCVAL = weekDay_hours;
    RTCVAL = minutes_seconds;
}
#endif


/****************************************************************************
  Function:
    void PrintFileInformation( SearchRec searchRecord )

  Description:
    This function prints the file information that is contained in
    searchRecord.  Information printed is:
                <date> <time> [<DIR>] [<size>] <name>

  Precondition:
    None

  Parameters:
    SearchRec searchRecord  - File information

  Returns:
    None

  Remarks:
    The timestamp is assumed to be in the following format:
            Date format:    Bits 15-9:  Year (0 = 1980, 127 = 2107)
                            Bits 8-5:   Month (1 = January, 12 = December)
                            Bits 4-0:   Day (1 - 31)

            Time format:    Bits 15-11: Hours (0-23)
                            Bits 10-5:  Minutes (0-59)
                            Bits 4-0:   Seconds/2 (0-29)
  ***************************************************************************/

void PrintFileInformation( SearchRec searchRecord )
{
    char        buffer[20];

    // Display the file's date/time stamp.
    sprintf( buffer, "%04d-%02d-%02d ", ((((DWORD_VAL)(searchRecord.timestamp)).w[1] & 0xFE00) >> 9) + 1980,
                                         (((DWORD_VAL)(searchRecord.timestamp)).w[1] & 0x01E0) >> 5,
                                          ((DWORD_VAL)(searchRecord.timestamp)).w[1] & 0x001F );
    UART2PrintString( buffer );
    sprintf( buffer, "%02d:%02d:%02d ",  (((DWORD_VAL)(searchRecord.timestamp)).w[0] & 0xF800) >> 11,
                                         (((DWORD_VAL)(searchRecord.timestamp)).w[0] & 0x07E0) >> 5,
                                         (((DWORD_VAL)(searchRecord.timestamp)).w[0] & 0x001F) << 1 );
    UART2PrintString( buffer );

    // Display the file size.  If the file is actually a directory, display an indication.
    if (searchRecord.attributes & ATTR_DIRECTORY)
    {
        UART2PrintString( "<DIR>           " );
    }
    else
    {
        sprintf( buffer, "     %10ld ", ((DWORD_VAL)(searchRecord.filesize)).Val );
        UART2PrintString( buffer );
    }

    // Display the file name.
    UART2PrintString( searchRecord.filename );
    UART2PrintString( "\r\n" );
}
/****************************************************************************
  Function:
    void RedoCommandPrompt( void )

  Description:
    This function is called when the user either removes or inserts media.
    We want to let the user know right away that something has changed, so
    we change the command prompt immediately.  If the user is entering a
    command, we rebuild his command.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void RedoCommandPrompt( void )
{
    int i;

    UART2PrintString( "\r\n" );
    if (volume.valid)
    {
        UART2PrintString( volume.label );
        //UART2PutChar( ':' );
        UART2PrintString( ":\\" );
    }
    UART2PrintString( "> " );

    if (commandInfo.reading)
    {
        for (i = 0; i < commandInfo.index; i++)
        {
            UART2PutChar( commandInfo.buffer[i] );
        }    
    }
}


/****************************************************************************
  Function:
    void ReplaceCommandLine( void )

  Description:
    This function is called when the user presses the arrow keys to scroll
    through previous commands.  The function erases the current command line
    and replaces it with the previous command indicated by
    commandBuffer.showing.

  Precondition:
    The buffer of old commands is valid.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/

void ReplaceCommandLine( void )
{
    BYTE    i;
    BYTE    lineLength;
    char    oneChar;

    EraseCommandLine();

    lineLength = strlen( commandBuffer.lines[commandBuffer.showing] );
    for (i=0; i<lineLength; i++)
    {
        oneChar = commandBuffer.lines[commandBuffer.showing][i];
        UART2PutChar( oneChar );
        commandInfo.buffer[commandInfo.index++] = oneChar;
    }
}

/****************************************************************************
  Function:
    void WriteOneBuffer( FSFILE *fptr, BYTE *data, WORD size )

  Description:
    This function writes one log buffer to the indicated file.  It then
    advances the pointer to the current buffer to write.

  Precondition:
    None

  Parameters:
    FSFILE *fptr    - Pointer to an open file
    BYTE *data      - Pointer to data to write
    WORD size       - How many bytes of data to write

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/

void WriteOneBuffer( FSFILE *fptr, BYTE *data, WORD size )
{
    if (FSfwrite( data, 1, size, fptr) != size)
    {
        UART2PrintString( "! Error writing log file\r\n" );
    }
    logData[logBufferWriting].bufferFull    = FALSE;
    logData[logBufferWriting].index         = 0;

    logBufferWriting++;
    if (logBufferWriting >= NUM_LOG_BUFFERS)
    {
        logBufferWriting = 0;
    }
}

/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                    void *data, DWORD size )

  Description:
    This routine handles USB events sent from the USB Embedded Host stack.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of the USB device generating the event
    USB_EVENT event - Event that has occurred
    void *data      - Pointer to the data associated with the event
    DWORD size      - Size of the data pointed to by *data

  Return Values:
    TRUE    - The event was handled successfully
    FALSE   - The even was not handled successfully

  Remarks:
    We will default to returning TRUE for unknown events, and let operation
    proceed.  Other applications may wish to return FALSE, since we are not
    really handling the event.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // We will let everything attach.
            return TRUE;
            break;

        case EVENT_VBUS_RELEASE_POWER:
            // We are not monitoring power allocation, so we have
            // nothing to update.
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
        case EVENT_UNSUPPORTED_DEVICE:
        case EVENT_CANNOT_ENUMERATE:
        case EVENT_CLIENT_INIT_ERROR:
        case EVENT_OUT_OF_MEMORY:
        case EVENT_UNSPECIFIED_ERROR: // This should never occur
            //usbErrorCode = USBHostDeviceStatus(1);

            // Shut down the USB.
            USBHostShutdown();
            //screenState = SCREEN_DISPLAY_FLASH_ERROR;
            return TRUE;
            break;

        default:
            break;
    }

    return TRUE;
}

/****************************************************************************
  Function:
    void	InitializeUSBMiniA( void )

  Description:
    This function initialize USB MiniA Port
  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void	InitializeUSBMiniA( void )
{
	TRISBbits.TRISB5 = 0;
	_RB5 = 1;
	TRISDbits.TRISD9 = 0;
	PORTDbits.RD9 = 0;
	Nop();
	TRISDbits.TRISD10 = 0;
	PORTDbits.RD10 = 0;
	Nop();

	return;
}

/****************************************************************************
  Function:
    void	CloseUSBMiniA( void )

  Description:
    This function initialize USB MiniA Port
  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void CloseUSBMiniA( void )
{
	TRISDbits.TRISD9 = 1;
	Nop();
	TRISDbits.TRISD10 = 1;

	return;
}

/****************************************************************************
  Function:
    void	InitializeUSBMiniB( void )

  Description:
    This function initialize USB MiniB Port
  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void	InitializeUSBMiniB( void )
{
	TRISDbits.TRISD9 = 0;
	PORTDbits.RD9 = 0;
	Nop();
	TRISDbits.TRISD10 = 0;
	PORTDbits.RD10 = 1;
	Nop();

	return;
}

/****************************************************************************
  Function:
    void UnlockRTCC( void )

  Description:
    This function unlocks the RTCC so we can write a value to it.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    For the PIC32MX, we use library routines.
  ***************************************************************************/

#define RTCC_INTERRUPT_REGISTER IEC3
#define RTCC_INTERRUPT_VALUE    0x2000

#if defined( __C30__ )
void UnlockRTCC( void )
{
    BOOL interruptsWereOn;

    interruptsWereOn = FALSE;
    if ((RTCC_INTERRUPT_REGISTER & RTCC_INTERRUPT_VALUE) == RTCC_INTERRUPT_VALUE)
    {
        interruptsWereOn = TRUE;
        RTCC_INTERRUPT_REGISTER &= ~RTCC_INTERRUPT_VALUE;
    }

    // Unlock the RTCC module
    __asm__ ("mov #NVMKEY,W0");
    __asm__ ("mov #0x55,W1");
    __asm__ ("mov #0xAA,W2");
    __asm__ ("mov W1,[W0]");
    __asm__ ("nop");
    __asm__ ("mov W2,[W0]");
    __asm__ ("bset RCFGCAL,#13");
    __asm__ ("nop");
    __asm__ ("nop");

    if (interruptsWereOn)
    {
        RTCC_INTERRUPT_REGISTER |= RTCC_INTERRUPT_VALUE;
    }
}
#endif

/****************************************************************************
  Function:
    void __attribute__((interrupt, shadow, auto_psv)) _T4Interrupt(void)

  Description:
    This function updates the tick count and calls ReadCTMU() to monitor the
    touchpads.

  Precondition:
    Timer 4 and the Timer 4 interrupt must be enabled in order for
                    this function to execute.  CTMUInit() must be called before
                Timer 4 and the Timer 4 interrupt are enabled.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
#if defined (__C30__)
void __attribute__((interrupt, shadow, auto_psv)) _T4Interrupt(void)
#elif defined (__C32__)
void __ISR(_TIMER_4_VECTOR, ipl7) _T4Interrupt(void)
#endif
{
	#if defined (__C30__)
    IFS1bits.T4IF = 0;    // Clear flag
	ReadButton();
	#elif defined (__C32__)
    if (IFS0 & PIC32MX_TIMER4_INTERRUPT)
    {
        // Clear the interrupt flag
    	mT4ClearIntFlag();
		ReadButton();
    }
	#endif

	return;
}

/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{
    #if (defined(__18CXX) & !defined(PIC18F87J50_PIM))
        ADCON1 |= 0x0F;                 // Default all pins to digital
    #elif defined(__C30__)
        AD1PCFG = 0xFFFF;
    #elif !defined(PIC18F87J50_PIM)
        AD1PCFG = 0xFFFF;
    #endif

//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif

    //********* Initialize Peripheral Pin Select (PPS) *************************
    //  This section only pertains to devices that have the PPS capabilities.
    //    When migrating code into an application, please verify that the PPS
    //    setting is correct for the port pins that are used in the application.
    //Initialize the SPI
	if(usb_sd_card == 1)
	{
		InitializeSDCardReader();
    	MDD_SDSPI_InitIO();
	}

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem


/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void)
{   
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))
	{
		return;
	}

    MSDTasks();    
}//end ProcessIO




// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *00000000000000000000000000000000
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

    #if defined(__C30__)
    #if 0
        U1EIR = 0xFFFF;
        U1IR = 0xFFFF;
        U1OTGIR = 0xFFFF;
        IFS5bits.USB1IF = 0;
        IEC5bits.USB1IE = 1;
        U1OTGIEbits.ACTVIE = 1;
        U1OTGIRbits.ACTVIF = 1;
        Sleep();
    #endif
    #endif
}

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
}

/********************************************************************
 Function:        void USBCB_SOF_Handler(void)

 Description:     The USB host sends out a SOF packet to full-speed
                  devices every 1 ms. This interrupt may be useful
                  for isochronous pipes. End designers should
                  implement callback routine as necessary.

 PreCondition:    None
 
 Parameters:      None
 
 Return Values:   None
 
 Remarks:         None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckMSDRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    #if (MSD_DATA_IN_EP == MSD_DATA_OUT_EP)
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    #else
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
        USBEnableEndpoint(MSD_DATA_OUT_EP,USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    #endif

    USBMSDInit();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function should only be called when:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()
 *
 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at lest 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    USBResumeControl = 1;                // Start RESUME signaling
    
    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}

/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER:
            Nop();
            break;
        default:
            break;
    }      
    return TRUE; 
}

/****************************************************************************
  Function:
    void InitializeSDCardReader( void )

  Description:
    This function initializes the SPI SD Card

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void InitializeSDCardReader( void )
{
//SPI SD Card initialize
	InitializeSPISDCard();

//enable a pull-up for the card detect, just in case the SD-Card isn't attached
//  then lets have a pull-up to make sure we don't think it is there.
	#if defined (__C30__)
    CNPU2bits.CN30PUE = 1;
	#endif 
}

/****************************************************************************
  Function:
    void SDCardReaderShutdown( void )

  Description:
    This function close the SPI SD Card

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void SDCardReaderShutdown( void )
{
//SPI SD Card change directions
    SPICLOCK = INPUT; 				//OUTPUT;
    SPIOUT = INPUT;					//OUTPUT;
    SPIIN = OUTPUT;					//INPUT;

//Disable USB MiniB
	TRISDbits.TRISD9 = 1;
	TRISDbits.TRISD10 = 1;

//Close SPI-SD Card
	MDD_SDSPI_ShutdownMedia();

//Disable USB Interrupt
	USBMaskInterrupts();
}

/****************************************************************************
  Function:
    void	SDCardReaderInternalFlashFunction()

  Description:
    This function is USB To UART or Internal Flash

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
  ***************************************************************************/
void	SDCardReaderInternalFlashFunction()
{
	BYTE            mediaPresentNow;
	BYTE            mediaPresentBefore = 0;
	int				firstTime = 0;

//Enable MiniB
	InitializeUSBMiniB();

    InitializeSystem();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

    while(1)
    {
        #if defined(USB_POLLING)
		// Check bus status and service USB interrupts.
        USBDeviceTasks(); 
        #endif

        ProcessIO();

		ButtonsMsg();
		if(buttonPress == 3)
		{
			if( usb_sd_card ==1 )
			{
				usb_sd_card = 0;
				SDCardReaderShutdown();
			}
			if( usb_flash == 1 )
			{
				usb_flash = 0;
				//Disable USB MiniB
				TRISDbits.TRISD9 = 1;
				TRISDbits.TRISD10 = 1;

				//Disable USB Interrupt
				USBMaskInterrupts();
			}
			break;
		}

		if( usb_sd_card == 1)
		{
			mediaPresentNow = MDD_SDSPI_MediaDetect();
			if( (firstTime == 0) && (mediaPresentNow == 0))
			{
				showStorageInformation(0,0);
			}
			if( mediaPresentNow != mediaPresentBefore )
			{
				if( mediaPresentNow )
				{
					firstTime = 1;
					showStorageInformation(1,0);
				}
				else
				{
					showStorageInformation(0,0);
				}
				mediaPresentBefore = mediaPresentNow;
			}
		}

    }//end while

	return;
}

/****************************************************************************
  Function:
    void _USB1Interrupt( void )

  Summary:
    This is the interrupt service routine for the USB interrupt.

  Description:
	USB Interrupts.

  Precondition:

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
#if defined(__C30__)
void __attribute__((__interrupt__, auto_psv)) _USB1Interrupt( void )
#elif defined(__PIC32MX__)
#pragma interrupt _USB1Interrupt ipl4 vector 45
void _USB1Interrupt( void )
#else
    #error Cannot define timer interrupt vector.
#endif
{
	if((usb_sd_card == 1)||(usb_flash == 1))			//SD Card Reader
	{
		USB_Device_Interrupt();
	}
	if(usb_master == 1)			//USB To UART
	{
		USB_Master_Interrupt();
	}
}

/****************************************************************************
  Function:
     void InitializeClock( void )

  Description:
    This function initializes the tick timer.  It configures and starts the
    timer, and enables the timer interrupt.  We are using Timer 3 so we can
    also trigger an A/D conversion when the timer rolls over.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
void    InitializeClock( void )
{
	RtccInit();
	RtccSetDate( DEFAULT_DATE );
	RtccSetTime( DEFAULT_TIME );
	RtccEnable();
	mRtccWrEnable();
  	while (RtccEnable() != RTCC_CLK_ON); // Make sure the RTCC is counting.
    mRtccWrDisable();

	return;
}

/*****************************************************************************
 * Function: int RTCCProcessEvents(void)
 *
 * Preconditions: RTCCInit must be called before.
 *
 * Overview: The function grabs the current time from the RTCC and translate
 * it into strings.
 *
 * Input: None.
 *
 * Output: It update time and date strings  _rtcc_str
 *
 *****************************************************************************/
int RTCCProcessEvents(void)
{
	currentTime.l = RtccGetTime();
	if( previousMinute != currentTime.min)
	{
		previousMinute = currentTime.min;

		_rtcc_str[11] = (currentTime.hour >> 4) + '0';
		_rtcc_str[12] = (currentTime.hour & 0xF) + '0';				//Hour:10
		_rtcc_str[13] = ':';
		_rtcc_str[14] = (currentTime.min >> 4) + '0';
		_rtcc_str[15] = (currentTime.min & 0xF) + '0';				//Minute:10

		currentDate.l   = RtccGetDate();
		_rtcc_str[0] = '2';
		_rtcc_str[1] = '0';
        _rtcc_str[2] = (currentDate.year >> 4) + '0';
        _rtcc_str[3] = (currentDate.year & 0xF) + '0';				//Year:2010
		_rtcc_str[4] = '/';
		_rtcc_str[5] = (currentDate.mon >> 4) + '0';
		_rtcc_str[6] = (currentDate.mon & 0xF) + '0';		//Month:01
		_rtcc_str[7] = '/';
        _rtcc_str[8] = (currentDate.mday >> 4) + '0';
        _rtcc_str[9] = (currentDate.mday & 0xF) + '0';				//Day:01
		_rtcc_str[10] = ' ';
	
		return 1;	
	}
	else
	{
		return 0;
	}	
}

