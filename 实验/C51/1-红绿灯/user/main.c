#include <reg52.h>
#include "head.h"

#ifndef LED_CONTROLLER

sbit led_green_ns = P1 ^ 4;
sbit led_yellow_ns = P1 ^ 5;
sbit led_red_ns = P1 ^ 6;
sbit led_green_we = P2 ^ 6;
sbit led_yellow_we = P2 ^ 5;
sbit led_red_we = P2 ^ 4;
sbit led_test = P0 ^ 1;

#endif

void delay_ms(uint_16 ms)
{
    uint_16 i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++)
            ;
}

void main()
{
    while (1)
    {
        led_green_ns = 1;
        led_yellow_ns = 1;
        led_red_ns = 1;
        led_green_we = 1;
        led_yellow_we = 1;
        led_red_we = 1;
        led_test = 1;
        delay_ms(100);
        led_green_ns = 0;
        led_yellow_ns = 0;
        led_red_ns = 0;
        led_green_we = 0;
        led_yellow_we = 0;
        led_red_we = 0;
        led_test = 0;
        delay_ms(100);
    }
}