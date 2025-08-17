#include <stdio.h>
#include <stdbool.h>

// Structure to hold sensor readings
typedef struct {
    int value;
    bool is_valid; //Flad to indicate if reading is considered valid
}SensorReading_t;

// Function to simulate readin from a sensor (for demonstration purposes)

SensorReading_t readSensor(int sensor_id){
    SensorReading_t reading;
    if (rand() % 10 < 2) {// Simualte a sensor with 20% failure chance
        reading.value = 0; // invalid reading
        reading.is_valid = false;
        printf("Sensor %d failed.\n", sensor_id);

    }else{
        reading.value = rand() % 100; // Simulate a valida reading between 0 and 99
        reading.is_valid = true;
        printf("Sensor %d reading: %d\n", sensor_id, reading.value);

    }
    return reading;
}

// Function to implement majority voting logic
int majorityVote(SensorReading_t s1, SensorReading_t s2, SensorReading_t s3, bool* disagreementDetected){
    *disagreementDetected = false; // Initialize disagreement flag

    //Cases for majority agreement
    if (s1.is_valid && s2.is_valid && s1.value == s2.value){
        return s1.value; // s1 and s2 agree
    }
    if (s1.is_valid && s3.is_valid && s1.value == s3.value){
        return s1.value; // s1 and s3 agree
    }
    if (s2.is_valid && s3.is_valid && s2.value == s3.value){
        return s2.value; // s2 and s3 agree
    }
    
    // cases for disagreement or only one valid sensor
    *disagreementDetected = true; // Set disagreement flag
    printf("Disagreement or insufficient valid sensor readings detected.\n");

    // If no clear majority, return a default value or trigger error handling
    if(s1.is_valid) return s1.value; // Prefer the first valid sensor if no majority
    if(s2.is_valid) return s2.value; // Prefer the second valid sensor if no majority
    if(s3.is_valid) return s3.value; // Prefer the third valid sensor if no majority

    return -1;  // Indicate a complete failure to get a valid reading



}

int main(){
    srand(time(NULL)); // Seed for random number generation

    SensorReading_t sensor1, sensor2, sensor3;
    bool disagreement;
    int votedValue;

    // Simulate reading from sensors multiple times
    for(int i = 0; i < 5; ++i){
        sensor1 = readSensor(1);
        sensor2 = readSensor(2);
        sensor3 = readSensor(3);

        votedValue = majorityVote(sensor1, sensor2, sensor3, &disagreement);

        if(disagreement){
            printf("Voting result: Disagreement/Failure detected. Voted value: %d\n", votedValue);
        }else {
            printf("Voting result : %d\n", votedValue);
        }
    }
    return 0;
}