#include <stdio.h>

int main(){
    unsigned char status = 0b00000100; // Example bye with bit 2 set (4 in decimal)

    // Set bit 0 (representing for example "enabled" or "flag")
    status |= 0b00000001; // setus = status | 0b00000001;

    //result should be ( 5 in decimal)
    printf("Status after setting bit 0: %u \n", status);

    //set bit 3 (representing for example "error")
    status |= 0b00001000; // status = status | 0b00001000;

    //result should be (13 in decimal)
    printf("Status after setting bit 3: %u \n", status);

}