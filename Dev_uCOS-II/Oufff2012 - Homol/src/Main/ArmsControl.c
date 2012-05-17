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
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CW_LIMIT, 0x40, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CW_LIMIT, 0xE9, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_CW_LIMIT, 0x7B, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_CW_LIMIT, 0x03, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_CW_LIMIT, 0x63, 0x02);

	// CCW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CCW_LIMIT, 0x18, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CCW_LIMIT, 0xB9, 0x02);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_CCW_LIMIT, 0xC6, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_CCW_LIMIT, 0x3A, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_CCW_LIMIT, 0x89, 0x03);
}

void ARMS_SetSpeed(void)
{
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_SPEED, 0x90, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_SPEED, 0x90, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_SPEED, 0x90, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_SPEED, 0x90, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_SPEED, 0xFF, 0x03);
}

// ARMS ---------------------------------------------------------------------------------
void ARMS_DefaultPosRed(void)
{
	WRIST_Left_DefaultPosRed();
	ARM_Left_DefaultPosRed();
	WRIST_Right_DefaultPosRed();
	ARM_Right_DefaultPosRed();
	ELEVATOR_DefaultPos();	
}

void ARMS_DefaultPosPurple(void)
{
	WRIST_Left_DefaultPosPurple();
	ARM_Left_DefaultPosPurple();
	WRIST_Right_DefaultPosPurple();
	ARM_Right_DefaultPosPurple();
	ELEVATOR_DefaultPos();	
}

void ARMS_DeploymentRed(void)
{
	WRIST_Left_Open();
	ARM_Left_Open();
	OSTimeDlyHMSM(0, 0, 0, 300);
	WRIST_Right_Open();
	OSTimeDlyHMSM(0, 0, 0, 300);
	ARM_Right_Open();
	OSTimeDlyHMSM(0, 0, 0, 250);
	ELEVATOR_Level_Open();
	OSTimeDlyHMSM(0, 0, 0, 250);
}

void ARMS_DeploymentPurple(void)
{
	WRIST_Right_Open();
	ARM_Right_Open();
	OSTimeDlyHMSM(0, 0, 0, 300);
	WRIST_Left_Open();
	OSTimeDlyHMSM(0, 0, 0, 300);
	ARM_Left_Open();
	OSTimeDlyHMSM(0, 0, 0, 250);
	ELEVATOR_Level_Open();
	OSTimeDlyHMSM(0, 0, 0, 250);
}

void ARMS_OpenDown(void)
{
	WRIST_Left_Open();
	ARM_Left_Open();
	WRIST_Right_Open();
	ARM_Right_Open();
	ELEVATOR_Level_Open();
	OSTimeDlyHMSM(0, 0, 1, 0);
}

void ARMS_OpenUp(void)
{
	ELEVATOR_Level_GrabTotem();
	OSTimeDlyHMSM(0, 0, 0, 100);
	WRIST_Left_Open();
	ARM_Left_Open();
	WRIST_Right_Open();
	ARM_Right_Open();
	OSTimeDlyHMSM(0, 0, 1, 0);
}

void ARMS_Close(void)
{
	ELEVATOR_Level_Low();
	OSTimeDlyHMSM(0, 0, 0, 250);
	ARM_Right_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	WRIST_Right_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	ARM_Left_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	WRIST_Left_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
}

void ARMS_OpenOneCD(void)
{
	WRIST_Left_OpenOneCD();
	ARM_Left_Open();
	WRIST_Right_OpenOneCD();
	ARM_Right_Open();
	ELEVATOR_Level_Open();
	OSTimeDlyHMSM(0, 0, 1, 0);
}

void ARMS_OpenTotem(void)
{
	ARMS_OpenDown();
	ELEVATOR_Level_GrabTotem();
}

void ARMS_CloseTotem(void)
{
	ELEVATOR_Level_High();
	ARM_Right_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	WRIST_Right_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	ARM_Left_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	WRIST_Left_Close();
	OSTimeDlyHMSM(0, 0, 0, 500);
	ELEVATOR_Level_GrabTotem();
	OSTimeDlyHMSM(0, 0, 0, 100);
}

void ARMS_Ungrab(void)
{
	ARMS_OpenDown();
	ARM_Left_Ungrab();
	OSTimeDlyHMSM(0, 0, 1, 0);
	ARM_Right_Ungrab();
	ELEVATOR_Level_High();
	OSTimeDlyHMSM(0, 0, 0, 100);
}

// ARM Left -----------------------------------------------------------------------------
void ARM_Left_DefaultPosRed(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0xD0);
}

void ARM_Left_DefaultPosPurple(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x01, 0x45);
}

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

void ARM_Left_Ungrab(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x01, 0x9A);
}

// ARM Right ----------------------------------------------------------------------------
void ARM_Right_DefaultPosRed(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0xA8);
}

void ARM_Right_DefaultPosPurple(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x6D);
}

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

void ARM_Right_Ungrab(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0x62);
}

// ELEVATOR -----------------------------------------------------------------------------
void ELEVATOR_DefaultPos(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x03, 0x07);
}

void ELEVATOR_Level_Low(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x02, 0x75);
}

void ELEVATOR_Level_High(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x03, 0x84);
}

void ELEVATOR_Level_GrabTotem(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x03, 0x57);
}

void ELEVATOR_Level_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x02, 0x9E);
}

// WRIST Left ---------------------------------------------------------------------------
void WRIST_Left_DefaultPosRed(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x01, 0xBD);
}

void WRIST_Left_DefaultPosPurple(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x03, 0xC5);
}

void WRIST_Left_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x00, 0x82);
}

void WRIST_Left_OpenOneCD(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x00, 0xF3);
}

void WRIST_Left_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x02, 0x9E);
}

void WRIST_Left_CloseTotem(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x02, 0x8A);
}

// WRIST Right --------------------------------------------------------------------------
void WRIST_Right_DefaultPosRed(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x00, 0x0F);
}

void WRIST_Right_DefaultPosPurple(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x01, 0xB8);
}

void WRIST_Right_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x03, 0x39);
}

void WRIST_Right_OpenOneCD(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x02, 0xB0);
}

void WRIST_Right_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x01, 0x2C);
}

void WRIST_Right_CloseTotem(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x01, 0x72);
}

// PUMP ---------------------------------------------------------------------------------
// Not used in 2012 --> Keep in code for future release
//void PUMP_Right_Suck(void)
//{
//	GPIO_Action (PUMP_RIGHT, 1);
//}
//
//void PUMP_Left_Suck(void)
//{
//	GPIO_Action (PUMP_LEFT, 1);
//}
//
void PUMP_Right_Release(void)
{
	GPIO_Action (PUMP_RIGHT, 0);
}

void PUMP_Left_Release(void)
{
	GPIO_Action (PUMP_LEFT, 0);
}
