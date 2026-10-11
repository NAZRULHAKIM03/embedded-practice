#include <stdio.h>
#include <stdint.h>     // for uint32_t, uint16_t...
#include <inttypes.h>   // for PRIx32, PRIX32...

void set_bit(uint32_t* reg, int pos);       // force bit pos to 1
void clear_bit(uint32_t* reg, int pos);     // force bit pos to 0
void toggle_bit(uint32_t* reg, int pos);    // flip bit pos
void check_bit(uint32_t* reg, int pos);     // check bit 0/1

int main()
{
    uint32_t reg = 0x00000000;  

    set_bit(&reg, 0);       // set bit 0
    set_bit(&reg, 3);       // set bit 3
    set_bit(&reg, 7);       // set bit 7
    toggle_bit(&reg, 3);    // toggle bit 3
    clear_bit(&reg, 7);     // clear bit 7
    check_bit(&reg, 0);     // check bit 0
    check_bit(&reg, 5);     // check bit 5

    printf("0x%08" PRIx32 "\n", reg);   // prints in HEX 0x00000000

    return 0;
}

void set_bit(uint32_t* reg, int pos)
{
    *reg |= (1u << pos);
}

void toggle_bit(uint32_t* reg, int pos)
{
    *reg ^= (1u << pos);
}

void clear_bit(uint32_t* reg, int pos)
{
    *reg &= ~(1u << pos);
}

void check_bit(uint32_t* reg, int pos)
{
    *reg & (1u << pos) ? printf("Value = 1\n") : printf("Value = 0\n");
}