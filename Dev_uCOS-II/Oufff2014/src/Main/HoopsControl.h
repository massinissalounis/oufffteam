// Control lib for the hoops - Oufffteam 2014
// Pierre - Emmanuel GAILLARDON

#ifndef  HOOPSCONTROL_H
#define  HOOPSCONTROL_H

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
#define AX12_LEFT_HOOP_ID			(0x12)
#define AX12_RIGHT_HOOP_ID			(0x0F)

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/   

// HOOPS ---------------------------------------------------------------------------------
void HOOPS_InitReg(void);
void HOOPS_SetSpeed(void);
void HOOPS_Up(void);
void HOOPS_Down(void);

// HOOP Back ----------------------------------------------------------------------------
void HOOP_Back_Up(void);
void HOOP_Back_Down(void);

#endif // HOOPSCONTROL_H
