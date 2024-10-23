#include "device.h"

// Status Delay_Ms_Init(void)
// {
//     if (SysTick_Config())
//     {
//         return SUCCESSED;
//     }
//     return FAILED;
// }

void delay(uint16_t ms)
{
    uint16_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++)
            ;
}
