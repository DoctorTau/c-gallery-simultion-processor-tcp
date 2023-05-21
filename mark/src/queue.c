#include "queue.h"
#include <stdio.h>

void initialize(queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(queue *q) {
    if (q->rear == MAX_SIZE - 1) {
        return 1;
    }
    return 0;
}

int isEmpty(queue *q) {
    if (q->front == -1 && q->rear == -1) {
        return 1;
    }
    return 0;
}

void enqueue(queue *q, int element) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = element;
    }
}

int dequeue(queue *q) {
    int element;
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
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

void display(queue *q) {
    int i;
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot display.\n");
    } else {
        printf("Queue elements are: ");
        for (i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}
