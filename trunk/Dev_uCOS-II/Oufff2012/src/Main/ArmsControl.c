#include "AppIncludes.h"
#include "ArmsControl.h"

#define DEFAULT_WAIT_S 1
#define DEFAULT_WAIT_MS 0

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
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CW_LIMIT, 0xA9, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CW_LIMIT, 0x0E, 0x01);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_CW_LIMIT, 0xC8, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_CW_LIMIT, 0xFA, 0x00);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_CW_LIMIT, 0x2C, 0x01);

	// CCW limits
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_ARM_ID, AX12_REG_CCW_LIMIT, 0xD0, 0x02);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_ARM_ID, AX12_REG_CCW_LIMIT, 0x53, 0x02);
	AX12_Write_Reg_2_Datas_Sync(AX12_LEFT_WRIST_ID, AX12_REG_CCW_LIMIT, 0x20, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_RIGHT_WRIST_ID, AX12_REG_CCW_LIMIT, 0x34, 0x03);
	AX12_Write_Reg_2_Datas_Sync(AX12_ELEVATOR_ID, AX12_REG_CCW_LIMIT, 0xFF, 0x03);
}

void ARMS_Init(void)
{
	// Shutdown the pump
	PUMP_Right_Release();
	PUMP_Left_Release();
	
	ELEVATOR_Level_Ingot();
	ARMS_Open_Ingot();
	ARMS_Sleep();

	LED_On(4);
}

void ARMS_DefaultPos(void)
{
	WRIST_Left_Up();
	WRIST_Right_Up();

	ELEVATOR_Level_Ingot();

	ARM_Left_Close();
	ARM_Right_Close();
}

void ARMS_Sleep(void)
{
	WRIST_Right_Up();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	WRIST_Left_Up();
	ARM_Right_Close();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);	
	ARM_Left_Close();		
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
}

void ARMS_Open_Ingot(void)
{
	ARM_Left_Open();		
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	ARM_Right_Open();		
	WRIST_Left_Down();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	WRIST_Right_Down();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
}

void ARMS_GrabTotem(void)
{
	ARM_Left_GrabTotem();
	ARM_Right_GrabTotem();
}

void ARMS_Catch(void)
{
	ARM_Left_Catch();
	ARM_Right_Catch();
}

void ARMS_Open_Map(void)
{
	ARM_Left_Open();		
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	ARM_Right_Open();		
	WRIST_Left_Middle();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	WRIST_Right_Middle();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
}

void ARMS_Open_Map(void)
{
	ARM_Left_Open();		
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	ARM_Right_Open();		
	WRIST_Left_Middle();
	OSTimeDlyHMSM(0, 0, DEFAULT_WAIT_S, DEFAULT_WAIT_MS);
	WRIST_Right_Middle();
}

void ARMS_Grab_Map(void)
{
	ELEVATOR_Level_Up();
	WRIST_Left_Up();
	WRIST_Right_Up();
}
	
void ARM_Left_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0xD0);
}

void ARM_Right_Close(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x0E);
}

void ARM_Left_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x01, 0xA9);
}

void ARM_Right_Open(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0x53);
}

void ARM_Right_GrabTotem(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x2C);
}

void ARM_Left_GrabTotem(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0xD0);
}

void ARM_Right_Catch(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x2C);
}

void ARM_Left_Catch(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0xD0);
}

// Functions for Pneumatic control of objects
//void ARM_Right_GrabIngotOnFloor(void)
//{
//	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
//	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0x2C);
//}
//
//void ARM_Left_GrabIngotOnFloor(void)
//{
//	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
//	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0xD0);
//}
//
//void ARM_Right_GrabIngotOnTotem(void)
//{
//	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
//	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x01, 0xC0);
//}

//void ARM_Left_GrabIngotOnTotem(void)
//{
//	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
//	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0x33);
//}

//void ARM_Left_GrabCD(void)
//{
//	AX12_Write_Torque_On_Sync (AX12_LEFT_ARM_ID);
//	AX12_Write_Position_Sync(AX12_LEFT_ARM_ID, 0x02, 0x00);
//}

//void ARM_Right_GrabCD(void)
//{
//	AX12_Write_Torque_On_Sync (AX12_RIGHT_ARM_ID);
//	AX12_Write_Position_Sync(AX12_RIGHT_ARM_ID, 0x02, 0x00);
//}

void ELEVATOR_Level_Low(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x01, 0x2C);
}

void ELEVATOR_Level_CD(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x01, 0xC2);
}

void ELEVATOR_Level_Ingot(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x02, 0xF8);
}

void ELEVATOR_Level_High(void)
{
	AX12_Write_Torque_On_Sync (AX12_ELEVATOR_ID);
	AX12_Write_Position_Sync(AX12_ELEVATOR_ID, 0x03, 0xFF);
}

void WRIST_Left_Down(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x00, 0xC8);
}

void WRIST_Right_Down(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x03, 0x34);
}

void WRIST_Left_Middle(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x02, 0x00);
}

void WRIST_Right_Middle(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x02, 0x00);
}

void WRIST_Left_Up(void)
{
	AX12_Write_Torque_On_Sync (AX12_LEFT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_LEFT_WRIST_ID, 0x03, 0x20);
}

void WRIST_Right_Up(void)
{
	AX12_Write_Torque_On_Sync (AX12_RIGHT_WRIST_ID);
	AX12_Write_Position_Sync(AX12_RIGHT_WRIST_ID, 0x00, 0xFA);
}

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
