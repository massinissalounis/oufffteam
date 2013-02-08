// XBEE communication control - Oufffteam 2012
// Pierre - Emmanuel GAILLARDON

#ifndef  XBEECONTROL_H
#define  XBEECONTROL_H

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/   

void XBEE_Init(void);
void XBEE_Rx_handler(char data_received);
void XBEE_SendPosition(void);

#endif // XBEECONTROL_H
