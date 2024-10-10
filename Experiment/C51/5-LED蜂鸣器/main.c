#include "reg52.h"

typedef unsigned int uint_16;
typedef unsigned char uint_8;

sbit BEEP = P2 ^ 5;

/**
 * 简易延时函数，10us的倍数
 */
void delay_10us(uint_16 ten_us)
{
	while (ten_us--)
		;
}
/**
 * 简易延时函数，1ms的倍数
 */
void delay_ms(uint_16 ms)
{
	int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 1000; j++)
			;
}

void fun(void)
{
	uint_16 i = 1000;
	while (i--)
	{
		BEEP = !BEEP;
		delay_10us(50);
	}
	i = 0;
	BEEP = 0;
}

void main()
{
	while (1)
	{
		fun();
		delay_ms(1000);
	}
}