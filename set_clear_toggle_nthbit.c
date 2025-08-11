#include <stdio.h>
/**
 * @brief Sets the nth bit of a given number.
 * @param num the number whose bit is to be set.
 * @param n The bit position (0-indexed)
 * @return The number with the nth bit set.
 */
unsigned int setNthBit(unsigned int num, int n) {
    return num | (1U << n); 


}
/**
 * @brief clears the nth bit of a given number
 * @param num the number to modify
 * @param n The bit position (0-indexed)
 * @return The number with the nth bit cleared.
 * 
 */
unsigned int clearNthBit(unsigned int num, int n){
    return num & ~(1U << n); 
}

/**
 * @brief Toggles the nth bit of a given number
 * @param num the number to modify
 * @param n The bit position (0-indexed)
 * @return The number with the nth bit toggled.
 */

 unsigned int toggleNthBit(unsigned int num, int n) {

    return num ^ (1U << n);

 }

 int main() {
    unsigned int num = 0b1010; // Example number (10 in decimal)
    int n = 1; // Example bit position

    printf("Original number : %u(binary: %s)\n", num, "1010");
    unsigned int set_num = setNthBit(num, n);
    printf("After setting bit %d: %u(binary: %s)\n", n, set_num, "1011");

    unsigned int clear_num = clearNthBit(num, n);
    printf("After clearing bit %d: %u(binary: %s)\n", n, clear_num, "1000");

    unsigned int toggle_num = toggleNthBit(num, n);
    printf("After toggling bit %d: %u(binary: %s)\n", n, toggle_num, "1010");

    return 0;
 }
