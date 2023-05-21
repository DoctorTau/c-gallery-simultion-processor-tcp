#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"

#define PORT 5678
#define MAX_RESPONSE_SIZE 1024

char buffer[MAX_RESPONSE_SIZE] = {0};

void SendMessage(int sock, const char *message) {
    if (send(sock, message, strlen(message), 0) < 0) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }
}

void ReceiveMessage(int sock, char *buffer) {
    if (read(sock, buffer, MAX_RESPONSE_SIZE) < 0) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }
}

int getRandomNumber(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

int main(int argc, char const *argv[]) {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
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

    for (;;) {
        int picture_number = getRandomNumber(0, NUMBER_OF_PICTURES - 1);
        // Wait for the picture to be free

        // Look at the picture
        sleep(time_to_stay);
        // printGalleryInfo();

        // Leave the picture

        // Mark the picture as visiteD
        visited_pictures[picture_number] = true;

        // If all pictures have been visited, leave the gallery
        if (isAllTrue(visited_pictures)) {
            break;
        }
    }
    printGalleryInfo();
    // Leave the gallery
    sem_post(gallery_sem_pointer);

    // Receive response from the server
    valread = read(sock, buffer, MAX_RESPONSE_SIZE);
    printf("%s\n", buffer);

    return 0;
}
