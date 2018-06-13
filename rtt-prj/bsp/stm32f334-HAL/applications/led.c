#include "led.h"

rt_sem_t sem_led;


void led_flow(void* param)
{
	rt_pin_write(LEDR,1);
	rt_pin_write(LEDG,1);
	rt_pin_write(LEDB,1);
	
	rt_pin_mode(LEDR,PIN_MODE_OUTPUT_OD);
	rt_pin_mode(LEDG,PIN_MODE_OUTPUT_OD);
	rt_pin_mode(LEDB,PIN_MODE_OUTPUT_OD);

	while(1)
	{
		for(rt_uint8_t i = 0;i <3;i++)
		{
			/* close led */
			rt_pin_write(LEDR+i,1);
			rt_pin_write(LEDR+((i+2)%3),1);
			/* open led */
			rt_pin_write(LEDR+((i+1)%3),0);
			rt_thread_delay(10);
		}
	}
}

void led_init(void* param)
{
	rt_pin_write(53,1);
	rt_pin_write(54,1);
	rt_pin_write(55,1);
	
	rt_pin_mode(53,PIN_MODE_OUTPUT_OD);
	rt_pin_mode(54,PIN_MODE_OUTPUT_OD);
	rt_pin_mode(55,PIN_MODE_OUTPUT_OD);

	rt_pin_write(53,1);
	rt_pin_write(54,1);
	rt_pin_write(55,1);
	
	sem_led = rt_sem_create("led on sem",1,RT_IPC_FLAG_FIFO);
}


void led_on(void* param)
{
	rt_err_t result;
	rt_base_t tmp = (rt_base_t)param;
	rt_uint8_t led = *(rt_uint8_t*)param;
	
	rt_kprintf("param = %ld\r\n",tmp);
	
	while(1)
	{
		result = rt_sem_take(sem_led,RT_WAITING_FOREVER);
		if(result == RT_EOK){
			switch(led)
			{
				case 53:rt_kprintf("led red            get the resource.\r\n");break;
				case 54:rt_kprintf("led     green      get the resource.\r\n");break;
				case 55:rt_kprintf("led           blue get the resource.\r\n");break;
			}
//			rt_kprintf("no.%d get the source.\r\n",led);
			rt_pin_write(led,0);
			rt_thread_delay(50);
			rt_pin_write(led,1);
			
			rt_sem_release(sem_led);
		}
	}
}
