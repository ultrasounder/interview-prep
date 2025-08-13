#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10// 

typedef struct {
    int buffer[BUFFER_SIZE];
     int head; //index for consumer
     int tail; //index for producer
} RingBuffer;

//Inititalize the ring buffer
void init_ring_buffer(RingBuffer *rb){
    rb->head = 0; // start at zero
    rb->tail = 0; // start at zero
}

//Producer thread, Add an item to the buffer
int enqueue(RingBuffer *rb, int item){
    if((rb->tail + 1) % BUFFER_SIZE == rb->head) {
        //buffer is full
        return -1;
    }
    rb->buffer[rb->tail] = item; //add itme to buffer
    return 0;

}

int dequeue(RingBuffer *rb, int *item){
    if (rb->head == rb->tail){
        //Buffer is empty
        return -1;
    }
    *item = rb->buffer[rb->head]; 
    
}