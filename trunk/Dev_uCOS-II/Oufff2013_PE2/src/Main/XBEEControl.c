#include "AppIncludes.h"
#include "XBEEControl.h"

void XBEE_Init(void)
{
	
}

void XBEE_Rx_handler(char data_received)
{
    LED_Toggle(4);
    AppDebugMsg("XBEE Handler ");
}


void XBEE_SendPosition(void)
{
	
}