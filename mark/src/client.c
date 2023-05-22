#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"
#include "tcpIO.h"

#define PORT 5678

char buffer[MAX_RESPONSE_SIZE] = {0};

int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

bool isAllTrue(bool array[]) {
    for (int i = 0; i < NUMBER_OF_PICTURES; i++) {
        if (!array[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    int sock = 0, valread, port;
    struct sockaddr_in serv_addr;
    char *ip_address;

    // Get ip address and port from the command line arguments
    if (argc == 3) {
        ip_address = (char *)argv[1];
        port = atoi(argv[2]);
    } else {
        printf("Usage: ./client <ip_address> <port>\n");
        return -1;
    }

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    bool visited_pictures[NUMBER_OF_PICTURES];
    int time_to_stay = getRandomNumber(1, 5);

    // Read the message from the server to enter the gallery
    ReceiveMessage(sock, buffer);

    if(buffer == "Welcome, to the gallery!") {
        printf("Entering the gallery.\n");
    }

    for (;;) {
        int picture_number = getRandomNumber(0, NUMBER_OF_PICTURES - 1);
        // Request the picture
        // convert picture_number to string
        // Clear the buffer
        memset(buffer, 0, MAX_RESPONSE_SIZE);
        sprintf(buffer, "%d", picture_number);
        SendMessage(sock, buffer);

        // Wait for the picture
        ReceiveMessage(sock, buffer);

        printf("Looking at the picture: %s\n", buffer);

        // Look at the picture
        sleep(time_to_stay);

        // Mark the picture as visiteD
        visited_pictures[picture_number] = true;

        SendMessage(sock, "Leave");

        // If all pictures have been visited, leave the gallery
        if (isAllTrue(visited_pictures)) {
            break;
        }
    }

    // Send the message to leave the gallery
    SendMessage(sock, EXIT_MESSAGE);
    printf("Exiting gallery.\n");

    return 0;
}
