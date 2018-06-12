/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>
#include <board.h>
#include "led.h"


int main(void)
{
  /* user app entry */
    rt_thread_t tid,tid2,tid3,tid4,tid5;
	rt_uint8_t led_no[3];
	
//	tid1 = rt_thread_create(
//							"led demo",
//							led_flow,RT_NULL,
//							LED_STACK_SIZE,LED_PRIORITY,LED_TIME_SLICE
//							);
//	if(tid1 != RT_NULL)
//			rt_thread_startup(tid1);
	
	/* led init */
	tid2 = rt_thread_create("led init",
							led_init,RT_NULL,
							1000,10,10);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

	led_no[0] = 53;
	led_no[1] = 54;
	led_no[2] = 55;
	
	/* led red */
	tid3 = rt_thread_create("led red",
							led_on,(void*)(&led_no[0]),
							1000,20,10);
    if (tid3 != RT_NULL)
        rt_thread_startup(tid3);
	
	/* led green */
	tid4 = rt_thread_create("led Green",
							led_on,(void*)(&led_no[1]),
							1000,20,10);
    if (tid4 != RT_NULL)
        rt_thread_startup(tid4);
	
	/* led blue */
	tid5 = rt_thread_create("led Blue",
							led_on,(void*)(&led_no[2]),
							1000,20,10);
    if (tid5 != RT_NULL)
        rt_thread_startup(tid5);
	
    return 0;
}





