#include "reg52.h"

#define _WTIME_ 20

void delay(int ms)
{
	int i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 1000; j++)
			;
	}
}

void turnOffAll(int m)
{
	P2 = 0xff;
	delay(m);
}

void leftToRight(int m)
{
	int i;
	unsigned char buf = 0X01;
	for (i = 0; i < 8; i++)
	{
		P2 = ~buf;
		delay(m);
		buf <<= 1;
	}
}

void rightToLeft(int m)
{
	int i;
	unsigned char buf = 0x80;
	for (i = 0; i < 8; i++)
	{
		P2 = ~buf;
		delay(m);
		buf >>= 1;
	}
}

/**
 * 从中间到两边依次常量
 */
void ledStyle_1(int m)
{
	int i;
	unsigned char left = 0x10;
	unsigned char right = 0x08;
	for (i = 0; i < 4; i++)
	{
		P2 &= ~(left | right);
		delay(m);
		left <<= 1;
		right >>= 1;
	}
}

/**
 * 从中间到两边依次闪烁
 */
void ledStyle_2(int m)
{
	int i;
	unsigned char left = 0x10;
	unsigned char right = 0x08;
	for (i = 0; i < 4; i++)
	{
		P2 = ~(left | right);
		delay(m);
		left <<= 1;
		right >>= 1;
	}
}

/**
 * 从左到右依次常量
 */
void ledStyle_3(int m)
{
	int i;
	unsigned char left = 0x01;
	for (i = 0; i < 8; i++)
	{
		P2 &= ~left;
		delay(m);
		left <<= 1;
	}
}

/**
 * 从右到左依次常量
 */
void ledStyle_4(int m)
{
	int i;
	unsigned char right = 0x80;
	for (i = 0; i < 8; i++)
	{
		P2 &= ~right;
		delay(m);
		right >>= 1;
	}
}

void main()
{
	while (1)
	{
		leftToRight(_WTIME_);
		turnOffAll(_WTIME_);
		rightToLeft(_WTIME_);
		turnOffAll(_WTIME_);
		ledStyle_1(_WTIME_);
		turnOffAll(_WTIME_);
		ledStyle_2(_WTIME_);
		turnOffAll(_WTIME_);
		ledStyle_3(_WTIME_);
		turnOffAll(_WTIME_);
		ledStyle_4(_WTIME_);
	}
}