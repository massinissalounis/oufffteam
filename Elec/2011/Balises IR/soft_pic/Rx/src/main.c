#include "p24Hxxxx.h"
#include "define.h"
#include "BSP.h"
#include "uart.h"

//Select Internal FRC at POR
_FOSCSEL(FNOSC_FRC);
//Enable Clocl Switching and configure
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF);



int main(void)
{
	configure_pic();

	while (1)
	{


	}
	return(0);
}

