#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

#define BUFFER_SIZE 8 // Choose a power of 2 for potential optimization

typedef struct {
    int data[BUFFER_SIZE];
    // declare head and tail as atomic to ensure correct behavior across threads
    atomic_uint head;
    atomic_uint tail;
} RingBuffer;

//Intialize the ring buffer
void ringbuffer_init(RingBuffer *rb){
    rb->head = 0; // Start at zero
    rb->tail = 0; //Start at zero

}
//check if the buffer is empty
int ringbuffer_is_empty(RingBuffer *rb){
    return rb->head == rb->tail;
}
//Check if the buffer is full
int ringbuffer_is_full(RingBuffer *rb){
    return ((rb->head + 1) % BUFFER_SIZE) == rb->tail;
}
//Enqueue an element
int ringbuffer_enqueue(RingBuffer *rb, int value){
    if (ringbuffer_is_full(rb)){
        return 0; // Buffer is full, cannot enqueue
    }
    rb->data[rb->head] = value; // Add item to buffer
    rb->head = (rb-> head + 1) % BUFFER_SIZE; // Update head index
    return 1; // Successfully enqueued
}

// Dequeue an element
int ringbuffer_dequeue(RingBuffer *rb, int *value){
    if (ringbuffer_is_empty(rb)){
        return 0; // BUffer is empty, cannot dequeue
    }
    *value = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % BUFFER_SIZE; // Update tail index
    return 1; 
}


int main(){
    RingBuffer myBuffer;
    ringbuffer_init(&myBuffer);

    //Enqueue some values
    for (int i = 0; i < BUFFER_SIZE - 1; ++i){
        if (ringbuffer_enqueue(&myBuffer, i * 10)){
            printf("Enqueued: %d\n", i * 10);

        }

    }
    // Dequeue some values
    int dequeued_value;
    while (ringbuffer_dequeue(&myBuffer, &dequeued_value)){
        printf("Dequeued: %d\n", dequeued_value);
    }
    return 0;

}