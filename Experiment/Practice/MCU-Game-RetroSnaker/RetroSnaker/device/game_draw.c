#include "game_draw.h"

void snake_init(Snake *snake)
{
    snake->dir = UP;
    snake->speed = 1;
    snake->length = 2;
    snake->snake_pos[0][0] = 2;
    snake->snake_pos[0][1] = 6;
    snake->snake_pos[1][0] = 1;
    snake->snake_pos[1][1] = 6;
}

void snake_pos_change(Snake *snake, uint16_t r, uint16_t c)
{
    uint16_t i;
    for (i = 0; i < snake->length - 1; i++)
    {
        snake->snake_pos[i + 1][0] = snake->snake_pos[i][0];
        snake->snake_pos[i + 1][1] = snake->snake_pos[i][1];
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

void snake_move(Snake *snake)
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
}

void show_snake(Snake snake)
{
    uchar8_t i = 0;
    char8_t dat[2] = {0x00, 0x00};
    for (i = 0; i < snake.length; i++)
    {
        dat[0] |= (1 << snake.snake_pos[i][0]);
        dat[1] |= (1 << snake.snake_pos[i][1]);
    }
    dat[1] = ~dat[1];
    led_maxtir_dispaly(dat);
}

// void show_food(uint16_t x, uint16_t y)
// {
//     uchar8_t buf = 0x00;
//     buf = (1 << y);
//     hc595_write_data(buf);
//     buf = 0x00;
//     buf = (1 << x);
//     LED_MAXTIR_CONTROL_PORT = ~buf;
// }

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