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

//---------------------------------------------
// TSOP STATE DEFINITION
//---------------------------------------------
#define TSOP33_1	0
#define TSOP40_1	1
#define TSOP33_2	2
#define TSOP40_2	3
#define TSOP33_3	4
#define TSOP40_3	5
#define TSOP33_4	6
#define TSOP40_4	7
#define TSOP33_5	8
#define TSOP40_5	9
#define TSOP33_6	10
#define TSOP40_6	11
#define TSOP33_7	12
#define TSOP40_7	13
#define TSOP33_8	14
#define TSOP40_8	15
#define TSOP33_9	16
#define TSOP40_9	17
#define TSOP33_10	18
#define TSOP40_10	19
#define TSOP33_11	20
#define TSOP40_11	21
#define TSOP33_12	22
#define TSOP40_12	23
#define TSOP33_13	24
#define TSOP40_13	25
#define TSOP33_14	26
#define TSOP40_14	27
#define TSOP33_15	28
#define TSOP40_15	29
#define TSOP33_16	30
#define TSOP40_16	31