#include<ports.h>

void CloseINTCN(void)
{
    /* Disables CN interrupt*/
    _CNIE = 0;
    _CNIF = 0;
}

