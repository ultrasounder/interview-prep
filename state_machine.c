#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

// Define states for the state machine
typedef enum {
    STATE_INIT,
    STATE_OPERATIONAL,
    STATE_FAULT_SENSOR,
    STATE_RECOVER_SENSOR,
    STATE_SHUTDOWN
} State_t;

// Define events for the state machine
typedef enum {
    EVENT_NONE,
    EVENT_START,
    EVENT_SENSOR_FAULT,
    EVENT_SENSOR_RECOVER,
    EVENT_SHUTDOWN
} Event_t;

// Function prototypes for state handlers

State_t handle_init_state(Event_t* event);
State_t handle_operational_state(Event_t* event);
State_t handle_fault_sensor_state(Event_t* event);
State_t handle_recover_sensor_state(Event_t* event);
State_t handle_shutdown_state(Event_t* event);

// Global state variable
State_t current_state = STATE_INIT;

// Simualted sensor reading function 
int read_sensor_data(){
    //Simulate a sensor error
    static int read_count = 0;
    read_count++;
    if (read_count % 3 == 0){
        errno = EIO; // Example error code
        return -1;
    }
    return 100; // Simulated sensor value
}

// State handler for initialization
State_t handle_init_state(Event_t* event){
    printf("Entering INIT state\n");
    // Perform initialization tasks
    //...

    return STATE_OPERATIONAL;

}
//State handler for operational mode
State_t handle_operational_state(Event_t* event){
    printf("Entering OPERATIONAL state\n");
    int data = read_sensor_data();
    if (data == -1){
        perror("Sensor read failed");
        return STATE_FAULT_SENSOR;
    }
    printf("Sensor data: %d\n", data);
    return STATE_OPERATIONAL;
}
// State handler for sensor fault
State_t handle_fault_sensor_state(Event_t* event){
    printf("Entering FAULT_SENSOR state\n");

    return STATE_RECOVER_SENSOR;

}

// State handler for sensor recovery

State_t handle_recover_sensor_state(Event_t* event){
    printf("Entering RECOVER_SENSOR state\n");
    // Attempt sensor reinitialization(eg reset the peripheral)
    //...
    //Simulate a successful recovery after some time
    static int retry_count = 0;
    retry_count++;
    if (retry_count >= 2){ 
        printf("Sensor recovery successful\n");
        retry_count = 0; //reset retry count every time
        return STATE_OPERATIONAL;
    } else {
        printf("Sensor recovery failed\n");
        // enter a brief wait period(WDT expires)
        return STATE_RECOVER_SENSOR; // Retry recovery
    }
}

// System state handler for shutdown
State_t handle_shutdown_state(Event_t* event){
    printf("Entering SHUTDOWN state\n");
    // Perform cleanup and gracefully shut down
    return STATE_SHUTDOWN;// Exit the state machine

}

// Main state machine loop 
void run_state_machine(){
    Event_t current_event;// Example event
    while(current_state != STATE_SHUTDOWN){
        switch (current_state){
            case STATE_INIT:
            current_state = handle_init_state(&current_event);
            break;
            case STATE_OPERATIONAL:
            current_state = handle_operational_state(&current_event);
            break;
            case STATE_FAULT_SENSOR:
            current_state = handle_fault_sensor(&current_event);
            break;
            case STATE_RECOVER_SENSOR:
            current_state = handle_recover_sensor_state(&current_event);
            break;
            case STATE_SHUTDOWN:
            fprintf(stderr, "Fatal Error: Unknown state encountered");
            current_state = STATE_SHUTDOWN;
            break;

            
        }
        for (volatile int i = 0; i < 10000000; ++i){
            __asm__ volatile ("nop");
        }
    }

}

int main(void){
    run_state_machine();
    return 0;
}