#ifndef _LED_H_
#define _LED_H_
#include "stm32f10x.h"

#define LED3_ON GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LED2_ON GPIO_ResetBits(GPIOE, GPIO_Pin_5)
#define LED3_OFF GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LED2_OFF GPIO_SetBits(GPIOE, GPIO_Pin_5)

void Led_Init(void);

#endif
