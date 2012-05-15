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

// ARMS ---------------------------------------------------------------------------------
void ARMS_InitReg(void);
void ARMS_SetSpeed(void);
void ARMS_DefaultPosRed(void);
void ARMS_DefaultPosPurple(void);
void ARMS_DeploymentRed(void);
void ARMS_DeploymentPurple(void);
void ARMS_Open(void);
void ARMS_Close(void);
void ARMS_OpenOneCD(void);
void ARMS_OpenTotem(void);
void ARMS_CloseTotem(void);
void ARMS_Ungrab(void);

// ARM Left -----------------------------------------------------------------------------
void ARM_Left_DefaultPosRed(void);
void ARM_Left_DefaultPosPurple(void);
void ARM_Left_Open(void);
void ARM_Left_Close(void);
void ARM_Left_Ungrab(void);

// ARM Right ----------------------------------------------------------------------------
void ARM_Right_DefaultPosRed(void);
void ARM_Right_DefaultPosPurple(void);
void ARM_Right_Open(void);
void ARM_Right_Close(void);
void ARM_Right_Ungrab(void);

// ELEVATOR -----------------------------------------------------------------------------
void ELEVATOR_DefaultPos(void);
void ELEVATOR_Level_Low(void);
void ELEVATOR_Level_High(void);
void ELEVATOR_Level_GrabTotem(void);
void ELEVATOR_Level_Open(void);

// WRIST Left ---------------------------------------------------------------------------
void WRIST_Left_DefaultPosRed(void);
void WRIST_Left_DefaultPosPurple(void);
void WRIST_Left_Open(void);
void WRIST_Left_OpenOneCD(void);
void WRIST_Left_Close(void);
void WRIST_Left_CloseTotem(void);

// WRIST Right --------------------------------------------------------------------------
void WRIST_Right_DefaultPosRed(void);
void WRIST_Right_DefaultPosPurple(void);
void WRIST_Right_Open(void);
void WRIST_Right_OpenOneCD(void);
void WRIST_Right_Close(void);
void WRIST_Right_CloseTotem(void);

// PUMP ---------------------------------------------------------------------------------
void PUMP_Right_Release(void);
void PUMP_Left_Release(void);


#endif // ARMSCONTROL_H
