#include "AppIncludes.h"
#include "bsp_ax12.h"

// Code from Robotis modified by PE
// 2012

// Initially, Use of Rx interupt and software filling of a queue

// TODO ADD MUTEX on PMP !!


#define AX12_BUF_SIZE	256


unsigned char Ax12Buffer[AX12_BUF_SIZE] = {0};
double gfByteTransTime_us;
unsigned int gwCountNum;
unsigned int gwTimeoutCountNum;
unsigned int gwReturnDelayCountNum;

////////
/// HAL
////////

int bsp_ax12_open()
{
	AX12_UART_Init();

	return 1;
}

void bsp_ax12_close(void)
{
	// Closing device
}

void bsp_ax12_clear(void)
{
	// Reset serial interface
}

int bsp_ax12_tx( unsigned char *pPacket, int numPacket )
{
	// Transmiting data
	// *pPacket: data array pointer
	// numPacket: number of data array
	// Return: number of data transmitted. -1 is error.	
	int count;
	
//	cli(); Stop ITs ??
//	DIR_TXD; // Autonatic in CBE's IP
	for( count=0; count<numPacket; count++ )
	{
		while(AX12_UART_Data_Sent()!=1);
		AX12_UART_Write(pPacket[count]);
	}
	while(AX12_UART_Data_Sent()!=1);
//	DIR_RXD;  // Automatic in CBE's IP
//	sei();
	return count;
}

CPU_INT08U bsp_ax12_rx( CPU_INT08U *pPacket, CPU_INT08U max_rx)
{
	// Recieving data
	// *pPacket: data array pointer
	// numPacket: number of data array
	// Return: number of data recieved. -1 is error.
	CPU_INT08U count=0;
	CPU_INT08U timeout=20;
	CPU_INT08U test=0;
	CPU_INT08U gg[8];
		
	// Wait for Data
	while(AX12_UART_Data_Ready()!=1	&& timeout>0)
	{
		BSP_Dly(10);
		timeout--;
	}

	// Read max_rx data
	while((AX12_UART_Data_Ready()==1) && count<max_rx)
	{
		test=AX12_UART_Read();
		gg[count]=test;
		pPacket[count]=test;
		count++;

		BSP_Dly(15);
	}

	count++;

	char uart_buffer[8];
	char *buffer_ptr;

	AppDebugMsg("GG0 ");
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[0], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[1], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[2], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[3], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[4], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[5], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);
	buffer_ptr = (char*) Str_FmtNbr_32 ((CPU_FP32) gg[6], (CPU_INT08U) 4, (CPU_INT08U) 1, (CPU_BOOLEAN) DEF_YES, (CPU_BOOLEAN) DEF_YES, uart_buffer);
	AppDebugMsg(buffer_ptr);

	// Empty the queue (in case)
	while(AX12_UART_Data_Ready()==1)
	{
		AX12_UART_Read();
	}
 
	return count;
}

void bsp_ax12_set_timeout( int NumRcvByte )
{
	// Start stop watch
	// NumRcvByte: number of recieving data(to calculate maximum waiting time)
	gwCountNum = 0;	
	gwTimeoutCountNum = (NumRcvByte + 10) + gwReturnDelayCountNum;
}

int bsp_ax12_timeout(void)
{
	// Check timeout
	// Return: 0 is false, 1 is true(timeout occurred)
	gwCountNum++;
		
	if( gwCountNum > gwTimeoutCountNum )
	{
		return 1;
	}
	
	BSP_Dly(10);
	return 0;
}


CPU_INT08U bsp_ax12_fill_checksum(CPU_INT08U *packet, CPU_INT08U packl)
{
	CPU_INT16U checksum=0;
	CPU_INT08U idx;
	
	for(idx=2; idx<packl-1; idx++)
	{
		checksum+=packet[idx];
	}
	checksum=~checksum;

	packet[packl-1]=(CPU_INT08U) checksum;
	return (CPU_INT08U)checksum;
}

CPU_INT08U bsp_ax12_ping (CPU_INT08U ax12_id)
{
	CPU_INT08U packet[6];
	CPU_INT08U status=0xAA;

	// Prepare Ping packet
    packet[0] = 0xFF;
	packet[1] = 0xFF;
	packet[2] = ax12_id; // ID
	packet[3] = 2; // LENGTH
	packet[4] = AX12_CMD_PING; // INSTRUCTION
	bsp_ax12_fill_checksum(packet,6); // CHECKSUM

	// Send Packet
while(1)
{
	bsp_ax12_tx(packet,6);

	// Read Status Packet
	status=bsp_ax12_rx(packet,6);
	
	BSP_Dly(50);
}
	return packet[4];
}

/*

///
/// DXL Ctrl
///

#define ID					(2)
#define LENGTH				(3)
#define INSTRUCTION			(4)
#define ERRBIT				(4)
#define PARAMETER			(5)
#define DEFAULT_BAUDNUMBER	(1)

unsigned char gbInstructionPacket[MAXNUM_TXPARAM+10] = {0};
unsigned char gbStatusPacket[MAXNUM_RXPARAM+10] = {0};
unsigned char gbRxPacketLength = 0;
unsigned char gbRxGetLength = 0;
int gbCommStatus = COMM_RXSUCCESS;
int giBusUsing = 0;


int dxl_initialize( )
{
	gbCommStatus = COMM_RXSUCCESS;
	giBusUsing = 0;
	return 1;
}

void dxl_tx_packet()
{
	unsigned char i;
	unsigned char TxNumByte, RealTxNumByte;
	unsigned char checksum = 0;

	if( giBusUsing == 1 )
		return;
	
	giBusUsing = 1;

	if( gbInstructionPacket[LENGTH] > (MAXNUM_TXPARAM+2) )
	{
		gbCommStatus = COMM_TXERROR;
		giBusUsing = 0;
		return;
	}
	
	if( gbInstructionPacket[INSTRUCTION] != INST_PING
		&& gbInstructionPacket[INSTRUCTION] != INST_READ
		&& gbInstructionPacket[INSTRUCTION] != INST_WRITE
		&& gbInstructionPacket[INSTRUCTION] != INST_REG_WRITE
		&& gbInstructionPacket[INSTRUCTION] != INST_ACTION
		&& gbInstructionPacket[INSTRUCTION] != INST_RESET
		&& gbInstructionPacket[INSTRUCTION] != INST_SYNC_WRITE )
	{
		gbCommStatus = COMM_TXERROR;
		giBusUsing = 0;
		return;
	}
	
	gbInstructionPacket[0] = 0xff;
	gbInstructionPacket[1] = 0xff;
	for( i=0; i<(gbInstructionPacket[LENGTH]+1); i++ )
		checksum += gbInstructionPacket[i+2];
	gbInstructionPacket[gbInstructionPacket[LENGTH]+3] = ~checksum;
	
	if( gbCommStatus == COMM_RXTIMEOUT || gbCommStatus == COMM_RXCORRUPT )
		dxl_hal_clear();

	TxNumByte = gbInstructionPacket[LENGTH] + 4;
	RealTxNumByte = dxl_hal_tx( (unsigned char*)gbInstructionPacket, TxNumByte );

	if( TxNumByte != RealTxNumByte )
	{
		gbCommStatus = COMM_TXFAIL;
		giBusUsing = 0;
		return;
	}

	if( gbInstructionPacket[INSTRUCTION] == INST_READ )
		dxl_hal_set_timeout( gbInstructionPacket[PARAMETER+1] + 6 );
	else
		dxl_hal_set_timeout( 6 );

	gbCommStatus = COMM_TXSUCCESS;
}

void dxl_rx_packet()
{
	unsigned char i, j, nRead;
	unsigned char checksum = 0;

	if( giBusUsing == 0 )
		return;

	if( gbInstructionPacket[ID] == BROADCAST_ID )
	{
		gbCommStatus = COMM_RXSUCCESS;
		giBusUsing = 0;
		return;
	}
	
	if( gbCommStatus == COMM_TXSUCCESS )
	{
		gbRxGetLength = 0;
		gbRxPacketLength = 6;
	}
	
	nRead = dxl_hal_rx( (unsigned char*)&gbStatusPacket[gbRxGetLength], gbRxPacketLength - gbRxGetLength );
	gbRxGetLength += nRead;
	if( gbRxGetLength < gbRxPacketLength )
	{
		if( dxl_hal_timeout() == 1 )
		{
			if(gbRxGetLength == 0)
				gbCommStatus = COMM_RXTIMEOUT;
			else
				gbCommStatus = COMM_RXCORRUPT;
			giBusUsing = 0;
			return;
		}
	}
	
	// Find packet header
	for( i=0; i<(gbRxGetLength-1); i++ )
	{
		if( gbStatusPacket[i] == 0xff && gbStatusPacket[i+1] == 0xff )
		{
			break;
		}
		else if( i == gbRxGetLength-2 && gbStatusPacket[gbRxGetLength-1] == 0xff )
		{
			break;
		}
	}	
	if( i > 0 )
	{
		for( j=0; j<(gbRxGetLength-i); j++ )
			gbStatusPacket[j] = gbStatusPacket[j + i];
			
		gbRxGetLength -= i;		
	}

	if( gbRxGetLength < gbRxPacketLength )
	{
		gbCommStatus = COMM_RXWAITING;
		return;
	}

	// Check id pairing
	if( gbInstructionPacket[ID] != gbStatusPacket[ID])
	{
		gbCommStatus = COMM_RXCORRUPT;
		giBusUsing = 0;
		return;
	}
	
	gbRxPacketLength = gbStatusPacket[LENGTH] + 4;
	if( gbRxGetLength < gbRxPacketLength )
	{
		nRead = dxl_hal_rx( (unsigned char*)&gbStatusPacket[gbRxGetLength], gbRxPacketLength - gbRxGetLength );
		gbRxGetLength += nRead;
		if( gbRxGetLength < gbRxPacketLength )
		{
			gbCommStatus = COMM_RXWAITING;
			return;
		}
	}

	// Check checksum
	for( i=0; i<(gbStatusPacket[LENGTH]+1); i++ )
		checksum += gbStatusPacket[i+2];
	checksum = ~checksum;

	if( gbStatusPacket[gbStatusPacket[LENGTH]+3] != checksum )
	{
		gbCommStatus = COMM_RXCORRUPT;
		giBusUsing = 0;
		return;
	}
	
	gbCommStatus = COMM_RXSUCCESS;
	giBusUsing = 0;
}

void dxl_txrx_packet()
{
	dxl_tx_packet();

	if( gbCommStatus != COMM_TXSUCCESS )
		return;	
	
	do{
		dxl_rx_packet();		
	}while( gbCommStatus == COMM_RXWAITING );	
}

int dxl_get_result()
{
	return gbCommStatus;
}

void dxl_set_txpacket_id( int id )
{
	gbInstructionPacket[ID] = (unsigned char)id;
}

void dxl_set_txpacket_instruction( int instruction )
{
	gbInstructionPacket[INSTRUCTION] = (unsigned char)instruction;
}

void dxl_set_txpacket_parameter( int index, int value )
{
	gbInstructionPacket[PARAMETER+index] = (unsigned char)value;
}

void dxl_set_txpacket_length( int length )
{
	gbInstructionPacket[LENGTH] = (unsigned char)length;
}

int dxl_get_rxpacket_error( int errbit )
{
	if( gbStatusPacket[ERRBIT] & (unsigned char)errbit )
		return 1;

	return 0;
}

int dxl_get_rxpacket_length()
{
	return (int)gbStatusPacket[LENGTH];
}

int dxl_get_rxpacket_parameter( int index )
{
	return (int)gbStatusPacket[PARAMETER+index];
}

int dxl_makeword( int lowbyte, int highbyte )
{
	unsigned short word;

	word = highbyte;
	word = word << 8;
	word = word + lowbyte;
	return (int)word;
}

int dxl_get_lowbyte( int word )
{
	unsigned short temp;

	temp = word & 0xff;
	return (int)temp;
}

int dxl_get_highbyte( int word )
{
	unsigned short temp;

	temp = word & 0xff00;
	temp = temp >> 8;
	return (int)temp;
}

void dxl_ping( int id )
{
	while(giBusUsing);

	gbInstructionPacket[ID] = (unsigned char)id;
	gbInstructionPacket[INSTRUCTION] = INST_PING;
	gbInstructionPacket[LENGTH] = 2;
	
	dxl_txrx_packet();
}

int dxl_read_byte( int id, int address )
{
	while(giBusUsing);

	gbInstructionPacket[ID] = (unsigned char)id;
	gbInstructionPacket[INSTRUCTION] = INST_READ;
	gbInstructionPacket[PARAMETER] = (unsigned char)address;
	gbInstructionPacket[PARAMETER+1] = 1;
	gbInstructionPacket[LENGTH] = 4;
	
	dxl_txrx_packet();

	return (int)gbStatusPacket[PARAMETER];
}

void dxl_write_byte( int id, int address, int value )
{
	while(giBusUsing);

	gbInstructionPacket[ID] = (unsigned char)id;
	gbInstructionPacket[INSTRUCTION] = INST_WRITE;
	gbInstructionPacket[PARAMETER] = (unsigned char)address;
	gbInstructionPacket[PARAMETER+1] = (unsigned char)value;
	gbInstructionPacket[LENGTH] = 4;
	
	dxl_txrx_packet();
}

int dxl_read_word( int id, int address )
{
	while(giBusUsing);

	gbInstructionPacket[ID] = (unsigned char)id;
	gbInstructionPacket[INSTRUCTION] = INST_READ;
	gbInstructionPacket[PARAMETER] = (unsigned char)address;
	gbInstructionPacket[PARAMETER+1] = 2;
	gbInstructionPacket[LENGTH] = 4;
	
	dxl_txrx_packet();

	return dxl_makeword((int)gbStatusPacket[PARAMETER], (int)gbStatusPacket[PARAMETER+1]);
}

void dxl_write_word( int id, int address, int value )
{
	while(giBusUsing);

	gbInstructionPacket[ID] = (unsigned char)id;
	gbInstructionPacket[INSTRUCTION] = INST_WRITE;
	gbInstructionPacket[PARAMETER] = (unsigned char)address;
	gbInstructionPacket[PARAMETER+1] = (unsigned char)dxl_get_lowbyte(value);
	gbInstructionPacket[PARAMETER+2] = (unsigned char)dxl_get_highbyte(value);
	gbInstructionPacket[LENGTH] = 5;
	
	dxl_txrx_packet();
}
*/
