#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

/**
 * @brief converts a strong to an integer with robust error checking
 * @param str the string to convert
 * @param result Pointer to store the converted integer
 * @return 0 on success, -1 on error invalid input , -2 on overflow/underflow
 */

 int safeAtoi(const char *str, int *result){
    char *endptr;
    long val;

    errno = 0; //reset errno before conversion
    val = strtol(str, &endptr, 10); //convert string to long

    //check for various error conditions
    if (endptr == str){
        fprintf(stderr, "Error: No digits were found in the input string.\n");
        return -1; // No digits found
    }
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)){
        return -2; // overflow or underflow
    }
    if (*endptr != '\0'){
        return -1; // contains non-numeric characters after digits
    }

    *result = (int)val;
    return 0; 
 }

 int main(){
    const char *str1 = "12345";
    const char *str2 = "abc";
    const char *str3 = "123test";
    const char *str4 = "2147483647"; //MAX_INT
    const char *str5 = "2147483648"; //mAX_INT + 1 (overflow)

    int num;
    int status;

    status = safeAtoi(str1, &num);
    if (status == 0){
        printf("Converted '%s' to %d\n", str1, num);
    } else {
        printf("Failed to convert '%s', error code: %d\n", str1, status);
            }
    status = safeAtoi(str2, &num);
    if (status == 0){
        printf("Converted '%s' to %d\n", str2, num);
    } else {
        printf("Failed to convert '%s', error code: %d\n", str2, status);
    }
    status = safeAtoi(str3, &num);
    if (status == 0){
        printf("Converted '%s' to %d\n", str3, num);
    } else {
        printf("Failed to convert '%s', error code: %d\n", str3, status);
    }
    status = safeAtoi(str4, &num);
    if (status == 0){
        printf("Converted '%s' to %d\n", str4, num);
    } else {
        printf("Failed to convert '%s', error code: %d\n", str4, status);
    }
    status = safeAtoi(str5, &num);
    if (status == 0){
        printf("Converted '%s' to %d\n", str5, num);
    } else {
        printf("Failed to convert '%s', error code: %d\n", str5, status);
    }

    return 0;
 }