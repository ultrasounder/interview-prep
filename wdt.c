#include <stdint.h>
#include <stdio.h>

//initialization
void watchdog_init(uint32_t timeout_ms) {
    // Set the watchdog timeout register
    WATCHDOG_TIMEOUT_REG = timeout_ms;
    // Enable the watchdog
    WATCHDOG_CONTROL_REG |= WATCHDOG_ENABLE_BIT;
    // Configure reset mode if applicable
    WATCHDOG_MODE_REG |= WATCHDOG_RESET_MODE;


}
//servicing
void watchdog_feed(){
    // write a specific value to the watchdog 
}