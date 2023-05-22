#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100

typedef struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
} queue;

void queue_initialize(queue *q);
int queue_isFull(queue *q);
int queue_isEmpty(queue *q);
void queue_enqueue(queue *q, int element);
int queue_dequeue(queue *q);
void queue_display(queue *q);

#endif
