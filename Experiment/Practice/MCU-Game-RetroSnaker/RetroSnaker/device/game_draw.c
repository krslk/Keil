#include "game_draw.h"

void snake_init(Snake *snake)
{
    snake->dir = UP;
    snake->speed = 10;
    snake->length = 2;
    snake->max_len = 15;
    snake->snake_pos[0][0] = 2;
    snake->snake_pos[0][1] = 6;
    snake->snake_pos[1][0] = 1;
    snake->snake_pos[1][1] = 6;
    snake->snake_pos[2][0] = 0;
    snake->snake_pos[2][1] = 6;
}

void snake_pos_change(Snake *snake, uint16_t r, uint16_t c)
{
    uint16_t i;
    for (i = snake->length - 1; i > 0; i--)
    {
        snake->snake_pos[i][0] = snake->snake_pos[i - 1][0];
        snake->snake_pos[i][1] = snake->snake_pos[i - 1][1];
    }
    if (r < 0)
    {
        snake->snake_pos[0][0] = snake->snake_pos[0][0] == 0 ? 7 : snake->snake_pos[0][0] - 1;
    }
    else
    {
        snake->snake_pos[0][0] = (snake->snake_pos[0][0] + r) % 8;
    }
    if (c < 0)
    {
        snake->snake_pos[0][1] = snake->snake_pos[0][1] == 0 ? 7 : snake->snake_pos[0][1] - 1;
    }
    else
    {
        snake->snake_pos[0][1] = (snake->snake_pos[0][1] + c) % 8;
    }
}

void snake_move(Snake *snake, Food *food)
{
    switch (snake->dir)
    {
    case UP:
        snake_pos_change(snake, 1, 0);
        break;
    case DOWN:
        snake_pos_change(snake, -1, 0);
        break;
    case LEFT:
        snake_pos_change(snake, 0, 1);
        break;
    case RIGHT:
        snake_pos_change(snake, 0, -1);
        break;
    }
    if (snake->snake_pos[0][0] == food->r && snake->snake_pos[0][1] == food->c)
    {
        food->tag = 1;
        eat_food(snake);
    }
}

 void show_snake(Snake snake)
 {
     uchar8_t i = 0;
     char8_t dat[2] = {0x00, 0x00};
     for (i = 0; i < snake.length; i++)
     {
         LED_MAXTIR_CONTROL_PORT = 0XFF;
         dat[0] = (1 << snake.snake_pos[i][0]);
         dat[1] = (1 << snake.snake_pos[i][1]);
         dat[1] = ~dat[1];
         led_maxtir_dispaly(dat);
     }
 }

 void show_food(uint16_t r, uint16_t c)
 {
     LED_MAXTIR_CONTROL_PORT = 0XFF;
     hc595_write_data((1 << r));
     LED_MAXTIR_CONTROL_PORT = ~(1 << c);
 }

void snake_change_dir(Snake *snake, uchar8_t k)
{
    switch (k)
    {
    case 2:
        if (snake->dir != DOWN)
        {
            snake->dir = UP;
        }
        break;
    case 10:
        if (snake->dir != UP)
        {
            snake->dir = DOWN;
        }
        break;
    case 5:
        if (snake->dir != RIGHT)
        {
            snake->dir = LEFT;
        }
        break;
    case 7:
        if (snake->dir != LEFT)
        {
            snake->dir = RIGHT;
        }
        break;
    }
}

void eat_food(Snake *snake)
{
    if (snake->length + 1 <= snake->max_len)
    {
        snake->length++;
    }
    if (snake->speed <= 400)
        snake->speed += 50;
}

void refresh_food_pos(Food *food, uint16_t seed)
{
    food->c = rand(seed);
    food->r = rand(seed * 9 % 8);
    food->tag = 0;
}

void display(const Snake snake, const Food food)
{
    uchar8_t i = 0, j, buf[2];
    for (i = 0; i < 8; i++)
    {
        buf[0] = (1 << i);
        buf[1] = 0x00;
        for (j = 0; j < snake.length; j++)
        {
            if (snake.snake_pos[j][0] == i)
            {
                buf[1] |= (1 << snake.snake_pos[j][1]);
            }
        }
        if (food.r == i)
        {
            buf[1] |= (1 << food.c);
        }
        LED_MAXTIR_CONTROL_PORT = 0xFF;
        buf[1] = ~buf[1];
        led_maxtir_dispaly(buf);
    }
}