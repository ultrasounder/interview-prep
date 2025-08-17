#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#define MAX_SIZE 1000

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

void stack_init(Stack* s) {
    s->top = -1; // Initialize stack top
}

bool push(Stack* s, int data) {
    if (s->top >= MAX_SIZE - 1) // Check for stack overflow
        return false;
    s->arr[++s->top] = data; // Push data onto stack
    return true;
}

int pop(Stack* s) {
    if (s->top < 0) // Check for stack underflow
        return INT_MIN;
    return s->arr[s->top--]; // Pop data from stack
}