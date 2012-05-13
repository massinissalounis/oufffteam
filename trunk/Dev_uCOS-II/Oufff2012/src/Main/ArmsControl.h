// Control for the arms - Oufffteam 2012
// Pierre - Emmanuel GAILLARDON

#ifndef  ARMSCONTROL_H
#define  ARMSCONTROL_H

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
#define AX12_LEFT_ARM_ID			(0x0F)
#define AX12_RIGHT_ARM_ID			(0x12)
#define AX12_LEFT_WRIST_ID			(0x0B)
#define AX12_RIGHT_WRIST_ID			(0x0A)
#define AX12_ELEVATOR_ID			(0x11)

#define PUMP_LEFT					(0x01)
#define PUMP_RIGHT					(0x02)

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/   

void ARMS_InitReg(void);
void ARMS_Init(void);
void ARMS_DefaultPos(void);
void ARMS_Sleep(void);
void ARMS_Open_Ingot(void);
void ARMS_GrabTotem(void);
void ARMS_Catch(void);
void ARMS_Open_Map(void);
void ARMS_Grab_Map(void);

void ARM_Left_Close(void);
void ARM_Right_Close(void);
void ARM_Left_Open(void);
void ARM_Right_Open(void);
void ARM_Right_GrabTotem(void);
void ARM_Left_GrabTotem(void);
void ARM_Right_Catch(void);
void ARM_Left_Catch(void);
//void ARM_Left_GrabIngotOnFloor(void);
//void ARM_Right_GrabIngotOnFloor(void);
//void ARM_Left_GrabIngotOnTotem(void);
//void ARM_Right_GrabIngotOnTotem(void);
//void ARM_Left_GrabCD(void);
//void ARM_Right_GrabCD(void);

void ELEVATOR_Level_Low(void);
void ELEVATOR_Level_Catch(void);
//void ELEVATOR_Level_CD(void);
//void ELEVATOR_Level_Ingot(void);
void ELEVATOR_Level_High(void);

void WRIST_Left_Down(void);
void WRIST_Right_Down(void);
void WRIST_Left_Middle(void);
void WRIST_Right_Middle(void);
void WRIST_Left_Up(void);
void WRIST_Right_Up(void);

//void PUMP_Right_Suck(void);
//void PUMP_Left_Suck(void);
void PUMP_Right_Release(void);
void PUMP_Left_Release(void);

#endif // ARMSCONTROL_H
