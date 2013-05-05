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
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CW_LIMIT, 0xE1, 0x00); // 225 0xE1
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CW_LIMIT, 0xBE, 0x00); // 190 0xBE

	// CCW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CCW_LIMIT, 0xFF, 0x03); // 1023 0x3FF
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CCW_LIMIT, 0xFF, 0x03); // 1023 0x3FF
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

void ARMS_Front(void)
{
	ARM_Left_Front();
	ARM_Right_Front();
//	OSTimeDlyHMSM(0, 0, 0, 100);
}

// ARM Left -----------------------------------------------------------------------------
void ARM_Left_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x03, 0x5C); // 860 0x35C
}

void ARM_Left_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x00, 0xF0); // 240  0xF0
}

void ARM_Left_Front(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x03, 0x02); // 770  0x302
}

// ARM Right ----------------------------------------------------------------------------
void ARM_Right_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x9A); // 410 0x19A
}

void ARM_Right_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x03, 0xF2); // 1010 0x3F2
}

void ARM_Right_Front(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0xC6); // 710  0x2C6
}
