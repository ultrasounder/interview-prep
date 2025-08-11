#include <stdio.h>

int main(){
    int foo = 42;
    int bar = -1;
    int *foo_ptr;
    foo_ptr = &foo;
    printf("Get the existing valuies of foo, bar, foo_ptr, and *foo_ptr:\n");
    printf("foo = %d\n", foo);
    printf("bar = %d\n", bar);
    printf("foo_ptr = %p\n", (void *)foo_ptr);
    printf("*foo_ptr = %d\n", *foo_ptr);

    //change the value of *foo_ptr
    printf("\nChanging the value of *foo_ptr to 100:\n");
    *foo_ptr = 100;
    printf("foo = %d\n", foo);
    printf("bar = %d\n", bar);
    printf("foo_ptr = %p\n", (void *)foo_ptr);
    printf("*foo_ptr = %d\n", *foo_ptr);

    //change the value of foo_ptr to & bar 
    printf("\nChanging foo_ptr to point to bar:\n");
    foo_ptr = &bar;
    printf("foo = %d\n", foo);
    printf("bar = %d\n", bar);
    printf("foo_ptr = %p\n", (void *)foo_ptr);
    printf("*foo_ptr = %d\n", *foo_ptr);

    //change the value of bar using foo_ptr


    return 0;
}