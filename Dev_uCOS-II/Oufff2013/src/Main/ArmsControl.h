// Control for the arms - Oufffteam 2013
// Pierre - Emmanuel GAILLARDON

#ifndef  ARMSCONTROL_H
#define  ARMSCONTROL_H

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
#define AX12_LEFT_ARM_ID			(0x0B)
#define AX12_RIGHT_ARM_ID			(0x0A)

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/   

// ARMS ---------------------------------------------------------------------------------
void ARMS_InitReg(void);
void ARMS_SetSpeed(void);
void ARMS_Open(void);
void ARMS_Close(void);
void ARMS_Front(void);

// ARM Back Left -----------------------------------------------------------------------------
void ARM_Left_Open(void);
void ARM_Left_Close(void);
void ARM_Left_Front(void);

// ARM Back Right ----------------------------------------------------------------------------
void ARM_Right_Open(void);
void ARM_Right_Close(void);
void ARM_Right_Front(void);

#endif // ARMSCONTROL_H
