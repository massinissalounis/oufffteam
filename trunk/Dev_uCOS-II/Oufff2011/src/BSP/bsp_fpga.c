/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                              (c) Copyright 2006, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                          Board Support Package
*                                               Oufff TEAM
*                                               O'CORE
*********************************************************************************************************
*/

#include "AppIncludes.h"

// AX12 UART CONTROL FUNCTIONS

void AX12_UART_Init (void)
{
 // Perform the initialization of UART8AX12 module
 // For normal operation, software initialization needs to do the following operations:
 // · Initialize the LCR register (with bit 7 = 1)
 // · Initialize the Baud Rate Divisor Registers to set the desired transfer rate
 // · Reinitialize the LCR register (with bit 7 = 0)
 // · Set the FIFO trigger level (in the FCR register)
 // · Enable the desired interrupts

	PMP_Write(AX12_UART_LCR, 0x83); // Ob1OOOOO11
	PMP_Write(AX12_UART_DLL, 0x0B);
	PMP_Write(AX12_UART_DLM, 0x00);
	PMP_Write(AX12_UART_LCR, 0x03); // Ob0OOOOO11
//	PMP_Write(AX12_UART_FCR, 0x00);
}

CPU_INT08U AX12_UART_Read_Status (void)
{
	CPU_INT08U value;
	value = PMP_Read(AX12_UART_STATUS);
	return value;
}

CPU_INT08U AX12_UART_Data_Ready (void)
{
	CPU_INT08U status;	
	status = PMP_Read(AX12_UART_STATUS);
	if( (status & AX12_UART_MASK_DATA_READY)==AX12_UART_MASK_DATA_READY) return 1;
    else return 0;    
}

CPU_INT08U AX12_UART_Data_Sent (void)
{
	CPU_INT08U status;	
	status = PMP_Read(AX12_UART_STATUS);
	if( (status & AX12_UART_MASK_DATA_SENT)==AX12_UART_MASK_DATA_SENT) return 1;
    else return 0;    
}

CPU_INT08U AX12_UART_Read (void)
{
	CPU_INT08U data;
	data = PMP_Read(AX12_UART_FIFO);
	return data;
}

void AX12_UART_Write (CPU_INT08U data)
{
	PMP_Write(AX12_UART_FIFO, data);
}

float gg;
CPU_INT08U AX12_Read_Return_Packet()
{
	CPU_INT08U timeout;
	CPU_INT08U id=0, length=0, error=0xFF, checksum=0, trash=0;

	char * buffer_ptr;
	char uart_buffer[8];

	timeout=250; // OxFF
	while((AX12_UART_Data_Ready()!=1) && timeout>0) { timeout--; BSP_Dly(100); }
	if(timeout==0) return 0xFF;
	else trash=AX12_UART_Read();

	timeout=250; // OxFF
	while((AX12_UART_Data_Ready()!=1) && timeout>0)	{ timeout--; BSP_Dly(100); }
	if(timeout==0) return 0xFF;
	else trash=AX12_UART_Read();

	timeout=250; // ID
	while((AX12_UART_Data_Ready()!=1) && timeout>0)	{ timeout--; BSP_Dly(100); }
	if(timeout==0) return 0xFF;
	else id=AX12_UART_Read();
	
	timeout=250; // LENGTH
	while((AX12_UART_Data_Ready()!=1) && timeout>0)	{ timeout--; BSP_Dly(100); }
	if(timeout==0) return 0xFF;
	else length=AX12_UART_Read();

	timeout=250; // ERROR
	while((AX12_UART_Data_Ready()!=1) && timeout>0)	{ timeout--; BSP_Dly(100); }
	if(timeout==0) return 0xFF;
	else error=AX12_UART_Read();

	timeout=250; // CHECKSUM
	while((AX12_UART_Data_Ready()!=1) && timeout>0)	{ timeout--; BSP_Dly(100); }
	if(timeout==0) return 0xFF;
	else checksum=AX12_UART_Read();

	return error;
}

// AX12 CONTROL FUNCTIONS

CPU_INT08U AX12_Write_Position (CPU_INT08U ax12_id, CPU_INT08U setpoint_high, CPU_INT08U setpoint_low)
{
	CPU_INT16U checksum;
	CPU_INT08U length=5;
	CPU_INT08U status=0xAA;

	checksum = ~(ax12_id + length + AX12_CMD_WRITE_DATA + AX12_REG_GOAL_POSITION + setpoint_low + setpoint_high);

    AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFF);
	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_WRITE_DATA); // INSTRUCTION
	AX12_UART_Write (AX12_REG_GOAL_POSITION); // Reg address
	AX12_UART_Write (setpoint_low);
	AX12_UART_Write (setpoint_high);
	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	status=AX12_Read_Return_Packet();

	return status;
}

void AX12_Write_Position_Sync (CPU_INT08U ax12_id1, CPU_INT08U ax12_id2, CPU_INT08U setpoint1_high, CPU_INT08U setpoint1_low, CPU_INT08U setpoint2_high, CPU_INT08U setpoint2_low)
{
	CPU_INT16U checksum;
	CPU_INT08U L=2;
	CPU_INT08U length=(2*(L+1))+4;

	checksum = ~(0xFE + length + AX12_CMD_SYNC_WRITE + AX12_REG_GOAL_POSITION + L + ax12_id1 + setpoint1_low + setpoint1_high + ax12_id2 + setpoint2_low + setpoint2_high);

    AX12_UART_Write (0xFF); 
	AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFE); // ID BROADCAST
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_SYNC_WRITE); // INSTRUCTION

	AX12_UART_Write (AX12_REG_GOAL_POSITION); // Starting address where the data is written
	AX12_UART_Write (L); // LENGTH PER AX

	AX12_UART_Write (ax12_id1); // ID1
	AX12_UART_Write (setpoint1_low);
	AX12_UART_Write (setpoint1_high);

	AX12_UART_Write (ax12_id2); // ID2
	AX12_UART_Write (setpoint2_low);
	AX12_UART_Write (setpoint2_high);

	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	while(AX12_UART_Data_Sent()!=1);
}

CPU_INT08U AX12_Write_Reg (CPU_INT08U ax12_id, CPU_INT08U reg_address, CPU_INT08U data)
{
	CPU_INT16U checksum;
	CPU_INT08U length=4;
	CPU_INT08U status=0xAA;

	checksum = ~(ax12_id + length + AX12_CMD_WRITE_DATA + reg_address + data);

    AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFF);
	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_WRITE_DATA); // INSTRUCTION
	AX12_UART_Write (reg_address); // Reg address
	AX12_UART_Write (data);
	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	status=AX12_Read_Return_Packet();

	return status;
}

CPU_INT08U AX12_Read_status (CPU_INT08U ax12_id)
{
	CPU_INT08U i;
	CPU_INT08U status=0xFF;

	// Send a PING command to the AX12
    AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFF);
	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (0x02); // LENGTH
	AX12_UART_Write (AX12_CMD_PING); // INSTRUCTION
	AX12_UART_Write (0xFB); // CHECKSUM

	status=AX12_Read_Return_Packet();

	return status;
}

void HOLDER_Open(void)
{
	AX12_Write_Position_Sync(AX12_FL_ID, AX12_FR_ID, 0x01, 0x9A, 0x02, 0x6C);
//	AX12_Write_Position(AX12_FL_ID,0x01,0x9A);
//	AX12_Write_Position(AX12_FR_ID,0x02,0x6C);
}

void HOLDER_Hold(void)
{
	AX12_Write_Position_Sync(AX12_FL_ID, AX12_FR_ID, 0x02, 0x24, 0x01, 0xD5);
//	AX12_Write_Position(AX12_FL_ID,0x02,0x24);
//	AX12_Write_Position(AX12_FR_ID,0x01,0xD5);
}

void HOLDER_Close(void)
{
	AX12_Write_Position_Sync(AX12_FL_ID, AX12_FR_ID, 0x03, 0x0C, 0x00, 0xE6);
}

void HOLDER_Open_Left_Only(void)
{
	AX12_Write_Position_Sync(AX12_FL_ID, AX12_FR_ID, 0x01, 0x9A, 0x00, 0xE6);
}

void HOLDER_Open_Right_Only(void)
{
	AX12_Write_Position_Sync(AX12_FL_ID, AX12_FR_ID, 0x03, 0x0C, 0x02, 0x6C);
}

void HOLDER_Level_Low(void)
{
	AX12_Write_Position_Sync(AX12_TL_ID, AX12_TR_ID, 0x00, 0x32, 0x03, 0xFF);
}

void HOLDER_Level_Middle(void)
{
	AX12_Write_Position_Sync(AX12_TL_ID, AX12_TR_ID, 0x02, 0x00, 0x02, 0x00);
}

void HOLDER_Level_High(void)
{
	AX12_Write_Position_Sync(AX12_TL_ID, AX12_TR_ID, 0x03, 0xFF, 0x00, 0x32);
}

void HOLDER_Init(void)
{
	// ALARM Shutdown
//	AX12_Write_Reg(AX12_FL_ID, AX12_REG_ALARM_SHUTDOWN, 0x04);
//	AX12_Write_Reg(AX12_FR_ID, AX12_REG_ALARM_SHUTDOWN, 0x04);
////	AX12_Write_Reg(AX12_TL_ID, AX12_REG_ALARM_SHUTDOWN, 0x00);
//	AX12_Write_Reg(AX12_TR_ID, AX12_REG_ALARM_SHUTDOWN, 0x04);

//	AX12_Write_Reg(AX12_FL_ID, AX12_REG_TEMPERATURE_LIMIT, 0x55);
//	AX12_Write_Reg(AX12_FR_ID, AX12_REG_TEMPERATURE_LIMIT, 0x55);
////	AX12_Write_Reg(AX12_TL_ID, AX12_REG_TEMPERATURE_LIMIT, 0x55);
//	AX12_Write_Reg(AX12_TR_ID, AX12_REG_TEMPERATURE_LIMIT, 0x55);

	// HOLDER Init
	HOLDER_Level_Low();
	HOLDER_Close();
}

void QUAD_Latch (void)
{
	PMP_Write(QUAD_LATCH_REGISTER,0xFF); // Latch quadrature counters
}

void QUAD_Wait_for_Latch (void)
{
	while(PMP_Read(QUAD_LATCH_REGISTER)!=0x00);
}

CPU_INT16S QUADD_Read (void)
{
	CPU_INT16S value;
	value = PMP_Read(QUADD_HI_REGISTER) <<8;
	value = value | PMP_Read(QUADD_LO_REGISTER);
	return value;
}

CPU_INT16S QUADG_Read (void)
{
	CPU_INT16S value;
	value = PMP_Read(QUADG_HI_REGISTER) <<8;
	value = value | PMP_Read(QUADG_LO_REGISTER);
	return value;
}

//Inter couleur transféré sur le pic
/*CPU_INT08U COLOR_Read (void)
{
	CPU_INT08U value;
	value = PMP_Read(GPIO_REGISTER);
	return value;
}*/

void BSPFPGA_Reset(void)
{

	char test;

	PMP_Write(RESET_REGISTER,0xFF);
	PMP_Write(RESET_REGISTER,0x00);
	PMP_Write(LED_REGISTER,0x01);

	AX12_UART_Init ();

//	HOLDER_Init();

/*	HOLDER_Open();
	BSP_Dly(100000);
	HOLDER_Close();

	BSP_Dly(200000);
	HOLDER_Level_Middle();

	BSP_Dly(200000);
	HOLDER_Level_Low();

	BSP_Dly(200000);
	HOLDER_Level_High();

	BSP_Dly(200000);
	HOLDER_Level_Middle();

	BSP_Dly(200000);
	HOLDER_Level_Low();

	BSP_Dly(200000);
	HOLDER_Open();*/
}
