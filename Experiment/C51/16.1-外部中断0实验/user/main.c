#include <reg52.h>

typedef unsigned char uchar_8;
typedef unsigned int uint_16;
sbit KEY3 = P3^2;
sbit LED1 = P2^0;

void delay_ms(uint_16 ms);
void delay_10us(uint_16 us);
void exti0_init();
void exti1_init();

void main()
{
    exti0_init();
    while (1)
    {
    }
}

void int0() interrupt 0
{
    delay_10us(1000);
    if (KEY3 == 0)
    {
        LED1 = !LED1;
    }
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