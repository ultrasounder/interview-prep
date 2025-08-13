#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define POOL_SIZE 1024 // Total memory pool size

// Define a block structure with a pointer to the next free block
typedef struct Block {
    struct Block *next;

}Block;

// Define the memory pool structure
typedef struct {
    Block *freeList; // Pointer to the free list
    unsigned char pool[POOL_SIZE];
}MemoryPool;

void initMemoryPool(MemoryPool *pool){
    pool->freeList = (Block *)pool->pool; // Initialize free list to the start of the pool
    Block *current = pool->freeList;

    //create a free list of blocks
    for (int i = 0; i < (POOL_SIZE) / sizeof(Block) - 1; ++i){
        current->next = (Block *)((unsigned char *)current + sizeof(Block));
        current = current->next;

    }
    current->next = NULL;
}
void *allocateMemory(MemoryPool *pool){
    if(pool->freeList == NULL){
        return NULL; // No free blocks available

    }
    // Get the first free block
    Block *block = pool->freeList;
    pool->freeList = block->next; // Remove the block from the free list
    return (void *)(block + 1); // Return a pointer to the memory after the block header
}

void freeMemory(MemoryPool *pool, void *ptr){
    Block *block = (Block *)ptr - 1; // Get the block header
    block->next = pool->freeList;
    pool->freeList = block; // 
}