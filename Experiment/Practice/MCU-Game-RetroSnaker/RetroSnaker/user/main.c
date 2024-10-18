#include "reg51.h"
#include "device.h"
#include "game_draw.h"

#ifndef SMG_A_DP_PORT
#define SMG_A_DP_PORT P0 // 使用宏定义数码管段码口
uchar8_t gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                          0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
#endif

uint16_t seed_a = 1;
uint16_t seed_b = 1;
sbit led = P2 ^ 7; // 程序运行测试
uchar8_t key_value = 0;
Snake snake;

void main()
{
    snake_init(&snake);
    time0_init();
    time1_init();
    while (1)
    {
        snake_move(&snake);
        delay_10us(5000000);
    }
}

void time0() interrupt 1
{
    static uint16_t time0_count = 0; // 定义静态变量i
    TH0 = 0XFC;                      // 给定时器赋初值，定时1ms
    TL0 = 0X18;
    time0_count++;
    seed_a = (seed_a + 3) % 65535;
    if (time0_count >= 3)
    {
        time0_count = 0;
        key_value = maxtir_flip_scan();
        if (key_value != 0)
        {
            snake_change_dir(&snake, key_value);
        }
    }
}

void time1() interrupt 3
{
    static uint16_t time1_count = 0; // 定义静态变量i
    TH0 = 0XFC;                      // 给定时器赋初值，定时1ms
    TL0 = 0X18;
    time1_count++;
    seed_b = (seed_b + 1) % 65535;
    if (time1_count >= 20)
    {
        time1_count = 0;
        show_snake(snake);
        // show_food(2, 2);
    }
}