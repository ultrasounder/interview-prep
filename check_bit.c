#include <stdio.h>

int main() {
    unsigned char flags = 0b00101101; //Example byte with bits set (45 in decimal)
    unsigned char mask = 0b00000001; //Mask to check the least significant bit

    //check if lsb is set
    if ((flags & mask) != 0) {
        printf("LSB is set .\n");
        
    }else {
        printf("LSB is not set.\n");
    }
    mask = 0b00000100;//Mask to check bit 2
    if ((flags & mask) != 0) {

    }
}