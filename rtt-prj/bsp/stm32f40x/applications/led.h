#ifndef __LED_H_
#define __LED_H_
#include <rtthread.h>
#include <drivers/pin.h>

#define LEDR	53
#define LEDG	54
#define LEDB	55

#define LED_PRIORITY		20
#define LED_STACK_SIZE	1000
#define LED_TIME_SLICE	11

void LED_Demo(void* param);



#endif
