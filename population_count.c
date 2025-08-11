int countSetBitsNaive(unsigned int n) {
    int count = 0;
    while (n > 0){
        count += (n & 1); //check the least significant bit
        n >>= 1; //right shigt to check the next bit
    }
}

int countSetBitsKernighan(unsigned int n){
    int count = 0;
    while (n>0){
        n &= (n - 1); // clears the rightmost set bit
        count++; //Increment count for each set bit cleared
    }
    return count;
}