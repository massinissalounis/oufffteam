// Control for the arms - Oufffteam 2012
// Pierre - Emmanuel GAILLARDON


/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  AX12_LEFT_ARM_ID			0x0F
#define  AX12_RIGHT_ARM_ID			0x12
#define  AX12_LEFT_WRIST_ID			0x0B
#define  AX12_RIGHT_WRIST_ID		0x0A
#define  AX12_ELEVATOR_ID			0x11

#define PUMP_LEFT					0x01
#define PUMP_RIGHT					0x02

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/   

void ARMS_InitReg(void);

void ARM_Left_Sleep(void);
void ARM_Right_Sleep(void);


void ELEVATOR_Level_Low(void);
void ELEVATOR_Level_Middle(void);
void ELEVATOR_Level_High(void);

void PUMP_Right_Suck(void);
void PUMP_Left_Suck(void);
void PUMP_Right_Release(void);
void PUMP_Left_Release(void);

void ARMS_Init(void);
