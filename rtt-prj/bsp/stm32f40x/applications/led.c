#include "led.h"

void LED_Demo(void* param)
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
