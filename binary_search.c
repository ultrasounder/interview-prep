#include <stdio.h>
#include "binary_search.h" //Binary search function prorotype

int main(){
    // Declare the array and its size
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    // Declare the target and a variable to store the result
    int target = 3;
    int result;

    //Call the binary search function and store the return value
    result = binary_search(arr, size, target);

    // Print the result
    if (result != -1) {
        printf("Element found at index: %d\n", result);
    } else {
        printf("Element not found in the array.\n");
    }


}