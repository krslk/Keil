#include "head.h"

void delay_ms(uint_16 ms)
{
    uint_16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++)
            ;
}

void delay_10us(uint_16 us)
{
    while (us--)
        ;
}

void exti0_init(void)
{
    IT0 = 1; // 下降沿触发,0低电平触发
    EX0 = 1;
    EA = 1;
}

void exti1_init(void)
{
    IT1 = 1; // 下降沿触发,0低电平触发
    EX1 = 1;
    EA = 1;
}