#include <ports.h>

/********************************************************************
* Function Name     : ConfigIntCN
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
#if defined(__dsPIC30F__) || defined(__dsPIC33F__) ||  defined(__PIC24H__)

void ConfigIntCN(long int config)
{

    _CNIF = 0;
    CNEN1 = (unsigned int)config;

#if defined(_CN16IE) || defined(_CN17IE) || \
    defined(_CN18IE) || defined(_CN19IE) || \
    defined(_CN20IE) || defined(_CN21IE) || \
    defined(_CN22IE) || defined(_CN23IE) || \
    defined(_CN24IE) || defined(_CN25IE) || \
    defined(_CN26IE) || defined(_CN27IE) || \
    defined(_CN28IE) || defined(_CN29IE) || \
    defined(_CN30IE) || defined(_CN31IE)
    CNEN2 = (unsigned int)(config >> 16);
#endif

    config = config >> 24;
    _CNIP = config;
    _CNIE = config >> 3; 
}

#endif

#if defined(__dsPIC33E__) || defined(__dsPIC24E)

/********************************************************************
* Function Name     : ConfigIntCNPortA
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEA0
void ConfigIntCNPortA(long int config)
{
    _CNIF = 0;
    CNENA = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}
#endif
/********************************************************************
* Function Name     : ConfigIntCNPortB
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEB0
void ConfigIntCNPortB(long int config)
{

    _CNIF = 0;
    CNENB = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}
#endif
/********************************************************************
* Function Name     : ConfigIntCNPortC
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
void ConfigIntCNPortC(long int config)
{

    _CNIF = 0;
    CNENC = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

/********************************************************************
* Function Name     : ConfigIntCNPortD
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
void ConfigIntCNPortD(long int config)
{

    _CNIF = 0;
    CNEND = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

/********************************************************************
* Function Name     : ConfigIntCNPortE
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigIntCNPortE(long int config)
{

    _CNIF = 0;
    CNENE = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

/********************************************************************
* Function Name     : ConfigIntCNPortF
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/

void ConfigIntCNPortF(long int config)
{

    _CNIF = 0;
    CNENF = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

/********************************************************************
* Function Name     : ConfigIntCNPortG
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
void ConfigIntCNPortG(long int config)
{

    _CNIF = 0;
    CNENG = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

/********************************************************************
* Function Name     : ConfigIntCNPortH
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEH0

void ConfigIntCNPortH(long int config)
{

    _CNIF = 0;
    CNENH = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

#endif

/********************************************************************
* Function Name     : ConfigIntCNPortJ
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEJ0

void ConfigIntCNPortJ(long int config)
{

    _CNIF = 0;
    CNENJ = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

#endif

/********************************************************************
* Function Name     : ConfigIntCNPortK
* Description       : Enables/Disables the individual CN interrupts 
*                     and sets priority and enables/disables CN.
* Parameters        : None
* Return Value      : None
*********************************************************************/
#ifdef _CNIEK0

void ConfigIntCNPortK(long int config)
{

    _CNIF = 0;
    CNENK = (unsigned int)config;
    config = config >> 16;
    _CNIP = config & 0x07;
    _CNIE = (config & 0x08) >> 3; ; 
}

#endif

#endif
