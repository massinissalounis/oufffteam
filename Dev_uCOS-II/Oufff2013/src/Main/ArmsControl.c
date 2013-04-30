#include "AppIncludes.h"
#include "ArmsControl.h"

void ARMS_InitReg(void)
{
	// Alarm: All alarms
	AX12_Write_Reg_Sync(AX12_LEFT_ARM_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);
	AX12_Write_Reg_Sync(AX12_RIGHT_ARM_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);

	// Temperature limit: 70°C = 0x46
	AX12_Write_Reg_Sync(AX12_LEFT_ARM_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
	AX12_Write_Reg_Sync(AX12_RIGHT_ARM_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
		
	// Max Torque : 768 = 0x0300
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	
	// Torque Limit : 768 = 0x0300
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);

	// CW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CW_LIMIT, 0x40, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CW_LIMIT, 0xE1, 0x00);

	// CCW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CCW_LIMIT, 0x18, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CCW_LIMIT, 0xB9, 0x02);
}

void ARMS_SetSpeed(void)
{
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_SPEED, 0x90, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_SPEED, 0x90, 0x01);
}

// ARMS ---------------------------------------------------------------------------------
void ARMS_Open(void)
{
	ARM_Left_Open();
	ARM_Right_Open();
//	OSTimeDlyHMSM(0, 0, 1, 0);
}


void ARMS_Close(void)
{
	ARM_Right_Close();
	ARM_Left_Close();
//	OSTimeDlyHMSM(0, 0, 0, 500);
}

void ARMS_Push(void)
{
	ARM_Left_Back();
	ARM_Right_Back();
//	OSTimeDlyHMSM(0, 0, 0, 100);
}

// ARM Left -----------------------------------------------------------------------------
void ARM_Left_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0x8F);
}

void ARM_Left_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x01, 0x86);
}

void ARM_Left_Back(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x01, 0x9A);
}

// ARM Right ----------------------------------------------------------------------------
void ARM_Right_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x98);
}

void ARM_Right_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0x62);
}

void ARM_Right_Back(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0x62);
}
