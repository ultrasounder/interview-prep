#include <stdio.h>
/**
 * @brief Countes the number of set bits in an integer
 * @param n the integer to analuze
 * @return the number of set bits
 * */

 int countSetBits(unsigned int n){
    int count = 0;// Initialize count of set bits
    while (n > 0){
        n &= (n - 1); // clears the lsb
        count += 1;
    }
    return count;
 }
 

 // For GCC and clang, you can use the built-in popcount function for efficiency
 #ifdef __GNUC__
 #define countSetBits_builtin __builtin_popcount
 #else
 //Fallback for other compilers
 int countSetBits_builtin(int n){
    return countSetBits(n);
 }
 #endif

 int main() {
    int num = 29; 

    printf("Number: %d\n", num);
    printf("set bits (iterative): %d\n", countSetBits(num));
    printf("set bits (builtin): %d\n", countSetBits_builtin(num));

    return 0;
 }