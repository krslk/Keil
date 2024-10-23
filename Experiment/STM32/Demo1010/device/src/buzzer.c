#include "buzzer.h"

void Buzzer_Init(void)
{
    GPIO_InitTypeDef buzzer_config = {GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_Init(GPIOB, &buzzer_config);
}
