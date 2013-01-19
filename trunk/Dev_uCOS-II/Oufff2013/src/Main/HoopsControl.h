// Control lib for the hoops - Oufffteam 2013
// Pierre - Emmanuel GAILLARDON

#ifndef  HOOPSCONTROL_H
#define  HOOPSCONTROL_H

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
#define AX12_FRONT_HOOP_ID			(0x0F)
#define AX12_BACK_HOOP_ID			(0x12)

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

// HOOP Front -----------------------------------------------------------------------------
void HOOP_Front_Up(void);
void HOOP_Front_Down(void);

// HOOP Back ----------------------------------------------------------------------------
void HOOP_Back_Up(void);
void HOOP_Back_Down(void);

#endif // HOOPSCONTROL_H
