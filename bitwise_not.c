#include <stdio.h>

int main(){
    unsigned char value = 0b00001111; // Example (15 in value)
    unsigned char inverted_value = ~value; // Bitwise NOT operation
    printf("Original value: %u\n", value);
    printf("Inverted value: %u\n", inverted_value);
    return 0;
}