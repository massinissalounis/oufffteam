#include <ports.h>

/********************************************************************
* Function Name     : ConfigCNPullups
* Description       : Configures the internal pull-up resistor bits
* Parameters        : None
* Return Value      : None
*********************************************************************/
#if defined(__dsPIC30F__) || defined(__dsPIC33F__) ||  defined(__PIC24H__)

void ConfigCNPullups(long int config)
{
    CNPU1 = (unsigned int)config;

#if defined(_CN16IE) || defined(_CN17IE) || \
    defined(_CN18IE) || defined(_CN19IE) || \
    defined(_CN20IE) || defined(_CN21IE) || \
    defined(_CN22IE) || defined(_CN23IE) || \
    defined(_CN24IE) || defined(_CN25IE) || \
    defined(_CN26IE) || defined(_CN27IE) || \
    defined(_CN28IE) || defined(_CN29IE) || \
    defined(_CN30IE) || defined(_CN31IE)
    CNPU2 = (unsigned int)(config >> 16);
#endif
}
/* end of function ConfigCNPullups */

#endif


#if defined(__dsPIC33E__) || defined(__dsPIC24E)

/********************************************************************
* Function Name     : ConfigCNPullupsPortA
* Description       : Configures the internal pull-up resistor bits for Port A
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEA0
void ConfigCNPullupsPortA(unsigned int config)
{
    CNPUA = config;
}
#endif
/********************************************************************
* Function Name     : ConfigCNPullupsPortB
* Description       : Configures the internal pull-up resistor bits for Port B
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEB0

void ConfigCNPullupsPortB(unsigned int config)
{
    CNPUB = config;
}
#endif
/********************************************************************
* Function Name     : ConfigCNPullupsPortC
* Description       : Configures the internal pull-up resistor bits for Port C
* Parameters        : None
* Return Value      : None
*********************************************************************/


void ConfigCNPullupsPortC(unsigned int config)
{
    CNPUC = config;
}


/********************************************************************
* Function Name     : ConfigCNPullupsPortD
* Description       : Configures the internal pull-up resistor bits for Port D
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPullupsPortD(unsigned int config)
{
    CNPUD = config;
}

/********************************************************************
* Function Name     : ConfigCNPullupsPortE
* Description       : Configures the internal pull-up resistor bits for Port E
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPullupsPortE(unsigned int config)
{
    CNPUE = config;
}

/********************************************************************
* Function Name     : ConfigCNPullupsPortF
* Description       : Configures the internal pull-up resistor bits for Port F
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPullupsPortF(unsigned int config)
{
    CNPUF = config;
}

/********************************************************************
* Function Name     : ConfigCNPullupsPortG
* Description       : Configures the internal pull-up resistor bits for Port G
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPullupsPortG(unsigned int config)
{
    CNPUG = config;
}

/********************************************************************
* Function Name     : ConfigCNPullupsPortH
* Description       : Configures the internal pull-up resistor bits for Port H
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEH0

void ConfigCNPullupsPortH(unsigned int config)
{
    CNPUH = config;
}

#endif
/********************************************************************
* Function Name     : ConfigCNPullupsPortJ
* Description       : Configures the internal pull-up resistor bits for Port J
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef __CNIEJ0

void ConfigCNPullupsPortJ(unsigned int config)
{
    CNPUJ = config;
}

#endif
/********************************************************************
* Function Name     : ConfigCNPullupsPortK
* Description       : Configures the internal pull-up resistor bits for Port K
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEK0

void ConfigCNPullupsPortK(unsigned int config)
{
    CNPUK = config;
}

#endif

#endif
