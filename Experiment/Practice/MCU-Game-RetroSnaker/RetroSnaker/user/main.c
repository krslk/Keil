#include "reg51.h"

typedef unsigned char uchar8_t;
typedef unsigned int uint16_t;

sbit SRCLK = P3 ^ 6; // 移位寄存器时钟输入
sbit RCLK = P3 ^ 5;  // 存储寄存器时钟输入
sbit SER = P3 ^ 4;   // 串行数据输入
uchar8_t ghc595_buf[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void delay_10us(uint16_t s);
void hc595_write_data(uchar8_t dat)
{
    uchar8_t i = 0;
    for (i = 0; i < 8; i++)
    {
        SER = dat >> 7;
        dat <<= 1;
        SRCLK = 0;
        delay_10us(1);
        SRCLK = 1;
        delay_10us(1);
    }
    RCLK = 1;
    delay_10us(1);
    RCLK = 0;
}

uint16_t i = 0;

void main()
{
    P0 = 0x80;
    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            hc595_write_data(0x00); // 消除前面寄存器缓存数据
            hc595_write_data(ghc595_buf[i]); // 写入新的数据
            delay_10us(50000); // 延时500ms
        }
    }
}

/**
 * **************************************************************************************************************
 */

void delay_10us(uint16_t s) //@11.0592MHz
{
    uint16_t i = 2 * s;
    while (--i)
        ;
}