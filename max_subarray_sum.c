#include <stdio.h>
#include <stdlib.h>

int maxSumSubarray(int* arr, int n, int k){
    int window_sum = 0, max_sum = 0;

    //first window
    for (int i = 0; i < k; i++){
        window_sum += arr[i];
    
    }
    max_sum = window_sum;

    //slide the window
    for (int i = k; i < n; i++){
        wiindow_sum = window_sum - arr[i - k] + arr[i];
    }
}

int main() {

}