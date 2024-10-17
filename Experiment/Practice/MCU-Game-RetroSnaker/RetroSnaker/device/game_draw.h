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
} Snake;

/**
 * @brief 蛇信息初识化
 * @param Snake *,蛇信息结构体指针
 * @return null
 */
void snake_init(Snake *snake);
/**
 * @brief 将蛇身坐标转换为点亮LED阵所需的数据类型
 * @param snake 蛇信息结构体变量
 * @return 返回一维数组，分别为输入给LED阵列行端口和列端口的值
 */
uchar8_t *getUcharFromSnake(Snake snake);
/**
 * @brief 蛇移动控制
 * @param Snake *,蛇信息结构体指针
 * @return null
 */
void snake_move(Snake *snake);