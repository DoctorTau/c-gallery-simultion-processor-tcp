#include "queue.h"
#include <stdio.h>

void queue_initialize(queue *q) {
    q->front = -1;
    q->rear = -1;
}

int queue_isFull(queue *q) {
    if (q->rear == MAX_SIZE - 1) {
        return 1;
    }
    return 0;
}

int queue_isEmpty(queue *q) {
    if (q->front == -1 && q->rear == -1) {
        return 1;
    }
    return 0;
}

void queue_enqueue(queue *q, int element) {
    if (queue_isFull(q)) {
        // printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = element;
    }
}

int queue_dequeue(queue *q) {
    int element;
    if (queue_isEmpty(q)) {
        // printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    } else if (q->front == q->rear) {
        element = q->items[q->front];
        q->front = -1;
        q->rear = -1;
    } else {
        element = q->items[q->front];
        q->front++;
    }
    return element;
}

void queue_display(queue *q) {
    int i;
    if (queue_isEmpty(q)) {
        // printf("Queue is empty. Cannot display.\n");
    } else {
        // printf("Queue elements are: ");
        for (i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}
