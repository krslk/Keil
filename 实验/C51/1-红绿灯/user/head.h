
#ifndef __REG52_H__
#include <reg52.h>
#endif

#ifndef HEAD_H

typedef unsigned char uchar_8;
typedef unsigned int uint_16;

#endif
/**
 *
 */
void delay_ms(uint_16 ms);
/**
 *
 */
void delay_10us(uint_16 us);
/**
 *
 */
void exti0_init();
/**
 *
 */
void exti1_init();