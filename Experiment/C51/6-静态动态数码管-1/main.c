#include "reg52.h"

typedef unsigned int uint_16;
typedef unsigned char uchar_8;

#define SMG_A_DP_PORT P0

uchar_8 led_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};

/**
 * 简易延时函数，10us的倍数
 */
void delay_10us(uint_16 us)
{
	while (us--)
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

// 数码管位选信号控制
sbit led_a = P2 ^ 2;
sbit led_b = P2 ^ 3;
sbit led_c = P2 ^ 4;

/**
 * 数码管位选函数
 * @param num 数码管位
 * 选择num对应的数码管输出
 */
void led_switch(uint_16 num)
{
	switch (num)
	{
	case 0:
		led_c = 0;
		led_b = 0;
		led_a = 0;
		break;
	case 1:
		led_c = 0;
		led_b = 0;
		led_a = 1;
		break;
	case 2:
		led_c = 0;
		led_b = 1;
		led_a = 0;
		break;
	case 3:
		led_c = 0;
		led_b = 1;
		led_a = 1;
		break;
	case 4:
		led_c = 1;
		led_b = 0;
		led_a = 0;
		break;
	case 5:
		led_c = 1;
		led_b = 0;
		led_a = 1;
		break;
	case 6:
		led_c = 1;
		led_b = 1;
		led_a = 0;
		break;
	case 7:
		led_c = 1;
		led_b = 1;
		led_a = 1;
	}
}

void ledShow(uchar_8 showInfo[])
{
	int i;
	for (i = 7; i >= 0; i--)
	{
		led_switch(i);
		SMG_A_DP_PORT = 0x00;
		SMG_A_DP_PORT = showInfo[i];
		delay_10us(100);
	}
}

void main()
{
	int s = 0, i, r;
	while (1)
	{
		for (r = 0; r < 80; r++)
		{
			for (i = 7; i >= 0; i--)
			{
				led_switch((i + s) % 8);
				SMG_A_DP_PORT = 0x00;
				SMG_A_DP_PORT = led_code[7 - i];
				delay_10us(100);
			}
		}
		s++;
	}
}