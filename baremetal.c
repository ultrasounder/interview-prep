# include "stm32f4xx.h"

void delay(volatile uint32_t d){
    while (d--);
}

int main(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //enable clock for GPIOA

    //set PA5 as output(MODER5 = 01)
    GPIOA->MODER &= ~(0x3 << (2 * 5)); //clear bits
    GPIOA->MODER |= (0x01 << (2 * 5)); //set as output

    while (1){
        GPIOA->ODR ^= (1 << 5); //toggle PA5
        delay(100000);
    }
}