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
#define  BEACON_REGISTER	        0x0011
//#define  COLOR_CONTROL_REGISTER     0x0012

#define  AX12_UART_FIFO				0x0020 // RBR + THR registers
#define  AX12_UART_STATUS			0x0025 // LSR regsiter
#define  AX12_UART_LCR				0x0023 
#define  AX12_UART_DLL				0x0020 
#define  AX12_UART_DLM				0x0021 

#define  AX12_UART_MASK_DATA_READY  0x01 // Data ready bit (=1 if data received in FIFO)
#define  AX12_UART_MASK_DATA_SENT   0x40 // Transmitter empty bit (=1 if buffer is empty)

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

#define AX12_REG_GOAL_POSITION 		0x1E
#define AX12_REG_ALARM_SHUTDOWN		0x12
#define AX12_REG_TEMPERATURE_LIMIT	0x0B
#define AX12_REG_MAX_TORQUE			0x0E
#define AX12_REG_TORQUE_LIMIT		0x22
#define AX12_REG_CW_LIMIT			0x06
#define AX12_REG_CCW_LIMIT			0x08
#define AX12_REG_TORQUE_ENABLE		0x18
#define AX12_REG_SPEED				0x20

/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/    

void AX12_UART_Init (void);

CPU_INT08U AX12_UART_Read_Status (void);
CPU_INT08U AX12_UART_Data_Sent (void);

void AX12_UART_Write (CPU_INT08U data);
void AX12_Dual_Write_Position_Sync (CPU_INT08U ax12_id1, CPU_INT08U ax12_id2, CPU_INT08U setpoint1_high, CPU_INT08U setpoint1_low, CPU_INT08U setpoint2_high, CPU_INT08U setpoint2_low);
void AX12_Write_Position_Sync (CPU_INT08U ax12_id, CPU_INT08U setpoint_high, CPU_INT08U setpoint_low);
void AX12_Dual_Write_Torque_On_Sync (CPU_INT08U ax12_id1, CPU_INT08U ax12_id2);
void AX12_Write_Torque_On_Sync (CPU_INT08U ax12_id);
CPU_INT08U AX12_Write_Reg_Sync (CPU_INT08U ax12_id, CPU_INT08U reg_address, CPU_INT08U data);
CPU_INT08U AX12_Write_Reg_2_Datas_Sync( CPU_INT08U ax12_id, CPU_INT08U reg_address, CPU_INT08U data1, CPU_INT08U data2);

void QUAD_Latch (void);
void QUAD_Wait_for_Latch (void);
CPU_INT16S QUADD_Read (void);
CPU_INT16S QUADG_Read (void);

CPU_INT08U GPIO_Action (CPU_INT08U bit_position, CPU_INT08U bit_value);

void BSPFPGA_Reset(void);
