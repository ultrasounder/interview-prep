#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Define memory pool Pre allocation 

#define POOL_SIZE 1024 // Total size of the memory pool in bytes
#define CHUNK_SIZE 32 // Size of each chunk in bytes
#define NUM_CHUNKS (POOL_SIZE / CHUNK_SIZE) // Number of chunks in the pool
static char memory_pool[POOL_SIZE]; // Actual memory pool

// Manage the memory pool
typedef struct FreeChunk {
    struct FreeChunk* next;

}FreeChunk;

/* FreeChunk struct will represent a chunk of free memory in the pool and contain a pointer FreeChunk* to the next free chunk */
/* The free_list_head will point to the first free chunk in the list */
static FreeChunk* free_list_head = NULL; /* Head of the free list */
/* The init_pool function initializes the memory pool by linking all chunks together into a free list, acting like a stack 
where newly freed blocks are placed to the top*/
void init_pool(){
    for (int i = 0; i < NUM_CHUNKS; ++i){
        FreeChunk* chunk = (FreeChunk*)&memory_pool[i * CHUNK_SIZE];
        chunk->next = free_list_head; //
        free_list_head = chunk;// Add chunk to the head of the free list
    }
}
/* The allocate_chunk() function returns the current free_list_head and updates the ehad to the next available chunk*/

void* allocate_chunk(){
    if(free_list_head == NULL){
        return NULL; // pool is exhausted
    }
    void* allocated_chunk = free_list_head; // Get the first free chunk
    free_list_head = free_list_head->next;
    return allocated_chunk; // Return the allocated chunk
}

void free_chunk(void* chunk){
    if (chunk == NULL){
        return;
    }
    FreeChunk* freed_chunk = (FreeChunk*)chunk; // Cast the chunk to FreeChunk type
    freed_chunk->next = free_list_head; // Link the freed chunk to the head of the free list
    free_list_head = freed_chunk; // Add the freed chunk back to the head of the free list
}
int main(){
    FreeChunk pool;
    init_pool(); // Initialize the memory pool

    //Allocate a few blokcs
    void *block1 = allocate_chunk(&pool);
    void *block2 = allocate_chunk(&pool);
    printf("Allocated blocks: %p, %p\n", block1, block2);
    free_chunk(block1);
    free_chunk(block2);
    printf("Freed blocks: %p, %p\n", block1, block2);
    return 0;
}