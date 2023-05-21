#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100

typedef struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
} queue;

void initialize(queue *q);
int isFull(queue *q);
int isEmpty(queue *q);
void enqueue(queue *q, int element);
int dequeue(queue *q);
void display(queue *q);

#endif
