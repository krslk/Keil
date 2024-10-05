#include "reg52.h"

typedef unsigned int uint_16;
typedef unsigned char uint_8;

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

// 独立按键控制引脚
sbit KEY1 = P3 ^ 1;
sbit KEY2 = P3 ^ 0;
sbit KEY3 = P3 ^ 2;
sbit KEY4 = P3 ^ 3;
// LED灯控制引脚
sbit LED_2 = P2 ^ 2;
sbit LED_3 = P2 ^ 3;
sbit LED_4 = P2 ^ 4;
/**
 * 检测按键是否按下
 * @param singleScan 扫描模式：0，按键抬起扫描；1，按键按下扫描
 * @return 返回按键对应的值，如果没有按键按下则返回0
 */
uint_16 keyScan(uint_16 singleScan)
{
	static uint_16 status = 1;
	if (singleScan == 0)
		status = 1;
	if (status == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0))
	{
		status = 0;
		delay_10us(1000);
		if (KEY1 == 0)
		{
			return 1;
		}
		else if (KEY2 == 0)
		{
			return 2;
		}
		else if (KEY3 == 0)
		{
			return 3;
		}
		else if (KEY4 == 0)
		{
			return 4;
		}
	}
	else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1)
	{
		status = 1;
	}
	return 0;
}

void main()
{
	while (1)
	{
		uint_16 res = keyScan(1);
		switch (res)
		{
		case 1:
			LED_2 = !LED_2;
			break;
		case 2:
			LED_3 = !LED_3;
			break;
		case 3:
			LED_4 = ~LED_4;
			break;
		case 4:
			LED_2 = 1;
			LED_3 = 1;
			LED_4 = 1;
			break;
		}
	}
}