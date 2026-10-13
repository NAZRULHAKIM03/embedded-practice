#include <stdio.h>
#include <stdint.h>         // uint32_t

int trailing_zeros(uint32_t x);     // count zeros from the right until first 1
int leading_zeros(uint32_t x);      // count zeros from the left until first 1

int main()
{
    printf("Trailing Zeros (0x00000001) = %d\n", trailing_zeros(0x00000001));   // expect 0
    printf("Trailing Zeros (0x80000000) = %d\n", trailing_zeros(0x80000000));   // expect 31
    printf("Trailing Zeros (0)          = %d\n", trailing_zeros(0));            // expect 32

    printf("Leading Zeros (0x00000001) = %d\n", leading_zeros(0x00000001));     // expect 31
    printf("Leading Zeros (0x80000000) = %d\n", leading_zeros(0x80000000));     // expect 0
    printf("Leading Zeros (0)          = %d\n", leading_zeros(0));              // expect 32

    return 0;
}

int trailing_zeros(uint32_t x)
{
    if(x == 0) return 32;

    int count = 0;

    for(int i=0; i<32; i++)
    {
        if(!((x >> i) & 1u))    // if bit i == 0, count + 1
        {
            count++;
        }
        else                    // if bit i == 1, break loop
        {
            break;
        }
    }

    return count;
}

int leading_zeros(uint32_t x)
{
    if(x == 0) return 32;

    int count = 0;

    for(int i = 31; i >= 0; i--)
    {
        if(!((x >> i) & 1u))    // if bit i == 0, count + 1
        {
            count++;
        }
        else                    // if bit i == 1, break loop
        {
            break;
        }
    }

    return count;
}