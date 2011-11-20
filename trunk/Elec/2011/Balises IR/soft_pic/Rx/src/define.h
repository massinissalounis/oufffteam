//---------------------------------------------
// Communication protocol
//---------------------------------------------

// FIRST 4bits: address LAST 4bits: order

#define B1_ADDRESS 0x1F
#define B2_ADDRESS 0x2F
#define B3_ADDRESS 0x3F

#define ORDER_SEND_ACK 0xF0
#define ORDER_START_EMITTING 0xF1
#define ORDER_STOP_EMITTING 0xF2
#define ORDER_START_LED 0xF3
#define ORDER_STOP_LED 0xF4