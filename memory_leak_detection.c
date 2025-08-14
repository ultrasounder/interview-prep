#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// Define a structure to hold information about each allocated block
typedef struct MemBlock{
    void* address;
    size_t size;
    const char* file;
    int line;
    struct MemBlock* next;

}MemBlock;

//Global head of the linked list
MemBlock* allocated_blocks = NULL;

// Custom malloc function
void* my_malloc(size_t size, const char* file, int line){
    void* ptr = malloc(size);
    if (ptr) {
        /* If allocation is sucessful, store the metadata */
        MemBlock* new_block = (MemBlock*)malloc(sizeof(MemBlock));
        if (new_block){
            new_block->address = ptr;
            new_block->size = size;
            new_block->file = file;
            new_block->line = line;
            new_block->next = allocated_blocks;
            allocated_blocks = new_block;
        } else{
            fprintf(stderr, "Memory allocation failed for metadata at %s:%d\n", file, line);
        }
    }
    return ptr;


}

void my_free(void* ptr, const char* file, int line){
    if (!ptr) return;

    MemBlock* current = allocated_blocks;
    MemBlock* previous = NULL;

    
}