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

CPU_INT08U AX12_UART_Data_Sent (void)
{
	CPU_INT08U status;	
	status = PMP_Read(AX12_UART_STATUS);
	if( (status & AX12_UART_MASK_DATA_SENT)==AX12_UART_MASK_DATA_SENT) return 1;
    else return 0;    
}

void AX12_UART_Write (CPU_INT08U data)
{
	PMP_Write(AX12_UART_FIFO, data);
}

// AX12 CONTROL FUNCTIONS

void AX12_Dual_Write_Position_Sync (CPU_INT08U ax12_id1, CPU_INT08U ax12_id2, CPU_INT08U setpoint1_high, CPU_INT08U setpoint1_low, CPU_INT08U setpoint2_high, CPU_INT08U setpoint2_low)
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

void AX12_Write_Position_Sync (CPU_INT08U ax12_id, CPU_INT08U setpoint_high, CPU_INT08U setpoint_low)
{
	CPU_INT16U checksum;
	CPU_INT08U L=2;
	CPU_INT08U length=(L+1)+4;

	checksum = ~(0xFE + length + AX12_CMD_SYNC_WRITE + AX12_REG_GOAL_POSITION + L + ax12_id + setpoint_low + setpoint_high);

    AX12_UART_Write (0xFF); 
	AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFE); // ID BROADCAST
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_SYNC_WRITE); // INSTRUCTION

	AX12_UART_Write (AX12_REG_GOAL_POSITION); // Starting address where the data is written
	AX12_UART_Write (L); // LENGTH PER AX

	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (setpoint_low);
	AX12_UART_Write (setpoint_high);

	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	while(AX12_UART_Data_Sent()!=1);
}

void AX12_Dual_Write_Torque_On_Sync (CPU_INT08U ax12_id1, CPU_INT08U ax12_id2)
{
	CPU_INT16U checksum;
	CPU_INT08U L=1;
	CPU_INT08U length=(2*(L+1))+4;

	checksum = ~(0xFE + length + AX12_CMD_SYNC_WRITE + AX12_REG_TORQUE_ENABLE + L + ax12_id1 + 0x01 + ax12_id2 + 0x01);

    AX12_UART_Write (0xFF); 
	AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFE); // ID BROADCAST
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_SYNC_WRITE); // INSTRUCTION

	AX12_UART_Write (AX12_REG_TORQUE_ENABLE); // Starting address where the data is written
	AX12_UART_Write (L); // LENGTH PER AX

	AX12_UART_Write (ax12_id1); // ID1
	AX12_UART_Write (0x01);

	AX12_UART_Write (ax12_id2); // ID2
	AX12_UART_Write (0x01);

	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	while(AX12_UART_Data_Sent()!=1);
}

void AX12_Write_Torque_On_Sync (CPU_INT08U ax12_id)
{
	CPU_INT16U checksum;
	CPU_INT08U L=1;
	CPU_INT08U length=(L+1)+4;

	checksum = ~(0xFE + length + AX12_CMD_SYNC_WRITE + AX12_REG_TORQUE_ENABLE + L + ax12_id + 0x01);

    AX12_UART_Write (0xFF); 
	AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFE); // ID BROADCAST
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_SYNC_WRITE); // INSTRUCTION

	AX12_UART_Write (AX12_REG_TORQUE_ENABLE); // Starting address where the data is written
	AX12_UART_Write (L); // LENGTH PER AX

	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (0x01);

	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	while(AX12_UART_Data_Sent()!=1);
}

CPU_INT08U AX12_Write_Reg_Sync (CPU_INT08U ax12_id, CPU_INT08U reg_address, CPU_INT08U data)
{
	CPU_INT16U checksum;
	CPU_INT08U L=1;
	CPU_INT08U length=(L+1)+4;

	checksum = ~(0xFE + length + AX12_CMD_SYNC_WRITE + reg_address + L + ax12_id + data);

    AX12_UART_Write (0xFF); 
	AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFE); // ID BROADCAST
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_SYNC_WRITE); // INSTRUCTION

	AX12_UART_Write (reg_address); // Starting address where the data is written
	AX12_UART_Write (L); // LENGTH PER AX

	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (data);

	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	while(AX12_UART_Data_Sent()!=1);
}

CPU_INT08U AX12_Write_Reg_2_Datas_Sync( CPU_INT08U ax12_id, CPU_INT08U reg_address, CPU_INT08U data1, CPU_INT08U data2)
{
	CPU_INT16U checksum;
	CPU_INT08U L=2;
	CPU_INT08U length=(L+1)+4;

	checksum = ~(0xFE + length + AX12_CMD_SYNC_WRITE + reg_address + L + ax12_id + data1 + data2);

    AX12_UART_Write (0xFF); 
	AX12_UART_Write (0xFF);
	AX12_UART_Write (0xFE); // ID BROADCAST
	AX12_UART_Write (length); // LENGTH
	AX12_UART_Write (AX12_CMD_SYNC_WRITE); // INSTRUCTION

	AX12_UART_Write (reg_address); // Starting address where the data is written
	AX12_UART_Write (L); // LENGTH PER AX

	AX12_UART_Write (ax12_id); // ID
	AX12_UART_Write (data1);
	AX12_UART_Write (data2);

	AX12_UART_Write ( (CPU_INT08U) checksum); // CHECKSUM

	while(AX12_UART_Data_Sent()!=1);
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

CPU_INT08U GPIO_Action (CPU_INT08U bit_position, CPU_INT08U bit_value)
{
	CPU_INT08U reg;
	reg = PMP_Read(GPIO_REGISTER);

	if(bit_value==0)
	{
		reg = reg & ~(0x01<<bit_position);
	}

	if(bit_value==1)
	{
		reg = reg | (0x01<<bit_position);
	}

	PMP_Write(GPIO_REGISTER, reg);
	return reg;
}

void BSPFPGA_Reset(void)
{

	char test;
	PMP_Write(RESET_REGISTER,0xFF);
	PMP_Write(RESET_REGISTER,0x00);
	PMP_Write(LED_REGISTER,0x01);

	AX12_UART_Init ();
	
	//DEBUG UART AX12
	//AX12_UART_Write (0X55);
	//AX12_UART_Write (0XAA);
	//AX12_UART_Write (0X55);

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
