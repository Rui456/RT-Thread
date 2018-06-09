/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "stm32f4xx_eth.h"
#endif

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

#ifdef RT_USING_GDB
#include <gdb_stub.h>
#endif

void rt_init_thread_entry(void* parameter)
{
    /* GDB STUB */
#ifdef RT_USING_GDB
    gdb_set_device("uart6");
    gdb_start();
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* register ethernetif device */
        eth_system_device_init();

        rt_hw_stm32_eth_init();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
#endif
}
#include "led.h"
int rt_application_init()
{
    rt_thread_t tid,tid2,tid3,tid4,tid5;
	

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

//		tid2 = rt_thread_create(
//														"led demo",
//														led_flow,RT_NULL,
//														LED_STACK_SIZE,LED_PRIORITY,LED_TIME_SLICE
//														);
//		if(tid2 != RT_NULL)
//				rt_thread_startup(tid2);
	
		tid3 = rt_thread_create("led init",
														led_init,RT_NULL,
														1000,10,10);
	
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);

		tid3 = rt_thread_create("led red",
														led_on,(void*)53,
														1000,20,10);
	
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);
		tid4 = rt_thread_create("led Green",
														led_on,(void*)54,
														1000,20,10);
    if (tid4 != RT_NULL)
        rt_thread_startup(tid4);
	
		tid5 = rt_thread_create("led Blue",
														led_on,(void*)55,
														1000,20,10);
    if (tid5 != RT_NULL)
        rt_thread_startup(tid5);
	
	

    return 0;
}
