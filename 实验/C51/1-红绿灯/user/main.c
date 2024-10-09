#include <reg52.h>

typedef unsigned char uchar_8;
typedef unsigned int uint_16;

// LED相关配置
#ifndef LED_CONTROLLER
#define LED_CONTROLLER
#define DELAY_TIME 50           // 默认延时时长
#define LED_YELLOW_TIME 3       // 黄灯持续时长
#define LED_RED_DEFAULT_TIME 25 // 红绿灯间隔时间
#define LED_GREEN_MIN_TIME 15   // 红绿灯最小间隔时间
#define LED_TIME_ADD_STEP 5     // 加时步长
#define LED_TIME_SUB_STEP 5     // 减时步长
// LED灯的控制引脚
sbit led_green_ns = P1 ^ 4;
sbit led_yellow_ns = P1 ^ 5;
sbit led_red_ns = P1 ^ 6;
sbit led_green_we = P2 ^ 6;
sbit led_yellow_we = P2 ^ 5;
sbit led_red_we = P2 ^ 4;
uint_16 sec_ns_step = LED_RED_DEFAULT_TIME;
uint_16 sec_we_step = LED_RED_DEFAULT_TIME - LED_YELLOW_TIME;
uint_16 sec_ns;
uint_16 sec_we;
#endif

// 数码管相关配置
#ifndef LED_SCREEN
#define LED_SCREEN P0
uint_16 num_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
sbit cn_we_dec = P2 ^ 0; // 东西方向数字十位
sbit cn_we_one = P2 ^ 1; // 东西方向数字个位
sbit cn_ns_dec = P2 ^ 2; // 南北方向数字十位
sbit cn_ns_one = P2 ^ 3; // 南北方向数字个位
#endif
// 按键相关配置
#ifndef KEY_CONTROLLER
#define KEY_CONTROLLER

#define KEY_START_PRESS 1
#define KEY_STOP_PRESS 2
#define KEY_ADD_TIME_PRESS 3
#define KEY_SUB_TIME_PRESS 4
#define NO_PRESS 0
// 按键监听引脚
sbit KEY_START = P1 ^ 0;
sbit KEY_STOP = P1 ^ 1;
sbit KEY_ADD_TIME = P1 ^ 2;
sbit KEY_SUB_TIME = P1 ^ 3;

#endif

// 函数声明
/**
 * 初始化函数，封装了程序运行前所需的各种初始化操作，包括计时器0初始化、数码管初始化、LED初始化等
 */
void init(void);
/**
 * 定时器0初始化（TR0=0）
 */
void time0_init(void);
/**
 * 数码管初始化
 */
void screen_init(void);
/**
 * 延时函数
 */
void delay_us(uint_16 us);
/**
 * 按键扫描函数
 * @return KEY_START_PRESS-启动按键按下
 *         KEY_STOP_PRESS-急停按键按下
 *         KEY_ADD_TIME_PRESS-加时按键按下
 *         KEY_SUB_TIME_PRESS-减时按键按下
 *         NO_PRESS-没有按键按下
 */
uchar_8 key_scan(void);
/**
 * LED控制函数，控制各个LED灯的亮灭
 */
void led_controller(void);
/**
 * 按键响应函数，处理各个按键按下后的事件
 */
void key_controller(void);
/**
 * 简单的值交换函数，用于交换两个变量的值
 * @param *a 指向uint_16类型变量的指针变量
 * @param *b 指向uint_16类型变量的指针变量
 */
void swap(uint_16 *a, uint_16 *b);
/**
 * 数码管显示函数
 */
void display(void);

// 主函数
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
            if ((sec_ns_step > sec_we_step ? sec_ns : sec_we) == LED_YELLOW_TIME)
            {
                if (sec_ns_step > sec_we_step)
                    sec_we = LED_YELLOW_TIME;
                else
                    sec_ns = LED_YELLOW_TIME;
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
        sec_ns_step += LED_TIME_ADD_STEP;
        sec_we_step += LED_TIME_ADD_STEP;
        sec_ns += LED_TIME_ADD_STEP;
        sec_we += LED_TIME_ADD_STEP;
        break;
    case KEY_SUB_TIME_PRESS:
        if (sec_ns_step > LED_GREEN_MIN_TIME && sec_we_step > LED_GREEN_MIN_TIME)
        {
            sec_ns_step -= LED_TIME_SUB_STEP;
            sec_we_step -= LED_TIME_SUB_STEP;
        }
        break;
    }
}

void led_controller(void)
{
    if ((sec_ns_step > sec_we_step ? sec_ns : sec_we) > LED_YELLOW_TIME)
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

void display(void)
{
    cn_we_dec = 1;
    cn_we_one = 0;
    cn_ns_dec = 0;
    cn_ns_one = 0;
    LED_SCREEN = ~num_code[sec_we / 10];
    delay_us(DELAY_TIME);
    LED_SCREEN = 0xff;
    cn_we_dec = 0;
    cn_we_one = 1;
    cn_ns_dec = 0;
    cn_ns_one = 0;
    LED_SCREEN = ~num_code[sec_we % 10];
    delay_us(DELAY_TIME);
    LED_SCREEN = 0xff;
    cn_we_dec = 0;
    cn_we_one = 0;
    cn_ns_dec = 1;
    cn_ns_one = 0;
    LED_SCREEN = ~num_code[sec_ns / 10];
    delay_us(DELAY_TIME);
    LED_SCREEN = 0xff;
    cn_we_dec = 0;
    cn_we_one = 0;
    cn_ns_dec = 0;
    cn_ns_one = 1;
    LED_SCREEN = ~num_code[sec_ns % 10];
    delay_us(DELAY_TIME);
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

void swap(uint_16 *a, uint_16 *b)
{
    uint_16 buf = *a;
    *a = *b;
    *b = buf;
}