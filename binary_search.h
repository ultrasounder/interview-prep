#include <stdio.h>

int main(int* arr, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right){
        int mid = left + (right - left) >> 1;
        if (arr[mid] == target){
            return mid;
        }
        else if (arr[mid] < target){
            left += 1;
        }
        else {
            right -= 1;

        }
    }
    return -1; // target not found

}
