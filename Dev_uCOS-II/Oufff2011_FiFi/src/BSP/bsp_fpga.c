/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                              (c) Copyright 2006, Micrium, Inc., Weston, FL
*                                           All Rights Reserved
*
*                                          Board Support Package
*                                               Oufff TEAM
*                                               O'CORE
*********************************************************************************************************
*/

#include "AppIncludes.h"

void QUAD_Latch (void)
{
	PMP_Write(QUAD_LATCH_REGISTER,0xFF); // Latch quadrature counters
}

void QUAD_Wait_for_Latch (void)
{
	while(PMP_Read(QUAD_LATCH_REGISTER)!=0x00);
}

CPU_INT16S QUADD_Read (void)
{
	CPU_INT16S value;
	value = PMP_Read(QUADD_HI_REGISTER) <<8;
	value = value | PMP_Read(QUADD_LO_REGISTER);
	return value;
}

CPU_INT16S QUADG_Read (void)
{
	CPU_INT16S value;
	value = PMP_Read(QUADG_HI_REGISTER) <<8;
	value = value | PMP_Read(QUADG_LO_REGISTER);
	return value;
}

//Inter couleur transféré sur le pic
/*CPU_INT08U COLOR_Read (void)
{
	CPU_INT08U value;
	value = PMP_Read(GPIO_REGISTER);
	return value;
}*/

void BSPFPGA_Reset(void)
{
	PMP_Write(RESET_REGISTER,0xFF);
	PMP_Write(RESET_REGISTER,0x00);
	PMP_Write(LED_REGISTER,0x01);
}
