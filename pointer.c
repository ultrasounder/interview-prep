#include <stdio.h>
#include <stdlib.h>

// int main(){
//     /*X is an integer variable*/
//     int x = 42;
//     /* x_ptr is a pointer to an integer variable*/
//     int *x_ptr = &x;
//     printf("x = %d\n", x);
//     printf("x_ptr = %p\n", x_ptr);
// }

int main() {
    int* x; //allocate the pointers x and y
    int* y;

    x = malloc(sizeof(int)); //allocate memory for x

    *x = 42; //assign value to x
    *y = 13; //this should crash since y is not allocated memory

    y = x; //point y to the same memory as x
    *y = 13; // assign value to y, which is now the same memory as x

    printf("x = %d\n", *x);
    printf("y = %d\n", *y);

    free(x); //free the allocated memory for x
    return 0;
}
