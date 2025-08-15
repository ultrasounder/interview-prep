
// #include <stdio.h>
// #include <stdint.h>
// #include <stdatomic.h>
// #include <pthread.h>

// #define BUFFER_SIZE 100 //Define the maximum number of sensor points
// typedef struct{
//     int32_t sensor_value;
//     float imu_sensor_value;
// } SensorData;

// static SensorData sensor_buffer[BUFFER_SIZE];

// // Buffer management variables
// // Volatile ensures that the compiler does not optimize these variables
// static volatile unsigned int head = 0;//consumer
// static volatile unsigned int tail = 0;//producer
// static volatile unsigned int count = 0;//

// static pthread_cond_t buffer_not_empty;
// static pthread_cond_t buffer_not_full;
// static pthread_mutex_t buffer_mutex;

// //Buffer Initialization
// void init_circular_buffer(){
//     pthread_mutex_init(&buffer_mutex, NULL);
//     pthread_cond_init(&buffer_not_empty, NULL);
//     pthread_cond_init(&buffer_not_full, NULL);
// }
// //Producer

// void produce_sensor_data(SensorData data){
//     pthread_mutex_lock(&buffer_mutex);
//     while(count == BUFFER_SIZE){
//         pthread_cond_wait(&buffer_not_full, &buffer_mutex);
//     }
//     sensor_buffer[tail] = data; // Add data to the buffer
//     tail = (tail + 1) % BUFFER_SIZE; // Update tail index
//     count++;
//     pthread_cond_signal(&buffer_not_empty); //signal consumer
//     pthread_mutex_unlock(&buffer_mutex);
// }

// //Consumer
// SensorData consume_sensor_data(){
//     SensorData data;
//     pthread_mutex_lock(&buffer_mutex);
//     while(count == 0){ 
//         pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
//     }
//     data = sensor_buffer[head];
//     head = (head + 1) % BUFFER_SIZE; //update head size
//     count --;
//     pthread_cond_signal(&buffer_not_full);
//     pthread_mutex_unlock(&buffer_mutex);
//     return data;
// }



//** A thread-safe circular buffer for sensor data in C, without dynamic memory allocation, can be implemented using a static array and a mutex for synchronization. 
#include <pthread.h>
#include <stdbool.h>


/*
Explanation: 

• CircularBuffer Structure: 
	• data[BUFFER_SIZE]: A static array to store the sensor data. BUFFER_SIZE is a pre-defined constant, eliminating dynamic allocation. 
	• head: Points to the next available position for writing. 
	• tail: Points to the next element to be read. 
	• full: A boolean flag to differentiate between a completely full buffer and an empty one when head and tail are equal. 
	• mutex: A pthread_mutex_t to ensure thread safety by protecting critical sections (modifications to head, tail, full, and data). 

• cb_init: Initializes the head, tail, and full flag, and initializes the mutex. 
• cb_write: 
	• Acquires the mutex to prevent race conditions. 
	• Checks if the buffer is full; if so, it releases the mutex and returns false. 
	• Writes the value to data[head]. 
	• Increments head and wraps it around using the modulo operator (% BUFFER_SIZE). 
	• Sets full to true if head catches up to tail. 
	• Releases the mutex. 

• cb_read: 
	• Acquires the mutex. 
	• Checks if the buffer is empty; if so, it releases the mutex and returns false. 
	• Reads the value from data[tail]. 
	• Increments tail and wraps it around. 
	• Sets full to false because a read operation always makes the buffer not full. 
	• Releases the mutex. 

• cb_destroy: Destroys the mutex when the buffer is no longer needed. 

This implementation provides a basic thread-safe circular buffer without dynamic memory allocation, suitable for embedded systems or scenarios where memory allocation is restricted. 

AI responses may include mistakes.

 */


#include <pthread.h>
#include <stdbool.h>

#define BUFFER_SIZE 100

typedef struct{
    int data[BUFFER_SIZE];
    unsigned int head;// index for next write position
    unsigned int tail; //index for next read position
    bool is_full;// Flag to distinguish between empty and full buffer when head == tail
    pthread_mutex_t mutex;
}CircularBuffer;

// Initialize the circular buffer
void init_circular_buffer(CircularBuffer *cb){
    cb->head = 0;
    cb->tail = 0;
    cb->is_full = false;
    pthread_mutex_init(&cb->mutex, NULL);
}

//writes data to the buffer
bool write_to_buffer(CircularBuffer *cb, int value){
    //Check if buffer is full
    pthread_mutex_lock(&cb->mutex);
    if(cb->is_full) {
        pthread_mutex_unlock(&cb->mutex);
        return false; //buffer is full
    }
    cb->data[cb->head] = value;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->is_full = (cb->head == cb->tail);
    pthread_mutex_unlock(&cb->mutex);
    return true; // Write successful
}

// Reads data from buffer
bool read_from_buffer(CircularBuffer *cb, int *value){
    //check if buffer is empty
    if(cb->head == cb->tail && !cb->is_full){
        return false; // Buffer is empty

    }

    *value = cb->data[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->is_full = false;
    pthread_mutex_lock(&cb->mutex);
    return true; // Read successful

}

void cb_destroy(CircularBuffer *cb){
    pthread_mutex_destroy(&cb->mutex);// Destroy the mutex 
}