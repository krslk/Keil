#ifndef _BUZZER_H_
#define _BUZZER_H_
#include "stm32f10x.h"

#define BuzzerOn GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define BuzzerOFF GPIO_ResetBits(GPIOB, GPIO_Pin_8)

void Buzzer_Init(void);

#endif
