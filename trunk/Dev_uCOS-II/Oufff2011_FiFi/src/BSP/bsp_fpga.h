// BSP for FPGA's IPs
// Pierre - Emmanuel GAILLARDON


/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define  RESET_REGISTER				0x0000
#define  LED_REGISTER				0x0001
#define  QUAD_LATCH_REGISTER        0x0008
#define  QUADD_LO_REGISTER          0x0009
#define  QUADD_HI_REGISTER          0x000A
#define  QUADG_LO_REGISTER          0x000B
#define  QUADG_HI_REGISTER          0x000C
#define  GPIO_REGISTER		        0x0010

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/    

void QUAD_Latch (void);
CPU_INT16S QUADD_Read (void);
CPU_INT16S QUADG_Read (void);
void QUAD_Wait_for_Latch (void);

void BSPFPGA_Reset(void);
CPU_INT08U COLOR_Read (void);
