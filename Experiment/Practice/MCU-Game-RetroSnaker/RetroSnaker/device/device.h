#ifndef DEVICE_H
#define DEVICE_H
#include "reg51.h"

typedef unsigned char uchar8_t;
typedef unsigned int uint16_t;
typedef int int16_t;
typedef char char8_t;

sbit SRCLK = P3 ^ 6; // 移位寄存器时钟输入
sbit RCLK = P3 ^ 5;  // 存储寄存器时钟输入
sbit SER = P3 ^ 4;   // 串行数据输入

#ifndef LED_MAXTIR_CONTROL_PORT
#define LED_MAXTIR_CONTROL_PORT P0
#endif

#ifndef KEY_MATRIX_PORT // 矩阵按键
#define KEY_MATRIX_PORT P1
#endif

void delay_10us(uint16_t s);

/**
 * @brief 向74HC595写入一个字节的数据
 * @param uchar_8
 * @return null
 */
void hc595_write_data(uchar8_t dat);

/**
 * @brief LED阵列显示
 * @param
 */
void led_maxtir_dispaly(char8_t dat[]);

/**
 * @brief 使用线翻转扫描方法，检测矩阵按键是否按下，按下则返回对应键值（可以重新宏定义SMG_A_DP_PORT来改变矩阵按键对应的引脚，默认为P1）
 * @param @null
 * @return 1-16,对应S1-S16键,0：按键未按下
 */
uchar8_t maxtir_flip_scan(void);

/**
 *
 */
void time1_init(void);

/**
 * @brief 线性同余生成随机数
 * @param seed,随机数种子
 * @return 无
 */
uint16_t rand(uint16_t seed);

#endif