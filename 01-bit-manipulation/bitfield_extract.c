#include <stdio.h>
#include <stdint.h>         // uint32_t, uint16_t...
#include <inttypes.h>       // PRIx32, PRIX32...

uint32_t extract_bits(uint32_t reg, int start, int length);                     // Extract bits from register
uint32_t insert_bits(uint32_t reg, uint32_t value, int start, int length);      // insert bit to a register

int main()
{
    uint32_t reg = 0x12345678, extract_result = 0x0, insert_result = 0x0;

    extract_result = extract_bits(reg, 0, 4);
    printf("0x%08" PRIX32 "\n", extract_result);

    insert_result = insert_bits(reg, 0xFF, 8, 8);
    printf("0x%08" PRIX32 "\n", insert_result);

    // Edge case : value has more bits than length
    insert_result = insert_bits(0x00000000, 0xFF, 8, 4);
    printf("0x%08" PRIX32 "\n", insert_result);     // Output : 0x00000F00

    return 0;
}

uint32_t extract_bits(uint32_t reg, int start, int length)
{
    return (reg >> start) & ((1u << length) - 1u);      // shift + mask
}

uint32_t insert_bits(uint32_t reg, uint32_t value, int start, int length)
{
    uint32_t mask = ((1u << length) - 1u) << start;
    return (reg & ~mask) | ((value << start) & mask);   // clear target bits with mask, then OR with masked shifted value
}