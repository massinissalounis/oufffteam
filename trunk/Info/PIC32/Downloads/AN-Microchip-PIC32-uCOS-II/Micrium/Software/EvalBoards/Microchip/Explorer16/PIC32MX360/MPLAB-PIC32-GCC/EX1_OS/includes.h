/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                                 (c) Copyright 2006, Micrium, Weston, FL
*                                           All Rights Reserved
*
*                                           MASTER INCLUDE FILE
*********************************************************************************************************
*/

#include    <stdio.h>
#include    <stdarg.h>
#include    <stddef.h>
#include    <stdlib.h>
#include    <string.h>
#include    <lib_def.h>
#include    <lib_mem.h>
#include    <lib_str.h>
#include    <ctype.h>

#include    <app_cfg.h>
#include    <cpu_def.h>
#include    <cpu.h>
#include    <ucos_ii.h>

#include    <p32xxxx.h>
#include    "int.h"
#include    "CoreTimer.h"
#include    "ports.h"

#include    <bsp.h>
