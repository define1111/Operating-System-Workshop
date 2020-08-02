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

void test();

int
main()
{
    test();

    return 0;
}

uint32_t
pack(signed short x, signed short y, signed short z)
{
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

void
test()
{
    uint32_t packed_val;
    signed short x, y, z;
    signed short unpacked_x, unpacked_y, unpacked_z;

    for (x = -512; x <= 511; ++x)
        for (y = -512; y <= 511; ++y)
            for (z = -512; z <= 511; ++z)
            {
               packed_val = pack(x, y, z);
               unpack(packed_val, &unpacked_x, &unpacked_y, &unpacked_z);
               if (x != unpacked_x || y != unpacked_y || z != unpacked_z)
                   printf("Test failed\n");
            }

}
