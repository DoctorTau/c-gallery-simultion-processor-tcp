#ifndef COMMON_H
#define COMMON_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/wait.h>


void printError(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

#define NUMBER_OF_PICTURES 5
#define EXIT_MESSAGE "exit"

const char vahter_sem_name[] = "/vahter_sem";
const char picture_sem_name_template[] = "/picture_sem";

char picture_sem_names[NUMBER_OF_PICTURES][sizeof(picture_sem_name_template) + 1];
sem_t *gallery_sem_pointer;
sem_t *picture_sems_pointers[NUMBER_OF_PICTURES];

void generatePictureSemNames() {
    for (int i = 0; i < NUMBER_OF_PICTURES; i++) {
        sprintf(picture_sem_names[i], "%s%d", picture_sem_name_template, i);
    }
}

void closeAllSems() {
    sem_close(gallery_sem_pointer);
    for (int i = 0; i < NUMBER_OF_PICTURES; i++) {
        sem_close(picture_sems_pointers[i]);
    }

    sem_unlink(vahter_sem_name);
    for (int i = 0; i < NUMBER_OF_PICTURES; i++) {
        sem_unlink(picture_sem_names[i]);
    }
}

void initSems(){
    gallery_sem_pointer = sem_open(vahter_sem_name, O_CREAT, 0666, 50);
    if (gallery_sem_pointer == SEM_FAILED) {
        printError("Could not create gallery semaphore.");
    }

    generatePictureSemNames();

    for (int i = 0; i < NUMBER_OF_PICTURES; i++) {
        picture_sems_pointers[i] = sem_open(picture_sem_names[i], O_CREAT, 0666, 10);
        if (picture_sems_pointers[i] == SEM_FAILED) {
            printError("Could not create picture semaphore.");
        }
    }
}

#endif
