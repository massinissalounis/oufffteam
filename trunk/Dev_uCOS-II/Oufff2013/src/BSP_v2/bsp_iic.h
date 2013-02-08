// BSP for iic
// Benjamin Minguez

#include "i2c.h"
//#include "ucos_ii.h"


/***********************************************************************************************************/
/*                                            TYPE                                                         */
/***********************************************************************************************************/
typedef enum
{
	I2C_MASTER_MODE = 0,
	I2C_SLAVE_MODE
} I2C_RUNNING_MODE;

/*********************************************************************************************************/
/*                                           I2C instance strucure                                       */
/*********************************************************************************************************/
typedef struct Iic
{
	I2C_MODULE        DeviceId;
    I2C_RUNNING_MODE  DeviceMode;
	I2C_7_BIT_ADDRESS SlaveAddress;
	I2C_CONFIGURATION DeviceConfig;
	I2C_ADDRESS_MODE  DeviceAddressMode;
 	I2C_STATUS        DeviceStatus;

	int IicIntPrio;
	int IicIntSubPrio;

	int   NbAddrInSlave;
	int   TrnWriteLength;
	int   TrnReadLength;
	UINT8 *AddrInSlave;
	UINT8 *WriteBuffer;
	UINT8 *ReadBuffer;

	int Option;
	UINT8 *error;
	int OperationInProgress;

	OS_EVENT *IicSem;

} IicDevice;

/*********************************************************************************************************/
/*                                                DEFINES                                                */
/*********************************************************************************************************/


// semaphore
#define IIC_SEMAPHORE_NB 16

// function return value
#define IIC_SUCCESS                   0
#define IIC_FAILURE                   1
#define IIC_DEVICE_NOT_IN_MASTER_MODE 2
#define IIC_DEVICE_NOT_IN_SLAVE_MODE  3
#define IIC_DEVICE_IS_NOT_READY       4 
#define IIC_DEVICE IS STOP            5
#define IIC_OPERATION_ONGOING         6
#define IIC_BUS_COLLISION             7
#define IIC_START_FAIL                8
#define IIC_REPEATED_START_FAIL       9
#define IIC_STOP_FAIL                 10
#define IIC_SEND_SLAVE_ADDR_FAIL      11
#define IIC_BYTE_NOT_ACKNOLEDGE       12
#define IIC_SEND_ADDR_IN_SLAVE_FAIL   13
#define IIC_SEND_BYTE_FAIL            14
#define IIC_RECEIVE_OVERFLOW          15
#define IIC_RECEIVE_DATA_FAIL         16
#define IIC_RECEIVE_ACKNOWLEDGE_FAIL  17

// Register address


// Control register
#define IIC_CTRL_SEN    (1)
#define IIC_CTRL_RSEN   (1<<1)
#define IIC_CTRL_PEN    (1<<2)
#define IIC_CTRL_RCEN   (1<<3)
#define IIC_CTRL_ACKEN  (1<<4)
#define IIC_CTRL_ACKDT  (1<<5)
#define IIC_CTRL_STREN  (1<<6)
#define IIC_CTRL_GCEN   (1<<7)
#define IIC_CTRL_SMEN   (1<<8)
#define IIC_CTRL_DISSLW (1<<9)
#define IIC_CTRL_A10M   (1<<10)
#define IIC_CTRL_STRICT (1<<11)
#define IIC_CTRL_SCLREL (1<<12)
#define IIC_CTRL_SIDL   (1<<13)
#define IIC_CTRL_FRZ    (1<<14)
#define IIC_CTRL_ON     (1<<15)

// Status register
#define IIC_STAT_TBF     (1)
#define IIC_STAT_RBF     (1<<1)
#define IIC_STAT_RWB     (1<<2)
#define IIC_STAT_S       (1<<3)
#define IIC_STAT_P       (1<<4)
#define IIC_STAT_DAB     (1<<5)
#define IIC_STAT_I2COV   (1<<6)
#define IIC_STAT_IWCOL   (1<<7)
#define IIC_STAT_ADD10   (1<<8)
#define IIC_STAT_GCSTAT  (1<<9)
#define IIC_STAT_BCL     (1<<10)
#define IIC_STAT_TRSTAT  (1<<14)
#define IIC_STAT_ACKSTAT (1<<15)

// Interrupt registers
// control
#define IIC_INT_CTRL_MIE (1<<31)
#define IIC_INT_CTRL_SIE (1<<30)
#define IIC_INT_CTRL_BIE (1<<29)
// status
#define IIC_INT_STAT_MIE (1<<31)
#define IIC_INT_STAT_SIE (1<<30)
#define IIC_INT_STAT_BIE (1<<29)
// priority
#define IIC_INT_PRIO_7    (7<<10)
#define IIC_INT_PRIO_6    (6<<10)
#define IIC_INT_PRIO_5    (5<<10)
#define IIC_INT_PRIO_4    (4<<10)
#define IIC_INT_PRIO_3    (3<<10)
#define IIC_INT_PRIO_2    (2<<10)
#define IIC_INT_PRIO_1    (1<<10)
#define IIC_INT_PRIO_0    (0<<10)
#define IIC_INT_SUBPRIO_3 (3<<8)
#define IIC_INT_SUBPRIO_2 (2<<8)
#define IIC_INT_SUBPRIO_1 (1<<8)
#define IIC_INT_SUBPRIO_0 (0<<8)

/***********************************************************************************************************/
/*                                            PROTOTYPES                                                   */
/***********************************************************************************************************/

// I2C Robot
static int Iic_Init(IicDevice *InstancePtr, I2C_MODULE id, I2C_RUNNING_MODE DeviceMode);
static int Iic_int_init(IicDevice *InstancePtr, OS_EVENT *MySem);
static int Iic_reset(IicDevice *InstancePtr);
//static int Iic_get_pos()

// Local functions
static int  IicWrite(IicDevice *InstancePtr);
static int  IicRead(IicDevice *InstancePtr);



