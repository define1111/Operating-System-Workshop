#include <stdio.h>

typedef __uint32_t uint32_t;

typedef union
{
    struct
    {
        unsigned sign_x : 1;
        unsigned sign_y : 1;
        unsigned sign_z : 1;
        unsigned short x : 9;
        unsigned short y : 9;
        unsigned short z : 9;
    }__attribute__((packed));
    uint32_t int_r;
} bit_ir_t;

uint32_t pack(signed short x, signed short y, signed short z);
void unpack(uint32_t packed_val, signed short *x, signed short *y, signed short *z);

int
main()
{
    uint32_t packed_val;
    signed short x, y, z;

    x = 234;
    y = -25; 
    z = -24;

    packed_val = pack(x, y, z);

    unpack(packed_val, &x, &y, &z); 

    printf("%hd %hd %hd\n", x, y, z);

    return 0;
}

uint32_t
pack(signed short x, signed short y, signed short z)
{
//  uint32_t packed_val = 0;
    bit_ir_t bit_ir;
    bit_ir.int_r = (uint32_t) 0;

    bit_ir.sign_x = x >> 16;
    bit_ir.sign_y = y >> 16;
    bit_ir.sign_z = z >> 16;

    bit_ir.x = x;
    bit_ir.y = y;
    bit_ir.z = z;

    return bit_ir.int_r;
}

void 
unpack(uint32_t packed_val, signed short *x, signed short *y, signed short *z)
{
    bit_ir_t bit_ir;
    bit_ir.int_r = packed_val;

    *x = bit_ir.x;
    if (bit_ir.sign_x) *x |= 0xFE00; 

    *y = bit_ir.y;
    if (bit_ir.sign_y) *y |= 0xFE00; 

    *z = bit_ir.z;
    if (bit_ir.sign_z) *z |= 0xFE00; 
}

