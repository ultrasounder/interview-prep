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
static FreeChunk* free_list_head = NULL; /* Head of the free list */

