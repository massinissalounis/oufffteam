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

#define  AX12_UART_FIFO				0x0020 // RBR + THR registers
#define  AX12_UART_STATUS			0x0025 // LSR regsiter
#define  AX12_UART_LCR				0x0023 
#define  AX12_UART_DLL				0x0020 
#define  AX12_UART_DLM				0x0021 

#define  AX12_UART_MASK_DATA_READY  0x01 // Data ready bit (=1 if data received in FIFO)
#define  AX12_UART_MASK_DATA_SENT   0x40 // Transmitter empty bit (=1 if buffer is empty)



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
//CPU_INT08U COLOR_Read (void);
