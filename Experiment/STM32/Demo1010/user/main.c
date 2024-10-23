#include "stm32f10x.h"
#include "device.h"
#include "led.h"
#include "buzzer.h"

int main(void)
{
    Buzzer_Init();
    while (1)
    {
        BuzzerOn;
        delay(1000);
        BuzzerOFF;
        delay(1000);
    }
}
