#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Checks if a number is a power of two.
 * @param n The number to check.
 * @return True if n is a power of two, falase otherwise.
 */
bool isPowerOfTwo(int n){
    return (n > 0 && (n&(n-1)) == 0);
}
int main() {
    int num1 = 16; //2^4
    int num2 = 15;
    int num3 = 1; // 2^0

    printf("Is %d a power of two? %s\n", num1, isPowerOfTwo(num1) ? "Yes" : "No");
    printf("Is %d a power of two? %s\n", num2, isPowerOfTwo(num2) ? "Yes" : "No");
    printf("Is %d a power of two? %s\n", num3, isPowerOfTwo(num3) ? "Yes" : "No");

    return 0;   
}