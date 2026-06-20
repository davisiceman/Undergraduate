#include "circular.h"
#include <stdio.h>

void CircularInitialize(CircularQueue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

void CircularEnqueue(CircularQueue *q, int value) {
    if (q->count == QUEUE_SIZE) {
        // Queue is full; overwrite the oldest value
        q->head = (q->head + 1) % QUEUE_SIZE;
    } else {
        q->count++;
    }
    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % QUEUE_SIZE;
}

int CircularDequeue(CircularQueue *q, int *pValue) {
    if (q->count == 0) {
        // Queue is empty
        return -1;
    }
    *pValue = q->data[q->head];
    q->head = (q->head + 1) % QUEUE_SIZE;
    q->count--;
    return 0;
}
