/*File header untuk ADT Queue*/

#ifndef QUEUE_H
#define QUEUE_H
#define MAX_PELANGGAN_KASIR 10
#include "boolean.h"
#include "linked.h"
#include "pelanggan.h"
#define NBElement 10

typedef Pelanggan infotype;

typedef struct Queue {
    address front;
    address rear;
} Queue;


void createQueue(Queue* q);
bool isQueueEmpty(Queue q)
// boolean is_Full (Queue Q);
QueueNode* newNode(infotype data);
void EnQueue (Queue *Q, infotype X);
void deQueue (Queue *Q, infotype *X);
void PrintQueue(Queue q);
void freeQueue(Queue* q);

#endif