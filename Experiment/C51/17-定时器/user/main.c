#include <reg52.h>

typedef unsigned char uchar_8;
typedef unsigned int uint_16;

uchar_8 num_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

uint_16 sec = 0;
uint_16 min = 0;

sbit a = P2 ^ 2;
sbit b = P2 ^ 3;
sbit c = P2 ^ 4;
sbit BEEP = P2 ^ 5;

delay_10us(uint_16 us)
{
    while (us--)
        ;
}

void showInfo()
{
    c = 0;
    b = 0;
    a = 0;
    P0 = num_code[sec % 10];
    delay_10us(100);
    P0 = 0x00;
    c = 0;
    b = 0;
    a = 1;
    P0 = num_code[sec / 10];
    delay_10us(100);
    P0 = 0x00;
    c = 1;
    b = 0;
    a = 0;
    P0 = num_code[min % 10];
    delay_10us(100);
    P0 = 0x00;
    c = 1;
    b = 0;
    a = 1;
    P0 = num_code[min / 10];
    delay_10us(100);
    P0 = 0x00;
}

void time0_init(void)
{
    TMOD |= 0x01;
    TH0 = 0xFb;
    TL0 = 0xca;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void main()
{
    BEEP=0;
    time0_init();
    while (1)
    {
        showInfo();
    }
}

void time0() interrupt 1 // 定时器0中断函数
{
    static uint_16 i = 0; // 定义静态变量i
    TH0 = 0XFC;           // 给定时器赋初值，定时1ms
    TL0 = 0X18;
    i++;
    if (i == 1000)
    {
        i = 0;
        sec++;
        if (sec == 60)
        {
            sec = 0;
            min++;
        }
    }
}