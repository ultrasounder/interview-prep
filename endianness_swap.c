#include <stdio.h>
#include <stdint.h> // For fixed-width integer types

/**
 * @brief Swaps the endianness of a 16-bit unsigned integer.
 * @param value The 16-bit integer to swap.
 * @return The byte-swapped 16-bit integer.
 */
uint16_t swapEndianness16(uint16_t value){
    return (value <<8) | (value >> 8);
}

/**
 * @brief Swap the endianness of a 32-bit unsigned integer.
 * @param value The 32-bit integer to swap.
 * @return The byte-swapped 32-bit integer.
 */
uint32_t swapEndianness32(uint32_t value){
    return ((value << 24) & (0xFF000000)) |
    ((value << 8) & 0x00FF0000) |
    ((value >> 8) & 0x0000FF00) |
    ((value >> 24) & 0x000000FF);
}
int main() {
    uint16_t value16 = 0x1234;
    uint32_t value32 = 0x12345678;

    printf("Original 16-bit value: 0x%04X\n", value16);
    printf("Swapped 16-bit value: 0x%04X\n", swapEndianness16(value16));

    printf("Original 32-bit value: 0x%08X\n", value32);
    printf("Swapped 32-bit value: 0x%08X\n", swapEndianness32(value32));

    return 0;
}
 