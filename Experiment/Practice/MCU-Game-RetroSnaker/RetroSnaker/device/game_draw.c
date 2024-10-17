#include "game_draw.h"

void snake_init(Snake *snake)
{
    snake->dir = UP;
    snake->speed = 1;
    snake->length = 2;
    snake->snake_pos[0][0] = 7;
    snake->snake_pos[0][1] = 7;
    snake->snake_pos[1][0] = 0;
    snake->snake_pos[1][1] = 0;
}

uchar8_t *getUcharFromSnake(Snake snake)
{
    char8_t i;
    static uchar8_t dat[2];
    dat[0] = 0x00;
    dat[1] = 0x00;
    for (i = 0; i < snake.length; i++)
    {
        dat[0] |= (1 << snake.snake_pos[i][0]);
        dat[1] &= (1 << snake.snake_pos[i][1]);
    }
    dat[1] = !dat[1];
    return dat;
}

void snake_pos_change(Snake *snake, uint16_t r, uint16_t c)
{
    uint16_t i;
    for (i = 0; i < snake->length; i++)
    {
        if (r < 0)
        {
            snake->snake_pos[i][0] = snake->snake_pos[i][0] == 0 ? 7 : snake->snake_pos[i][0] - 1;
        }
        else
        {
            snake->snake_pos[i][0] = (snake->snake_pos[i][0] + r) % 8;
        }
        if (c < 0)
        {
            snake->snake_pos[i][1] = snake->snake_pos[i][1] == 0 ? 7 : snake->snake_pos[i][1] - 1;
        }
        else
        {
            snake->snake_pos[i][1] = (snake->snake_pos[i][1] + c) % 8;
        }
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