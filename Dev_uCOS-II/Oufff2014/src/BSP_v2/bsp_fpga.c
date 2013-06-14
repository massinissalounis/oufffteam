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

CPU_INT08U AX12_UART_Read_Status (void)
{
	CPU_INT08U value;
	value = PMP_Read(AX12_UART_STATUS_REGISTER);
	return value;
}

CPU_INT08U AX12_UART_Busy (void)
{
	CPU_INT08U status;	
	status = PMP_Read(AX12_UART_STATUS_REGISTER);
	if( (status & AX12_UART_MASK_BUSY)==AX12_UART_MASK_BUSY) return 1;
    else return 0;    
}

void AX12_UART_Write (CPU_INT08U data)
{
	while(AX12_UART_Busy())
		OSTimeDlyHMSM(0, 0, 0, 1);
	PMP_Write(AX12_UART_OUT_REGISTER, data);
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

	while(AX12_UART_Busy());
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

	while(AX12_UART_Busy());
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

	while(AX12_UART_Busy());
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

	while(AX12_UART_Busy());
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

	while(AX12_UART_Busy());
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

	while(AX12_UART_Busy());
}

/// TO DO : Stop 3/02/2013 --> Fct test lecture AX12
/// TO DO : COLOR Sensor control
/// TO DO : SERVO CONTROL
/// TO DO : fonctions balises haut niveau ?
/// TO DO : fonctions debug code FPGA ! --> servo
/// TO DO : fonctions debug code FPGA ! --> AX12 + procedure pour cyril !


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

CPU_INT08U FPGA_LED1_Action (CPU_INT08U bit_value)
{
	CPU_INT08U reg;

	reg = PMP_Read(LED_REGISTER);

	if(bit_value==0)
		reg = reg & ~(0x01);

	if(bit_value==1)
		reg = reg | (0x01);

	PMP_Write(LED_REGISTER, reg);
	return reg;
}

CPU_INT08U FPGA_LED2_Action (CPU_INT08U bit_value)
{
	CPU_INT08U reg;
	reg = PMP_Read(LED_REGISTER);

	if(bit_value==0)
		reg = reg & ~(0x02);

	if(bit_value==1)
		reg = reg | (0x02);

	PMP_Write(LED_REGISTER, reg);
	return reg;
}

void SERVO_0_Write_Pulse (CPU_INT08U pulse_duration)
{
	PMP_Write(SERVO_0_REGISTER, pulse_duration);
}

void SERVO_1_Write_Pulse (CPU_INT08U pulse_duration)
{
	PMP_Write(SERVO_1_REGISTER, pulse_duration);
}

CPU_INT08U BEACON_MOTOR_Latch (void)
{
	PMP_Write(BEACON_ENCODER_LATCH_REGISTER,0xFF);
}

CPU_INT16S BEACON_MOTOR_Read (void)
{
	CPU_INT16S value;
	value = PMP_Read(BEACON_ENCODER_MSB_REGISTER) <<8;
	value = value | PMP_Read(BEACON_ENCODER_LSB_REGISTER);
	return value;
}

void BEACON_MOTOR_Write_PWM (CPU_INT08U pulse_duration)
{
	PMP_Write(BEACON_MOTOR_PERIOD_REGISTER, pulse_duration);
}

CPU_INT8U BEACON_STATUS_Read (void)
{
	CPU_INT8U value;
	value = PMP_Read(BEACON_STATUS_REGISTER);
	return value;
}

CPU_INT16U BEACON_POSITION_REG_Read (INT8U indix)
{
	CPU_INT16U value;
	CPU_INT8U Address_MSB;
	CPU_INT8U Address_LSB;
	
	switch(indix)
	{
		case 0: Address_MSB=BEACON_0_MSB_REGISTER; Address_LSB=BEACON_0_LSB_REGISTER; break;
		case 1: Address_MSB=BEACON_1_MSB_REGISTER; Address_LSB=BEACON_1_LSB_REGISTER; break;
		case 2: Address_MSB=BEACON_2_MSB_REGISTER; Address_LSB=BEACON_2_LSB_REGISTER; break;
		case 3: Address_MSB=BEACON_3_MSB_REGISTER; Address_LSB=BEACON_3_LSB_REGISTER; break;
		case 4: Address_MSB=BEACON_4_MSB_REGISTER; Address_LSB=BEACON_4_LSB_REGISTER; break;
		case 5: Address_MSB=BEACON_5_MSB_REGISTER; Address_LSB=BEACON_5_LSB_REGISTER; break;
		case 6: Address_MSB=BEACON_6_MSB_REGISTER; Address_LSB=BEACON_6_LSB_REGISTER; break;
		case 7: Address_MSB=BEACON_7_MSB_REGISTER; Address_LSB=BEACON_7_LSB_REGISTER; break;
		default: Address_MSB=0xFF; Address_LSB=0xFF; break;
	}
		
	value = PMP_Read(Address_MSB) <<8;
	value = value | PMP_Read(Address_LSB);
	return value;
}


void BSPFPGA_Reset(void)
{
	PMP_Write(RESET_REGISTER,0xFF);
	PMP_Write(RESET_REGISTER,0x00);
	PMP_Write(LED_REGISTER,0x01);
}
