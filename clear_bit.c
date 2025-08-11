#include <stdio.h>

int main(){
    unsigned char myByte = 0b10101010;//decimal 170
    unsigned char mask = 0b00000011;// Mask to clear bits 0 and 1

    // clear bits 0 and 1 using bitwise AND with the inverter mask
    myByte &= ~mask; // myByte = myByte & (~mask)
    printf("myByte after clearning bits 0 and 1: %u\n", myByte); // Should print 168

    return 0;
}