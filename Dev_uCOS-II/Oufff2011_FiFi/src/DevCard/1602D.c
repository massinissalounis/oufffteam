/*****************************************************************************
 *  Module for Sure Electronics LCD Graphics Library
 *  1602D LCD controller driver  
 *****************************************************************************
 * FileName:        1602D.c
 * Dependencies:    p24Fxxxx.h
 * Processor:       PIC24
 * Compiler:       	MPLAB C30
 * Linker:          MPLAB LINK30
 * Company:         Sure Electronics
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vivian Zhao  		12/01/09	Original
 *****************************************************************************/
#include "1602D.h"

/*********************************************************************
* Function:  void  DelayMs(int time)
*
* PreCondition: none
*
* Input: time - delay in ms
*
* Output: none
*
* Side Effects: none
*
* Overview: delays execution on time specified in ms
*
* Note: 
*
********************************************************************/
#define DELAY_1MS (32000/9)  //GetSystemClock() == 32000000

void  DelayMs(int time)
{
	unsigned delay;
	while(time--)
		for(delay=0; delay<DELAY_1MS; delay++);	
}

/*********************************************************************
* Function:  void  DelayMs(int time)
*
* PreCondition: none
*
* Input: time - delay in ms
*
* Output: none
*
* Side Effects: none
*
* Overview: delays execution on time specified in ms
*
* Note: 
*
********************************************************************/
#define DELAY_300NS 1  //GetSystemClock() == 32000000

void  Delay300Ns(int time)
{
	unsigned delay;
	while(time--)
		for(delay=0; delay<DELAY_300NS; delay++) Nop();	
}

/*********************************************************************
* Function:  void LightLCD(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: light LCD
*
* Note: none
*
********************************************************************/
void LightLCD(void)
{	
	TRIS_LCD_LIGHT=0;
	TRIS_LCD_COMPARE=0;
	TRIS_LCD_POWER=0;
	LCD_LIGHT=1;
	Nop();Nop();		//Time Delay,Must Be,if < 2 Nop(),cannot light LCD
	LCD_COMPARE=1;
	Nop();Nop();		//Time Delay,Must Be,if < 2 Nop(),cannot light LCD from "USB UART Port"
	LCD_POWER=1;

	return;
}

/*********************************************************************
* Function:  void InitLCDPins(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: resets LCD, initializes PMP
*
* Note: none
*
********************************************************************/
void InitLCDPins(void)
{	
// Set pins Output Direction
	TRIS_DATA_PORT=0;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD11 = 0;
	TRISBbits.TRISB15 = 0;

//	Endable 
	E_PIN=0;
	Delay300Ns(3);
	E_PIN=1;
}

/*********************************************************************
* Macros: void WriteAdress(unsigned char adr)
*
* Overview: Write Adress word to the display controller. A delay
*			is inserted at the end to meet the controller requirements
*			on selected commands.
*
* PreCondition: none
*
* Input: address
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
//#define WriteAdress(adr) 	LCD_check_busy();TRIS_DATA_PORT=0x00;RS_PIN=0;RW_PIN=0;Delay300Ns(2);E_PIN=1;Delay300Ns(1);DATA_PORT=(adr | 0x80);Delay300Ns(1);E_PIN=0;
void WriteAdress(unsigned char adr)
{
	LCD_check_busy();
	TRIS_DATA_PORT=0x00;

	RS_PIN=0;
	RW_PIN=0;
	Delay300Ns(2);

	E_PIN=1;
	Delay300Ns(1);
	DATA_PORT=(adr | 0x80);
	Delay300Ns(1);
	E_PIN=0;

	return;
}

/*********************************************************************
* Function:  void InitByInstru(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Initialize LCD By Commands
*
* Note: 
*
********************************************************************/
void InitByInstru(void)
{
    
   	DelayMs(4);Delay300Ns(4);	//Delay more than 4.1ms
	WriteCommand(0b00111111);
    Delay300Ns(334);			//Delay more than 100us			  
	WriteCommand(0b00111111);
    Delay300Ns(134);			//Delay more than 40us
	WriteCommand(0b00111111);

	LCD_check_busy();
	WriteCommand(0b00111011); //Function Set:8-bit mode,two lines,5*7 character
	LCD_check_busy();
	WriteCommand(0b00001100); //Display Method Set:display on,cursor off,blink off
	LCD_check_busy();
	WriteCommand(0b00000001); //Clear display
	LCD_check_busy();
	WriteCommand(0b00000011); //Return home:AC=0
	LCD_check_busy();
	WriteCommand(0b00000110); //Entry Mode Set:Set entry mode,increment adress by 1
	                           // and shift cursor to the right at the
	                           // time of write to DD/CGRAM.Display
	                           // is not shifted
}



/*********************************************************************
* Macros: void WriteCommand(unsigned char cmd)
*
* Overview: Writes command word to the display controller. A delay
*			is inserted at the end to meet the controller requirements
*			on selected commands.
*
* PreCondition: none
*
* Input: command
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
//#define WriteCommand(cmd)		LCD_check_busy();_RB15=0;_RD4=0;Nop();_RD5=1;TRISE=0x00;LATE=cmd;Nop();_RD5=0;
//#define WriteCommand(cmd) 	LCD_check_busy();TRIS_DATA_PORT=0x00;RS_PIN=0;RW_PIN=0;Delay300Ns(2);E_PIN=1;Delay300Ns(1);DATA_PORT=cmd;Delay300Ns(1);E_PIN=0;

void WriteCommand(unsigned char cmd)
{
	LCD_check_busy();
	TRIS_DATA_PORT=0x00;

	RS_PIN=0;
	RW_PIN=0;
	Delay300Ns(2);

	E_PIN=1;
	Delay300Ns(1);
	DATA_PORT=cmd;
	Delay300Ns(1);
	E_PIN=0;

	return;
}


/*********************************************************************
* Macros:  void WriteData(unsigned char data)
*
* Overview: Writes data.
*
* PreCondition: none
*
* Input: writeByte - Data byte to be written.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
//#define WriteData(writeByte)	LCD_check_busy();TRISE=0x00;_RB15=1;_RD4=0;LATE=writeByte;Nop();_RD5=1;Nop();_RD5=0;
//#define WriteData(writeByte) 	LCD_check_busy();TRIS_DATA_PORT=0x00;RS_PIN=1;RW_PIN=0;Delay300Ns(2);E_PIN=1;Delay300Ns(1);DATA_PORT=data;Delay300Ns(1);E_PIN=0;

void WriteData(unsigned char data)
{
	LCD_check_busy();
	TRIS_DATA_PORT=0x00;

	RS_PIN=1;
	RW_PIN=0;
	Delay300Ns(2);

	E_PIN=1;
	Delay300Ns(1);
	DATA_PORT=data;
	Delay300Ns(1);
	E_PIN=0;

	return;
}


/*********************************************************************
* Macros:  unsigned char ReadCommand(void)
*
* Overview: Reads command word to the display controller. A delay
*			is inserted at the end to meet the controller requirements
*			on selected commands.
*
* PreCondition: none
*
* Input: command
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
//#define ReadCommand(readByte)		_RB15=0;_RD4=1;Nop();_RD5=1;Nop();TRISE=0xff;_RD5=0;readByte=PORTE;
//#define ReadCommand(readByte) 	TRIS_DATA_PORT=0xff;RS_PIN=0;RW_PIN=1;Delay300Ns(2);E_PIN=1;Delay300Ns(1);cmd=DATA_PORT;Delay300Ns(1);E_PIN=0;

unsigned char ReadCommand(void)
{
	unsigned char cmd=0;

	TRIS_DATA_PORT=0xff;

	RS_PIN=0;
	RW_PIN=1;
	Delay300Ns(2);

	E_PIN=1;
	Delay300Ns(1);
	cmd=DATA_PORT;
	Delay300Ns(1);
	E_PIN=0;

	return cmd;
}


/*********************************************************************
* Macros:  unsigned char ReadData(void)
*
* Overview: Reads a byte from the display buffer. This assumes that the 
*			page value, lower and higher column address pointers are already set.
*
* PreCondition: none
*
* Input: none.
*
* Output: ReadByte - data read from the display buffer.
*
* Side Effects: none
*
********************************************************************/
//#define ReadData(readByte)			LCD_check_busy();_RB15=1;_RD4=1;Nop();_RD5=1;Nop();TRISE=0xff;_RD5=0;readByte=PORTE;
//#define ReadData(readByte) 	LCD_check_busy();RS_PIN=1;RW_PIN=1;Delay300Ns(2);E_PIN=1;Delay300Ns(1);TRIS_DATA_PORT=0xff;E_PIN=0;data=DATA_PORT;

unsigned char ReadData(void)
{
	unsigned char data;
	LCD_check_busy();

	RS_PIN=1;
	RW_PIN=1;
	Delay300Ns(2);

	E_PIN=1;
	Delay300Ns(1);
	TRIS_DATA_PORT=0xff;
	E_PIN=0;
	data=DATA_PORT;

	return data;
}

/*********************************************************************
* Macros:  void WriteStr(const char *string,int cnt)
*
* Overview: Writes strings.
*
* PreCondition: none
*
* Input: string, string length.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void WriteStr(const char *string,int cnt)
{
	while(cnt--)
	{
		LCD_check_busy();
		WriteData(*string);
		string++;
	} 
}
	
/*********************************************************************
* Macros:  void ReadStr(const char *string,int cnt)
*
* Overview: Reads strings.
*
* PreCondition: none
*
* Input: string, string length.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void ReadStr(unsigned char *string,int cnt)
{
	while(cnt--)
	{
		LCD_check_busy();
		*string=ReadData();
		string++;
	}
	return;
}

/*********************************************************************
* Function: void LCD_check_busy(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Check if LCD is busy 
*
* Note: none
*
********************************************************************/
void LCD_check_busy(void)
{
	unsigned char lcd_status;
	do{ 
		lcd_status = ReadCommand();
	}while(lcd_status & 0x80);

	lcd_status=0;
	
	return;
}

/*********************************************************************
* Function: int Set_Line_Information(int line,const char offset,const char *string,const int num)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Set Line Information
*
* Note: none
*
********************************************************************/
int Set_Line_Information(int line,const char offset,const char *string,const int num)
{
	char adr=0;
	if(line == 1)
		adr+=offset;
	else if(line == 2)
		adr+=offset+0x40;
	else
		return 1;

	LCD_check_busy();
	WriteAdress(adr);//set display adress at 0x00,Line One
	WriteStr(string,num);

	return 0;	
}

/*********************************************************************
* Function: int Read_Line_Information(int line,char *string,int num)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: Set Line Information
*
* Note: none
*
********************************************************************/
/*
int Read_Line_Information(int line,char *string,int num)
{
	char adr=0;
	if(line == 1)
		adr=0x00;
	else if(line == 2)
		adr=0x40;
	else
		return 1;

	LCD_check_busy();
	WriteAdress(adr);//set display adress at 0x00,Line One
	ReadStr(string,num);

	return 0;	
}
*/
