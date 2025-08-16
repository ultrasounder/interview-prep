#include <stdint.h> //For unint8_t, uint32_t

// Define priority levels

//Define priority levels
typedef enum{
    PRIORITY_HIGH = 0,
    PRIORITY_MEDIUM,
    PRIORITY_LOW,
    NUM_PRIORITIES // Keep track of the number of priority levels
} CANMessagePriority_t;

// Structure for a CAN message
typedef struct{
    uint32_t id; // CAN Message ID
    uint8_t data[8]; //CAN message data (up to 8 bytes)
    uint8_t dlc; // Data Length code
    CANMessagePriority_t priority; // Criticality level
} CanMessage_t;

/** Priority Queue implementation(using multiple queues)
 * This approach uses an array of standard queues, with each index 
 * representing a priority level.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>






