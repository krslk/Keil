#include "reg51.h"
#include "device.h"
#include "game_draw.h"

uint16_t seed = 1;
Food food;

sbit led = P2 ^ 7; // 程序运行测试
uchar8_t key_value = 0;
Snake snake;

void main()
{
    food.tag = 0;
    food.r = rand(seed * 7) % 8;
    food.c = rand(seed) % 8;
    snake_init(&snake);
    // time0_init();
    time1_init();
    while (1)
    {
        show_snake(snake);
        show_food(food.r, food.c);
        if (food.tag == 1)
        {
            refresh_food_pos(&food, seed);
        }
    }
}

// void time0() interrupt 1
// {
//     static uint16_t time0_count = 0; // 定义静态变量i
//     TH0 = 0XFC;                      // 给定时器赋初值，定时1ms
//     TL0 = 0X18;
//     time0_count++;
//     seed_a = (seed_a + 3) % 65535;
//     if (time0_count >= 5)
//     {
//         led = !led;
//         time0_count = 0;
//         key_value = maxtir_flip_scan();
//         if (key_value != 0)
//         {
//             snake_change_dir(&snake, key_value);
//         }
//     }
// }

void time1() interrupt 3
{
    static uint16_t time1_count = 0; // 定义静态变量i
    TH1 = 0XD5;                      // 给定时器赋初值，定时1ms
    TL1 = 0X24;
    time1_count++;
    seed = (seed * 29 + 29) % 8;
    if (time1_count % 5 == 0)
    {
        key_value = maxtir_flip_scan();
        if (key_value != 0)
        {
            snake_change_dir(&snake, key_value);
        }
    }
    if (time1_count >= 500)
    {
        time1_count = 0;
        snake_move(&snake, &food);
    }
}
