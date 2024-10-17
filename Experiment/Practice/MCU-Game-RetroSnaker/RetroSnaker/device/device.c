#include "device.h"

void hc595_write_data(uchar8_t dat)
{
    uchar8_t i = 0;
    for (i = 0; i < 8; i++)
    {
        SER = dat >> 7;
        dat <<= 1;
        SRCLK = 0;
        delay_10us(1);
        SRCLK = 1;
        delay_10us(1);
    }
    RCLK = 1;
    delay_10us(1);
    RCLK = 0;
}

void led_maxtir_dispaly(char8_t dat[])
{
    hc595_write_data(dat[0]);
    LED_MAXTIR_CONTROL_PORT = dat[1];
}

void delay_10us(uint16_t s) //@11.0592MHz
{
    uint16_t i = 2 * s;
    while (--i)
        ;
}

uchar8_t maxtir_flip_scan(void)
{
    static uchar8_t key_value = 0;
    KEY_MATRIX_PORT = 0x0f;
    if (KEY_MATRIX_PORT != 0x0f)
    {
        delay_10us(1000);
        if (KEY_MATRIX_PORT != 0x0f)
        {
            KEY_MATRIX_PORT = 0x0f;
            switch (KEY_MATRIX_PORT)
            {
            case 0x07:
                key_value = 1;
                break;
            case 0x0b:
                key_value = 2;
                break;
            case 0x0d:
                key_value = 3;
                break;
            case 0x0e:
                key_value = 4;
                break;
            }
        }
        KEY_MATRIX_PORT = 0xf0;
        switch (KEY_MATRIX_PORT)
        {
        case 0x70:
            key_value = key_value;
            break;
        case 0xb0:
            key_value += 4;
            break;
        case 0xd0:
            key_value += 8;
            break;
        case 0xe0:
            key_value += 12;
            break;
        }
        while (KEY_MATRIX_PORT != 0xf0)
            ;
    }
    else
    {
        key_value = 0;
    }
    return key_value;
}

void time0_init(void)
{
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x18;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}