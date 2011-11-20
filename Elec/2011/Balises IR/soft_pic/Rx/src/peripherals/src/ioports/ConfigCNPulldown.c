#include <ports.h>

#if defined(__dsPIC33E__) || defined(__dsPIC24E)

/********************************************************************
* Function Name     : ConfigCNPulldownPortA
* Description       : Configures the internal pull-up resistor bits for Port A
* Parameters        : None
* Return Value      : None
*********************************************************************/

#ifdef _CNIEA0

void ConfigCNPulldownPortA(unsigned int config)
{
    CNPDA = config;
}

#endif
/********************************************************************
* Function Name     : ConfigCNPulldownPortB
* Description       : Configures the internal pull-up resistor bits for Port B
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEB0

void ConfigCNPulldownPortB(unsigned int config)
{
    CNPDB = config;
}

#endif
/********************************************************************
* Function Name     : ConfigCNPulldownPortC
* Description       : Configures the internal pull-up resistor bits for Port C
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPulldownPortC(unsigned int config)
{
    CNPDC = config;
}

/********************************************************************
* Function Name     : ConfigCNPulldownPortD
* Description       : Configures the internal pull-up resistor bits for Port D
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPulldownPortD(unsigned int config)
{
    CNPDD = config;
}

/********************************************************************
* Function Name     : ConfigCNPulldownPortE
* Description       : Configures the internal pull-up resistor bits for Port E
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPulldownPortE(unsigned int config)
{
    CNPDE = config;
}

/********************************************************************
* Function Name     : ConfigCNPulldownPortF
* Description       : Configures the internal pull-up resistor bits for Port F
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPulldownPortF(unsigned int config)
{
    CNPDF = config;
}

/********************************************************************
* Function Name     : ConfigCNPulldownPortG
* Description       : Configures the internal pull-up resistor bits for Port G
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigCNPulldownPortG(unsigned int config)
{
    CNPDG = config;
}

/********************************************************************
* Function Name     : ConfigCNPulldownPortH
* Description       : Configures the internal pull-up resistor bits for Port H
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef __CNIEH0

void ConfigCNPulldownPortH(unsigned int config)
{
    CNPDH = config;
}

#endif

/********************************************************************
* Function Name     : ConfigCNPulldownPortJ
* Description       : Configures the internal pull-up resistor bits for Port J
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef __CNIEJ0

void ConfigCNPulldownPortJ(unsigned int config)
{
    CNPDJ = config;
}

#endif
/********************************************************************
* Function Name     : ConfigCNPulldownPortK
* Description       : Configures the internal pull-up resistor bits for Port K
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEK0

void ConfigCNPulldownPortK(unsigned int config)
{
    CNPDK = config;
}

#endif


#endif
