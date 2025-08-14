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

    while(current){
        if(current->address == ptr){
            //Found the block, remove it from the list
            if(ptr){
                previous->next = current->next;
            }else {
                allocated_blocks = current->next;
            }
            free(current);
            free(ptr); // Free the actual memory
            return;
            }
            previous = current;
            current = current->next;
        }
        fprintf(stderr, "warning ; Attempted to free unallocated memory at %p (called from %s:%d)\n", ptr, file, line);
        free(ptr);// Free the actual memory 

    }
/* Macro for easier memory allocation */
#define MALLOC(size) my_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) my_free(ptr, __FILE__, __LINE__)

    //Leak detection report

void dump_memory_leaks(){
    MemBlock* current = allocated_blocks;
    if(!current){
        printf("No memory leaks detected.\n");
        return;
    }

    printf("Memory leaks detected:\n");
    while (current) {
        printf("Leak at %p (size: %zu, allocated from %s:%d)\n",
               current->address, current->size, current->file, current->line);
        current = current->next;
    }
    printf("End of memory leak report.\n");
}

int main(){
    char* data1 = (char*)MALLOC(100);
    if(data1){
        strcpy(data1, "Hello, World!");

    }
    int* data2 = (int*)MALLOC(sizeof(int) * 10);
    if(data2){
        for(int i = 0; i < 10; i++){
            data2[i] = i;
        }
        FREE(data2); // Freeing data2
        //Simulate a leak by not freeing data1
        //FREE(data1);

        dump_memory_leaks(); // Check for memory leaks
        return 0;
    }
}