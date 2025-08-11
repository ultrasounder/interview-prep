#include <stdio.h>
/**
 * @brief adds two integers without using the '+' operator.
 * @param a First integer.
 * @param b Second integer.
 * @return The sum of a and b.  
 * 
 */
int addWithoutPlus(int a, int b){
    int sum, carry;
    while (b != 0){
        sum = a ^ b; //Sum without carry
        carry = (a & b) << 1; //carry bits
        a = sum;
        b = carry;
    }
    return a; // Final result
    
}

int main(){
    int a = 5, b = 7;
    printf("%d + %d = %d\n", a, b, addWithoutPlus(a, b));
    return 0;
}