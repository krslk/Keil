#include "device.h"

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} snake_dir;

/**
 * 蛇信息结构体
 */
typedef struct
{
    snake_dir dir;            // 蛇当前移动的方向
    uint16_t speed;           // 蛇的速度
    char8_t snake_pos[15][2]; // 蛇身的坐标
    uint16_t length;          // 蛇当前的长度
    uint16_t max_len;
} Snake;

typedef struct
{
    uchar8_t r;
    uchar8_t c;
    uchar8_t tag; // 食物刷新的标志
} Food;

/**
 * @brief 蛇信息初识化
 * @param Snake *,蛇信息结构体指针
 * @return null
 */
void snake_init(Snake *snake);

/**
 * @brief 蛇移动控制
 * @param Snake *,蛇信息结构体指针
 * @return null
 */
void snake_move(Snake *snake, Food *food);

/**
 * @brief 显示蛇的位置
 * @param Snake,蛇信息结构体
 * @return 无
 */
void show_snake(Snake Snake);

/**
 * @brief 改变蛇的移动方向,根据矩阵按键号k使蛇向指定方向移动
 * @param Snake *,蛇信息结构体指针
 * @param uchar8_t k,表示按键号
 * @return 无
 */
void snake_change_dir(Snake *snake, uchar8_t k);

/**
 *
 */
void show_food(uint16_t x, uint16_t y);

/**
 *
 */
void eat_food(Snake *snake);

/**
 *
 */
void refresh_food_pos(Food *food, uint16_t seed);