// BSP for AX12
// Pierre - Emmanuel GAILLARDON
// 2012

#define  AX12_FL_ID			        0x0F
#define  AX12_FR_ID			        0x12
#define  AX12_TL_ID			        0x10
#define  AX12_TR_ID			        0x11

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


int dxl_hal_open(int devIndex, float baudrate);
void dxl_hal_close(void);
void dxl_hal_clear(void);
int dxl_hal_tx( unsigned char *pPacket, int numPacket );
int dxl_hal_rx( unsigned char *pPacket, int numPacket );
void dxl_hal_set_timeout( int NumRcvByte );
int dxl_hal_timeout(void);
