#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"

#define PORT 5678

int server_fd, new_socket, valread;

void closeConnection() {
    close(server_fd);
    close(new_socket);
}

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    initSems();

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified IP address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding failed");
        closeConnection();
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listening failed");
        closeConnection();
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Acceptance failed");
            closeConnection();
            exit(EXIT_FAILURE);
        }

        // Check if the maximum number of visitors has been reached
        int number_of_visitors;
        sem_getvalue(gallery_sem_pointer, &number_of_visitors);
        if (number_of_visitors < 0) {
            strcpy(buffer, "Gallery is full. Please try again later.");
        } else {
            strcpy(buffer, "Welcome to the gallery.");
            // Increase the visitor count in the gallery
            sem_post(gallery_sem_pointer);
        }

        // Send response to the client
        send(new_socket, buffer, strlen(buffer), 0);

        // Close the connection
        close(new_socket);

        // Close the semaphores
        sem_close(gallery_sem_pointer);
        for (int i = 0; i < NUMBER_OF_PICTURES; i++) {
            sem_close(picture_sems_pointers[i]);
        }
    }

    close(server_fd);

    return 0;
}
