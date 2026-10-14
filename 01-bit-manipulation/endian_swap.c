#include <stdio.h>
#include <stdint.h>     // uint32_t, uint16_t
#include <inttypes.h>   // PRIX16

uint16_t swap_endian_16(uint16_t x);    // Swap Byte(8 bits) Order for 16 bits
uint32_t swap_endian_32(uint32_t x);    // Swap Byte(8 bits) Order for 32 bits

int main()
{
    printf("Swap 16 bits (0xABCD)     : 0x%04" PRIX16 "\n", swap_endian_16(0xABCD));        // Expect 0xCDAB
    printf("Swap 16 bits (0x0001)     : 0x%04" PRIX16 "\n", swap_endian_16(0x0001));        // Expect 0x0100
    printf("Swap 16 bits (0xFFFF)     : 0x%04" PRIX16 "\n", swap_endian_16(0xFFFF));        // Expect 0xFFFF
    printf("Swap 32 bits (0x12345678) : 0x%08" PRIX32 "\n", swap_endian_32(0x12345678));    // Expect 0x78563412
    printf("Swap 32 bits (0xDEADBEEF) : 0x%08" PRIX32 "\n", swap_endian_32(0xDEADBEEF));    // Expect 0xEFBEADDE

    return 0;
}

uint16_t swap_endian_16(uint16_t x)
{
    return (x >> 8) | (x << 8);     // swap high and low bytes
}

uint32_t swap_endian_32(uint32_t x)
{
    return ((uint32_t)swap_endian_16(x & 0xFFFF) << 16) | swap_endian_16(x >> 16);      // swap_endian_16 handles swapping first half(16 bits) and second half(16 bits)
}