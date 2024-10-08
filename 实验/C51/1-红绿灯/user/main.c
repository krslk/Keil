#include <reg52.h>

typedef unsigned char uchar_8;
typedef unsigned int uint_16;

#ifndef LED_CONTROLLER

sbit led_green_ns = P1 ^ 4;
sbit led_yellow_ns = P1 ^ 5;
sbit led_red_ns = P1 ^ 6;
sbit led_green_we = P2 ^ 6;
sbit led_yellow_we = P2 ^ 5;
sbit led_red_we = P2 ^ 4;
sbit led_test = P0 ^ 1;

#endif

#ifndef LED_SCREEN

#define LED_SCREEN P0
uint_16 num_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
sbit cn_we_dec = P2 ^ 0; // 东西方向数字十位
sbit cn_we_one = P2 ^ 1; // 东西方向数字个位
sbit cn_ns_dec = P2 ^ 2; // 南北方向数字十位
sbit cn_ns_one = P2 ^ 3; // 南北方向数字个位
#endif

uint_16 sec_ns = 25;
uint_16 sec_we = 20;

// 函数声明
void delay_us(uint_16 us);
void time0_init(void);
void display(void);

void main()
{
    time0_init();
    while (1)
    {
        display();
    }
}

void delay_us(uint_16 us)
{
    while (us--)
        ;
}

void time0_init(void)
{
    TMOD |= 0X01; // 选择为定时器 0 模式，工作方式 1
    TH0 = 0XFC;   // 给定时器赋初值，定时 1ms
    TL0 = 0X18;
    ET0 = 1; // 打开定时器 0 中断允许
    EA = 1;  // 打开总中断
    TR0 = 1; // 打开定时器
}

void time0() interrupt 1
{
    static uint_16 count_ms = 0;
    TH0 = 0XFC;
    TL0 = 0X18;
    count_ms++;
    if (count_ms == 1000)
    {
        count_ms = 0;
        sec_we--;
        sec_ns--;
    }
}

void display(void)
{
    cn_we_dec = 1;
    cn_we_one = 0;
    cn_ns_dec = 0;
    cn_ns_one = 0;
    LED_SCREEN = ~num_code[sec_we / 10];
    delay_us(50);
    LED_SCREEN = 0xff;
    cn_we_dec = 0;
    cn_we_one = 1;
    cn_ns_dec = 0;
    cn_ns_one = 0;
    LED_SCREEN = ~num_code[sec_we % 10];
    delay_us(50);
    LED_SCREEN = 0xff;
    cn_we_dec = 0;
    cn_we_one = 0;
    cn_ns_dec = 1;
    cn_ns_one = 0;
    LED_SCREEN = ~num_code[sec_ns / 10];
    delay_us(50);
    LED_SCREEN = 0xff;
    cn_we_dec = 0;
    cn_we_one = 0;
    cn_ns_dec = 0;
    cn_ns_one = 1;
    LED_SCREEN = ~num_code[sec_ns % 10];
    delay_us(50);
    LED_SCREEN = 0xff;
}