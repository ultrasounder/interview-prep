#include <stdint.h> //For unint8_t, uint32_t

// Define priority levels

//Define priority levels
typedef enum{
    CRITICAL = 0,
    HIGH,
    MEDIUM,
    LOW,
    
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
/**
 * A common approach for  priority queue datastructure is to use a min-heap or max-heap implemented 
 * using an array. For this , a simple array-based approach with insertion sorting or a linked list with ordered
 * insertion can also work for smaller queues.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>


#define MAX_CAN_QUEUE_SIZE 100 // Maximum number of messages in the queue

CanMessage_t can_message_queue[MAX_CAN_QUEUE_SIZE];//CAN message queue array based 
int queue_size = 0;

// Function to insert a message into priority queue
void enqueue_can_message(CanMessage_t message){
    if (queue_size >= MAX_CAN_QUEUE_SIZE){
        printf("Queue is full. Cannot enqueue message with ID: %u\n", message.id);
        return;
    }
    // Insert message into the queue based on its priority
    int i = queue_size - 1;
    while (i >= 0 && can_message_queue[i].priority > message.priority){
        can_message_queue[i + 1] = can_message_queue[i];
        i--;
    }
    can_message_queue[i + 1] = message;
    queue_size ++;
}

// Function to retrieve highest priority message
CanMessage_t dequeue_can_message(){
    if (queue_size == 0){// Queue is empty
        // Handle empty queue (e.g. return a special "empty" message)
        CanMessage_t empty_msg = {0}; // Inititalize zeros
        return empty_msg;
    }

    CanMessage_t highest_priority_msg = can_message_queue[0];
    // Shift remaining messages to fill the gap
    for(int i = 0; i < queue_size - 1; i++){
        can_message_queue[i] = can_message_queue[i + 1];

    }
    queue_size--;
    return highest_priority_msg;


}
// Synchronization mechanisms (e.g., mutexes) should be used in a real-time system to protect access to the queue
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void enqueue_message_safe(CanMessage_t message){
    pthread_mutex_lock(&queue_mutex);// Lock the mutex
    enqueue_can_message(message);// call the thread-safe enqueue function
    pthread_mutex_unlock(&queue_mutex);// release the mutex
}
CanMessage_t dequeue_message_safe(){
    pthread_mutex_lock(&queue_mutex);// Lock the mutex
    CanMessage_t message = dequeue_can_message();// Call the thread-safe dequeue function
    pthread_mutex_unlock(&queue_mutex);// release the mutex
    return message;
}
