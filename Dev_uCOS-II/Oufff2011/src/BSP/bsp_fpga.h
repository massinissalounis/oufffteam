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
#define  AX12_UART_FIFO					0x0100 // RBR + THR registers
#define  AX12_UART_STATUS				0x0102 // LSR regsiter

#define  AX12_UART_MASK_DATA_READY  0x01 // Data ready bit (=1 if data received in FIFO)
#define  AX12_UART_MASK_DATA_SENT   0x40 // Transmitter empty bit (=1 if buffer is empty)

#define  AX12_FL_ID			        0x01
#define  AX12_FR_ID			        0x02
#define  AX12_TL_ID			        0x03
#define  AX12_TR_ID			        0x04

#define  AX12_CMD_PING				0x01
#define  AX12_CMD_READ_DATA         0x02
#define  AX12_CMD_WRITE_DATA        0x03
#define  AX12_CMD_REG_WRITE         0x04
#define  AX12_CMD_ACTION            0x05
#define  AX12_CMD_RESET             0x06
#define  AX12_CMD_SYNC_WRITE        0x83

#define AX12_ERROR_MASK_INSTRUCTION	0x40
#define AX12_ERROR_MASK_OVERLOAD	0x20
#define AX12_ERROR_MASK_CHECKSUM	0x10
#define AX12_ERROR_MASK_RANGE		0x08
#define AX12_ERROR_MASK_OVERHEATING 0x04
#define AX12_ERROR_MASK_ANGLE		0x02
#define AX12_ERROR_MASK_VOLTAGE		0x01



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
