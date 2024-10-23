#include "led.h"

void Led_Init(void)
{
    GPIO_InitTypeDef gpio_Config;
    gpio_Config.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_Config.GPIO_Pin = GPIO_Pin_5;
    gpio_Config.GPIO_Mode = GPIO_Mode_Out_PP;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_Init(GPIOB, &gpio_Config);
    GPIO_Init(GPIOE, &gpio_Config);
}
