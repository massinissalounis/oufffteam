#include "AppIncludes.h"
#include "ArmsControl.h"

void ARMS_InitReg(void)
{
	// Alarm: All alarms
	AX12_Write_Reg_Sync(AX12_LEFT_ARM_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);
	AX12_Write_Reg_Sync(AX12_RIGHT_ARM_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);
	AX12_Write_Reg_Sync(AX12_LEFT_WRIST_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);
	AX12_Write_Reg_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);
	AX12_Write_Reg_Sync(AX12_ELEVATOR_ID, AX12_REG_ALARM_SHUTDOWN, 0x7F);

	// Temperature limit: 70°C = 0x46
	AX12_Write_Reg_Sync(AX12_LEFT_ARM_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
	AX12_Write_Reg_Sync(AX12_RIGHT_ARM_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
	AX12_Write_Reg_Sync(AX12_LEFT_WRIST_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
	AX12_Write_Reg_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
	AX12_Write_Reg_Sync(AX12_ELEVATOR_ID, AX12_REG_TEMPERATURE_LIMIT, 0x46);
		
	// Max Torque : 768 = 0x0300
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_MAX_TORQUE, 0x00, 0x03);
	
	// Torque Limit : 768 = 0x0300
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_TORQUE_LIMIT, 0x00, 0x03);

	// CW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CW_LIMIT, 0x5E, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CW_LIMIT, 0xE6, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_CW_LIMIT, 0x00, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_CW_LIMIT, 0x00, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_CW_LIMIT, 0x44, 0x00);

	// CCW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CCW_LIMIT, 0xF8, 0x02);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CCW_LIMIT, 0x9E, 0x02);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_CCW_LIMIT, 0xFF, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_CCW_LIMIT, 0xFF, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_CCW_LIMIT, 0xFF, 0x03);
}

void ARM_Left_Sleep(void)
{
	AX12_Dual_Write_Torque_On_Sync (AX12_LEFT_ARM_ID, AX12_LEFT_WRIST_ID);
	AX12_Dual_Write_Position_Sync(AX12_LEFT_ARM_ID, AX12_LEFT_WRIST_ID, 0x00, 0xDC, 0x03, 0x93);  // CBE, FIFI --> Update Value!
}

void ARM_Right_Sleep(void)
{
	AX12_Dual_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID, AX12_RIGHT_WRIST_ID);
	AX12_Dual_Write_Position_Sync(AX12_RIGHT_ARM_ID, AX12_RIGHT_WRIST_ID, 0x00, 0xDC, 0x03, 0x93);  // CBE, FIFI --> Update Value!
}

// FIFI, CBE --> Add new functions if required !


void ELEVATOR_Level_Low(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x03, 0xFF);
}

void ELEVATOR_Level_Middle(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x01, 0xD0);
}

void ELEVATOR_Level_High(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x00, 0x32);
}

void PUMP_Right_Suck(void)
{
	GPIO_Action (PUMP_RIGHT, 1);
}

void PUMP_Left_Suck(void)
{
	GPIO_Action (PUMP_LEFT, 1);
}

void PUMP_Right_Release(void)
{
	GPIO_Action (PUMP_RIGHT, 0);
}

void PUMP_Left_Release(void)
{
	GPIO_Action (PUMP_LEFT, 0);
}

void ARMS_Init(void)
{
	// ALARM Control
//	ARMS_InitReg();

	// HOLDER Init
	ELEVATOR_Level_Low();
	ARM_Right_Sleep();
	ARM_Left_Sleep();

	PUMP_Right_Release();
	PUMP_Left_Release();
}
