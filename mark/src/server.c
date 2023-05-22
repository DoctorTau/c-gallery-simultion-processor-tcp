#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "common.h"
#include "queue.h"
#include "tcpIO.h"

#define PORT 5678

int server_fd;
queue clients_queue;
pthread_t warder_process;

void closeConnection() {
    close(server_fd);
    while (!isEmpty(&clients_queue)) {
        int client_socket = dequeue(&clients_queue);
        close(client_socket);
    }
}

void handleSigInt(int sig) {
    if (sig != SIGINT) {
        return;
    }
    closeConnection();
    // kill warder process
    pthread_kill(warder_process, SIGKILL);
    exit(EXIT_SUCCESS);
}

void *processClient(void *arg) {
    int *client_socket = (int *)arg;
    char buffer[1024] = {0};
    int valread;

    SendMessage(*client_socket, WELCOME_MESSAGE);

    for (;;) {
        // Receive the message number from the client
        ReceiveMessage(*client_socket, buffer);

        // Check if the client wants to exit
        if (strcmp(buffer, "exit") == 0) {
            printf("Client %d disconnected\n", *client_socket);
            close(*client_socket);
            return NULL;
        }

        int picture_number = atoi(buffer);

        // Check if the picture number is valid
        if (picture_number < 0 || picture_number >= NUMBER_OF_PICTURES) {
            strcpy(buffer, "Invalid picture number.");
            send(*client_socket, buffer, strlen(buffer), 0);
            close(*client_socket);
            free(client_socket);
            return NULL;
        }

        // Wait till the picture is available
        sem_wait(picture_sems_pointers[picture_number]);

       

        // Send the picture to the client
        // It should ber the string "Here is picture <picture_number>"
        sprintf(buffer, "Here is picture %d", picture_number);
        SendMessage(*client_socket, buffer);

        // Open sems after leaving the picture
        ReceiveMessage(*client_socket, buffer);
        sem_post(picture_sems_pointers[picture_number]);
    }
}

void *warderProcess(void *arg) {
    for (;;) {
        // Check if there are any clients waiting and there are available slots in gallery
        if (!isEmpty(&clients_queue)) {
            sem_wait(gallery_sem_pointer);
            int *client_socket = malloc(sizeof(int));
            *client_socket = dequeue(&clients_queue);
            pthread_t client_thread;
            pthread_create(&client_thread, NULL, processClient, (void *)client_socket);
        }
    }
}

int main() {
    (void)signal(SIGINT, handleSigInt);

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    initialize(&clients_queue);

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
    if (listen(server_fd, 1) < 0) {
        perror("Listening failed");
        closeConnection();
        exit(EXIT_FAILURE);
    }

    // Create the warder thread
    pthread_create(&warder_process, NULL, warderProcess, NULL);

    for (;;) {
        int new_socket;
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) <
            0) {
            perror("Acceptance failed");
            closeConnection();
            exit(EXIT_FAILURE);
        }

        printf("New client connected to socket: %d\n", new_socket);

        // Add the new client to the queue
        enqueue(&clients_queue, new_socket);
    }

    close(server_fd);

    return 0;
}
