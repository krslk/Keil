#ifndef _DEVICE_H_
#define _DEVICE_H_

#define Status uint16_t;
#define SUCCESSED 1
#define FAILED 0

#include "stm32f10x.h"

// void Delay_Ms_Init(void);
void delay(uint16_t ms);

#endif
