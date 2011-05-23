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
 //· Enable the desired interrupts
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

// AX12 CONTROL FUNCTIONS

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
	while(AX12_UART_Data_Sent()!=1);

	for(i=0; i<6; i++)
	{
		while(AX12_UART_Data_Ready()!=1);

		if(i==4) status=AX12_UART_Read();
		else AX12_UART_Read();
	}

	return status;
}

/*void AX12_Write (CPU_INT8U address_ax12, CPU_INT8U address_reg, CPU_INT8U data)
{
	PMP_Write(AX12_TX,0xFF);

	while(PMP_Read(QUAD_LATCH_REGISTER)!=0x00);

	PMP_Write(RESET_REGISTER,0xFF);
}
*/
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

CPU_INT08U COLOR_Read (void)
{
	CPU_INT08U value;
	value = PMP_Read(GPIO_REGISTER);
	return value;
}

void BSPFPGA_Reset(void)
{
	PMP_Write(RESET_REGISTER,0xFF);
	PMP_Write(RESET_REGISTER,0x00);
	PMP_Write(LED_REGISTER,0x01);
}
