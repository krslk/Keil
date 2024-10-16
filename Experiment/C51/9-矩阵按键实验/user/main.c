#include <reg52.h>

typedef unsigned int uint16_t;
typedef unsigned char uchar8_t;

#define MATRIX_KEY_PORT P1

// 共阴极数码管显示0~F的段码数据
uchar8_t gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                          0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

void main()
{
  P2 = 0x00;
}

uint16_t key_matrix_scan()
{
  uchar8_t key_value = 0;
}