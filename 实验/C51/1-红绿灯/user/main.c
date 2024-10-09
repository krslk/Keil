#include <reg52.h>

typedef unsigned char uchar_8;
typedef unsigned int uint_16;
typedef int int_16;

#ifndef LED_CONTROLLER
#define LED_CONTROLLER
int_16 sec_ns_step = 23;
int_16 sec_we_step = 20;
int_16 sec_ns = 0;
int_16 sec_we = 0;
sbit led_green_ns = P1 ^ 4;
sbit led_yellow_ns = P1 ^ 5;
sbit led_red_ns = P1 ^ 6;
sbit led_green_we = P2 ^ 6;
sbit led_yellow_we = P2 ^ 5;
sbit led_red_we = P2 ^ 4;

#endif

#ifndef LED_SCREEN
#define LED_SCREEN P0
uint_16 num_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
sbit cn_we_dec = P2 ^ 0; // 东西方向数字十位
sbit cn_we_one = P2 ^ 1; // 东西方向数字个位
sbit cn_ns_dec = P2 ^ 2; // 南北方向数字十位
sbit cn_ns_one = P2 ^ 3; // 南北方向数字个位
#endif

#ifndef KEY_CONTROLLER
#define KEY_CONTROLLER

#define KEY_START_PRESS 1
#define KEY_STOP_PRESS 2
#define KEY_ADD_TIME_PRESS 3
#define KEY_SUB_TIME_PRESS 4
#define NO_PRESS 0

sbit KEY_START = P1 ^ 0;
sbit KEY_STOP = P1 ^ 1;
sbit KEY_ADD_TIME = P1 ^ 2;
sbit KEY_SUB_TIME = P1 ^ 3;

#endif

// 函数声明
void delay_us(uint_16 us);
void time0_init(void);
void display(void);
void screen_init(void);
void init(void);
void led_controller(void);
void key_controller(void);
void swap(int_16 *a, int_16 *b);

uchar_8 key_scan(void);

void main()
{
    init();
    while (1)
    {
        key_controller();
        display();
    }
}

/**
 *
 * ********************************************************************************************************
 */

void init(void)
{
    screen_init();
    time0_init();
}

void screen_init(void)
{
    sec_ns = sec_ns_step;
    sec_we = sec_we_step;
}

void time0_init(void)
{
    TMOD |= 0X01; // 选择为定时器 0 模式，工作方式 1
    TH0 = 0XFC;   // 给定时器赋初值，定时 1ms
    TL0 = 0X18;
    ET0 = 1; // 打开定时器 0 中断允许
    EA = 1;  // 打开总中断
    TR0 = 0; // 关闭定时器
}

void key_controller(void)
{
    switch (key_scan())
    {
    case KEY_START_PRESS:
        TR0 = 1;
        break;
    case KEY_STOP_PRESS:
        TR0 = 0;
        break;
    case KEY_ADD_TIME_PRESS:
        sec_ns_step += 5;
        sec_we_step += 5;
        sec_ns += 5;
        sec_we += 5;
        break;
    case KEY_SUB_TIME_PRESS:
        if (sec_ns_step > 15 && sec_we_step > 15)
        {
            sec_ns_step -= 5;
            sec_we_step -= 5;
        }
        break;
    }
}

void led_controller(void)
{
    if ((sec_ns_step > sec_we_step ? sec_ns : sec_we) > 3)
    {
        if (sec_ns_step > sec_we_step)
        {
            led_red_ns = 1;
            led_green_ns = 0;
            led_yellow_ns = 0;
            led_red_we = 0;
            led_green_we = 1;
            led_yellow_we = 0;
        }
        else
        {
            led_red_ns = 0;
            led_green_ns = 1;
            led_yellow_ns = 0;
            led_red_we = 1;
            led_green_we = 0;
            led_yellow_we = 0;
        }
    }
    else
    {
        if (sec_ns_step > sec_we_step)
        {
            led_red_ns = 1;
            led_green_ns = 0;
            led_yellow_ns = 0;
            led_red_we = 0;
            led_green_we = 0;
            led_yellow_we = 1;
        }
        else
        {
            led_red_ns = 0;
            led_green_ns = 0;
            led_yellow_ns = 1;
            led_red_we = 1;
            led_green_we = 0;
            led_yellow_we = 0;
        }
    }
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
        if ((sec_ns_step > sec_we_step ? sec_we : sec_ns) == 0)
        {
            if ((sec_ns_step > sec_we_step ? sec_ns : sec_we) == 3)
            {
                if (sec_ns_step > sec_we_step)
                {
                    sec_we = 3;
                }
                else
                {
                    sec_ns = 3;
                }
            }
            else
            {
                swap(&sec_ns_step, &sec_we_step);
                screen_init();
            }
        }
        led_controller();
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

uchar_8 key_scan(void)
{
    static uchar_8 tag = 0;
    if (tag == 0 && (KEY_START == 0 || KEY_STOP == 0 || KEY_ADD_TIME == 0 || KEY_SUB_TIME == 0))
    {
        tag = 1;
        display();
        if (KEY_START == 0)
        {
            return KEY_START_PRESS;
        }
        else if (KEY_STOP == 0)
        {
            return KEY_STOP_PRESS;
        }
        else if (KEY_ADD_TIME == 0)
        {
            return KEY_ADD_TIME_PRESS;
        }
        else if (KEY_SUB_TIME == 0)
        {
            return KEY_SUB_TIME_PRESS;
        }
    }
    else if (KEY_START == 1 && KEY_STOP == 1 && KEY_ADD_TIME == 1 && KEY_SUB_TIME == 1)
    {
        tag = 0;
    }
    return NO_PRESS;
}

void delay_us(uint_16 us)
{
    while (us--)
        ;
}

void swap(int_16 *a, int_16 *b)
{
    int_16 buf = *a;
    *a = *b;
    *b = buf;
}