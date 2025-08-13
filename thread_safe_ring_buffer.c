
#include <stdio.h>
#include <stdint.h>
#include <stdatomic.h>
#include <pthread.h>

#define BUFFER_SIZE 100 //Define the maximum number of sensor points
typedef struct{
    int32_t sensor_value;
    float imu_sensor_value;
} SensorData;

static SensorData sensor_buffer[BUFFER_SIZE];

// Buffer management variables
// Volatile ensures that the compiler does not optimize these variables
static volatile unsigned int head = 0;//consumer
static volatile unsigned int tail = 0;//producer
static volatile unsigned int count = 0;//

static pthread_cond_t buffer_not_empty;
static pthread_cond_t buffer_not_full;
static pthread_mutex_t buffer_mutex;

//Buffer Initialization
void init_circular_buffer(){
    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_cond_init(&buffer_not_empty, NULL);
    pthread_cond_init(&buffer_not_full, NULL);
}
//Producer

void produce_sensor_data(SensorData data){
    pthread_mutex_lock(&buffer_mutex);
    while(count == BUFFER_SIZE){
        pthread_cond_wait(&buffer_not_full, &buffer_mutex);
    }
    sensor_buffer[tail] = data; // Add data to the buffer
    tail = (tail + 1) % BUFFER_SIZE; // Update tail index
    count++;
    pthread_cond_signal(&buffer_not_empty); //signal consumer
    pthread_mutex_unlock(&buffer_mutex);
}

//Consumer
SensorData consume_sensor_data(){
    SensorData data;
    pthread_mutex_lock(&buffer_mutex);
    while(count == 0){ 
        pthread_cond_wait(&buffer_not_empty, &buffer_mutex);
    }
    data = sensor_buffer[head];
    head = (head + 1) % BUFFER_SIZE; //update head size
    count --;
    pthread_cond_signal(&buffer_not_full);
    pthread_mutex_unlock(&buffer_mutex);
    return data;
}