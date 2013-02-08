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
#include    "i2c.h"
#include "bsp_iic.h"

static int Iic_Init (IicDevice *InstancePtr, I2C_MODULE id, I2C_RUNNING_MODE DeviceMode)
{

	int res = IIC_SUCCESS;

	// first set the config
	InstancePtr->DeviceConfig = I2C_ENABLE_HIGH_SPEED | I2C_ENABLE_SLAVE_CLOCK_STRETCHING;
	InstancePtr->DeviceAddressMode = I2C_USE_7BIT_ADDRESS;
	InstancePtr->DeviceMode = DeviceMode;

	// TODO set the baudrate

	// enable et setup the Iic // TODO find how to configure the address mode
	I2CConfigure(InstancePtr->DeviceId, InstancePtr->DeviceConfig);
	I2CEnable(InstancePtr->DeviceId, TRUE);

	InstancePtr->OperationInProgress = 0;

	return res;
}

static int Iic_int_init(IicDevice *InstancePtr, OS_EVENT *MySem)
{
	int res = IIC_SUCCESS;

	// Create semphore // TODO check if create ends OK
	MySem = OSSemCreate(0);
	// Associate semaphore
	InstancePtr->IicSem = MySem;

	// Enable interrupt and set priority
	if(InstancePtr->DeviceId = I2C1)
	{
		mI2C1SGetIntEnable();
		mI2C1SetIntPriority(InstancePtr->IicIntPrio);
		mI2C1SetIntSubPriority(InstancePtr->IicIntSubPrio);

		// Read back config
		if(mI2C1GetIntPriority() != InstancePtr->IicIntPrio)
		{
			res = IIC_FAILURE;
		}
		if(mI2C1GetIntSubPriority() != InstancePtr->IicIntSubPrio)
		{
			res = IIC_FAILURE;
		}
	}
	else if(InstancePtr->DeviceId = I2C2)
	{
		mI2C2SGetIntEnable();
		mI2C2SetIntPriority(InstancePtr->IicIntPrio);
		mI2C2SetIntSubPriority(InstancePtr->IicIntSubPrio);

		// Read back config
		if(mI2C2GetIntPriority() != InstancePtr->IicIntPrio)
		{
			res = IIC_FAILURE;
		}
		if(mI2C2GetIntSubPriority() != InstancePtr->IicIntSubPrio)
		{
			res = IIC_FAILURE;
		}
	}

	return res;
}

static int Iic_reset(IicDevice *InstancePtr)
{
	// first stop all transaction
	if(InstancePtr->OperationInProgress != 0)
	{
		InstancePtr->OperationInProgress = 0;
		InstancePtr->NbAddrInSlave = 0;
		InstancePtr->TrnWriteLength = 0;
		InstancePtr->TrnReadLength = 0;

		// gen a stop condition
		I2CStop(InstancePtr->DeviceId);
		while(!(I2CGetStatus(InstancePtr->DeviceId) & I2C_STOP));
	}

	// disable the i2c module
	I2CEnable(InstancePtr->DeviceId, FALSE);
	// disable interrupt and  clear all interrupt
	if(InstancePtr->DeviceId == I2C1)
	{
		mI2C1IntDisable();
		mI2C1ClearAllIntFlag();
	}
	if(InstancePtr->DeviceId == I2C2)
	{
		mI2C2IntDisable();
		mI2C2ClearAllIntFlag();
	}

	// clear i2c status register
	I2CClearStatus(InstancePtr->DeviceId, I2SGetStatus(InstancePtr->DeviceId));

	return IIC_SUCCESS;
}

///////////////////////////////////////////////////////////
// I2C functions
///////////////////////////////////////////////////////////

//void __ISR(_TIMER_2_VECTOR, ipl6) I2C_Handler(void *InstancePtr)
//{
//	IicDevice *IicPtr = (IicDevice *) InstancePtr;
//	I2C_STATUS status;
//
//	// first clear the interrupt register
//	mI2C1MClearAllIntFlags();
//
//	// then read the status register
//	status = I2CGetStatus(IicPtr->DeviceId);
//
//	IicPtr->DeviceStatus = status;
//
//	I2CClearStatus(IicPtr->DeviceId, status);
//
//	// release semaphore
//	OSSemPost(IicPtr->IicSem);
//}

static int IicWrite(IicDevice *InstancePtr)
{
	int index;

	// check if the device is in master mode
	if(InstancePtr->DeviceMode != I2C_MASTER_MODE)
		return IIC_DEVICE_NOT_IN_MASTER_MODE;

	// first check if the i2c module is there the device is not already in use
	if(InstancePtr->OperationInProgress != 0)
		return IIC_OPERATION_ONGOING;

	InstancePtr->OperationInProgress = 1;

	// check if the transmiter is ready to send
	if(I2CTransmitterIsReady(InstancePtr->DeviceId) == FALSE)
		// TODO check with PE whether we wait for the bus to be ready or not
		return IIC_DEVICE_IS_NOT_READY;

	// update slave address for write operation
	I2C_FORMAT_7_BIT_ADRESS(InstancePtr->SlaveAddress, InstancePtr->SlaveAddress.byte, I2C_WRITE);
	
	// Set the start bit and wait for the interrupt using the semaphore
	if(I2CStart(InstancePtr->DeviceId) != I2C_SUCCESS)
		return IIC_BUS_COLLISION;

	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (start condition ok)
	if((InstancePtr->DeviceStatus & I2C_START) == 0)
		return IIC_START_FAIL;

	// now start to send the slave address and wait for the interrupt using the semaphore
	if(I2CSendByte(InstancePtr->DeviceId, InstancePtr->SlaveAddress.byte) == I2C_MASTER_BUS_COLLISION)
		return IIC_BUS_COLLISION;
	
	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (transfert done + acknowledge)
	if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
		return IIC_SEND_SLAVE_ADDR_FAIL;
	if((InstancePtr->DeviceStatus & I2C_BYTE_ACKNOWLEDGED) == 0)
		return IIC_BYTE_NOT_ACKNOLEDGE;

	// then send the address in slave
	index = 0;
	while(index < InstancePtr->NbAddrInSlave)
	{
		if(I2CSendByte(InstancePtr->DeviceId, InstancePtr->AddrInSlave[index]) == I2C_MASTER_BUS_COLLISION)
			return IIC_BUS_COLLISION;
	
		OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
		// check if the interrupt status (transfert done + acknowledge)
		if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
			return IIC_SEND_ADDR_IN_SLAVE_FAIL;
		if((InstancePtr->DeviceStatus & I2C_BYTE_ACKNOWLEDGED) == 0)
			return IIC_BYTE_NOT_ACKNOLEDGE;

		index++;
	}

	// then send data to the slave
	index = 0;
	while(index < InstancePtr->TrnWriteLength)
	{
		if(I2CSendByte(InstancePtr->DeviceId, InstancePtr->WriteBuffer[index]) == I2C_MASTER_BUS_COLLISION)
			return IIC_BUS_COLLISION;
	
		OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
		// check if the interrupt status (transfert done + acknowledge)
		if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
			return IIC_SEND_BYTE_FAIL;
		if((InstancePtr->DeviceStatus & I2C_BYTE_ACKNOWLEDGED) == 0)
			return IIC_BYTE_NOT_ACKNOLEDGE;

		index++;
	}

	// finally gen a stop condition and wait for the interrupt using the semaphore
	I2CStop(InstancePtr->DeviceId);

	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (stop condition ok)
	if((InstancePtr->DeviceStatus & I2C_STOP) == 0)
		return IIC_STOP_FAIL;

	InstancePtr->OperationInProgress = 0;
	
	return IIC_SUCCESS;

} // IicWrite

static int IicRead(IicDevice *InstancePtr)
{
	int index;

	// check if the device is in master mode
	if(InstancePtr->DeviceMode != I2C_MASTER_MODE)
		return IIC_DEVICE_NOT_IN_MASTER_MODE;

	// first check if the i2c module is there the device is not already in use
	if(InstancePtr->OperationInProgress != 0)
		return IIC_OPERATION_ONGOING;

	InstancePtr->OperationInProgress = 1;

	// check if the transmiter is ready to send
	if(I2CTransmitterIsReady(InstancePtr->DeviceId) == FALSE)
		// TODO check with PE whether we wait for the bus to be ready or not
		return IIC_DEVICE_IS_NOT_READY;

	// update slave address for write operation
	I2C_FORMAT_7_BIT_ADRESS(InstancePtr->SlaveAddress, InstancePtr->SlaveAddress.byte, I2C_WRITE);
	
	// Set the start bit and wait for the interrupt using the semaphore
	if(I2CStart(InstancePtr->DeviceId) != I2C_SUCCESS)
		return IIC_BUS_COLLISION;

	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (start condition ok)
	if((InstancePtr->DeviceStatus & I2C_START) == 0)
		return IIC_START_FAIL;

	// now start to send the slave address and wait for the interrupt using the semaphore
	if(I2CSendByte(InstancePtr->DeviceId, InstancePtr->SlaveAddress.byte) == I2C_MASTER_BUS_COLLISION)
		return IIC_BUS_COLLISION;
	
	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (transfert done + acknowledge)
	if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
		return IIC_SEND_SLAVE_ADDR_FAIL;
	if((InstancePtr->DeviceStatus & I2C_BYTE_ACKNOWLEDGED) == 0)
		return IIC_BYTE_NOT_ACKNOLEDGE;

	// then send the address in slave
	index = 0;
	while(index < InstancePtr->NbAddrInSlave)
	{
		if(I2CSendByte(InstancePtr->DeviceId, InstancePtr->AddrInSlave[index]) == I2C_MASTER_BUS_COLLISION)
			return IIC_BUS_COLLISION;
	
		OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
		// check if the interrupt status (transfert done + acknowledge)
		if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
			return IIC_SEND_ADDR_IN_SLAVE_FAIL;
		if((InstancePtr->DeviceStatus & I2C_BYTE_ACKNOWLEDGED) == 0)
			return IIC_BYTE_NOT_ACKNOLEDGE;

		index++;
	}

	// update slave address for read operation
	I2C_FORMAT_7_BIT_ADRESS(InstancePtr->SlaveAddress, InstancePtr->SlaveAddress.byte, I2C_READ);

	// send the slave address in read mode with a repeated start to switch the slave in read mode
	if(I2CRepeatedStart(InstancePtr->DeviceId) != I2C_SUCCESS)
		return IIC_BUS_COLLISION;

	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (start condition ok)
	if((InstancePtr->DeviceStatus & I2C_START) == 0)
		return IIC_REPEATED_START_FAIL;

	if(I2CSendByte(InstancePtr->DeviceId, InstancePtr->SlaveAddress.byte) == I2C_MASTER_BUS_COLLISION)
		return IIC_BUS_COLLISION;
	
	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (transfert done + acknowledge)
	if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
		return IIC_SEND_BYTE_FAIL;
	if((InstancePtr->DeviceStatus & I2C_BYTE_ACKNOWLEDGED) == 0)
		return IIC_BYTE_NOT_ACKNOLEDGE;

	// then receive data from slave
	index = 0;
	while(index < InstancePtr->TrnReadLength)
	{
		// set the I2C module ready to received data
		if(I2CReceiverEnable(InstancePtr->DeviceId, TRUE) == I2C_RECEIVE_OVERFLOW)
			return IIC_RECEIVE_OVERFLOW;

		// wait for the interrupt (received the byte)
		OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
		// check if the interrupt status (transfert done + data available)
		if((InstancePtr->DeviceStatus & I2C_TRANSMITTER_BUSY) == 0)
			return IIC_RECEIVE_DATA_FAIL;

		if(I2CReceivedDataIsAvailable(InstancePtr->DeviceId))
		{
			// now acknoledge the received byte
			I2CAcknowledgeByte(InstancePtr->DeviceId, TRUE);
			// store the received byte
			InstancePtr->ReadBuffer[index] = I2CGetByte(InstancePtr->DeviceId);
		}

		// wait for the end of acknowledge
		OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
		// check if the interrupt status (acknowledge ok) // TODO check if we can use the status register ACKSTAT
		if((I2CAcknowledgeHasCompleted(InstancePtr->DeviceId)) != 0)
			return IIC_RECEIVE_ACKNOWLEDGE_FAIL;

		index++;

	}

	// finally gen a stop condition and wait for the interrupt using the semaphore
	I2CStop(InstancePtr->DeviceId);

	OSSemPend(InstancePtr->IicSem, 0, InstancePtr->error);
	// check if the interrupt status (stop condition ok)
	if((InstancePtr->DeviceStatus & I2C_STOP) == 0)
		return IIC_STOP_FAIL;

	InstancePtr->OperationInProgress = 0;

	return IIC_SUCCESS;

} // IicRead
