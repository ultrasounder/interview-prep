#include <stdio.h>
#include <string.h>

// function to calculate a simple checksum
unsigned char calculate_checksum(const char *data){
    unsigned char checksum = 0;//
    for (int i = 0; i < strlen(data); ++i){
        checksum ^= data[i]; //
    }
    return checksum;

}

// Function to simulate sending a message
void send_message(const char *data){
    unsigned char checksum = calculate_checksum(data);
    printf("Sending: %s (Checksum: %02x)\n", data, checksum);
    // Simulate sending the message
    for (volatile int i = 0; i < 10000000; ++i){
        __asm__ volatile ("nop");
    }
    printf("Message sent successfully.\n");
}

void receive_and_parse(const char *received_data, unsigned char received_checksum){
    unsigned char calculated_checksum = calculate_checksum(received_data);

    if(received_checksum == calculated_checksum){
        printf("Message received successfully: %s\n", received_data);
    } else {
        printf("Error: Checksum mismatch (Received: %02x, Calculated: %02x)\n", received_checksum, calculated_checksum);
    }
}

int main(){
    const char *message = "Hello, World!";
    send_message(message);

    receive_and_parse("Hello, World!", calculate_checksum(message));

    receive_and_parse("Hlllllo, werld!", 0x1A);
}
