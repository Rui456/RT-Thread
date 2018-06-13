/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stm32f3xx.h>
#include <stm32f3xx_hal.h>
#include <rtthread.h>
#if \
    defined(SOC_STM32F410T8)||\
    defined(SOC_STM32F410TB)
#define STM32F4xx_PIN_NUMBERS 36
#elif \
    defined(SOC_STM32F334C6)||\
    defined(SOC_STM32F401CC)||\
    defined(SOC_STM32F401CD)||\
    defined(SOC_STM32F401CE)||\
    defined(SOC_STM32F410C8)||\
    defined(SOC_STM32F423CH)
#define STM32F4xx_PIN_NUMBERS 48
#endif

#if \
    defined(SOC_STM32F405RG)||\
    defined(SOC_STM32F405VG)||\
    defined(SOC_STM32F405ZG)
//#define STM32F405xx
#define STM32_SRAM_SIZE (192-64)
#elif \
    defined(SOC_STM32F334C6)||\
    defined(SOC_STM32F410TB)
//#define STM32F410Tx
#define STM32_SRAM_SIZE 12
#endif


#define STM32_SRAM_END          (0x20000000 + STM32_SRAM_SIZE * 1024)

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN  ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN  (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN  ((void *)&__bss_end)
#endif
#define HEAP_END    STM32_SRAM_END

#endif
extern void rt_hw_board_init(void);

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)


// <<< Use Configuration Wizard in Context Menu >>>
