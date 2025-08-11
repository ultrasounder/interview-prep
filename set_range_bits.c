#include <stdio.h>

/**
 * @brief Sets a range of bits within a number.
 * @param num The number to modify.
 * @param start The starting bit position (0-indexed).
 * @param end The ending bit position (0-indexed).
 * @return The number with the specified range of bits set.
 */
unsigned int setBitRange(unsigned int num, int l, int r){
    unsigned int mask =  ((1U<<(r - l + 1)) - 1) << l;
    return num | mask;
}

int main() {
    unsigned int num = 0b10100000;
    int l = 2; 
    int r = 5; 
    printf("Original number: %u (binary: %s)\n", num, "10100000");
}