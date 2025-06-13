/*File header untuk ADT Queue*/

#ifndef QUEUE_H
#define QUEUE_H
#define MAX_PELANGGAN_KASIR 10 // kalo mau ada batas maks pelanggan di kasir
#include "boolean.h"
//#include "linked.h"
#include "pelanggan.h"

typedef Pelanggan infotype;

typedef struct QueueNode {
    infotype data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int count;
} Queue;


void createQueue(Queue* q);
bool isQueueEmpty(Queue q);
// boolean is_Full (Queue Q);
QueueNode* newNode(infotype data);
void enqueue(Queue* q, infotype data);
bool dequeue(Queue* q, infotype* dataOut);
void printQueue(Queue q);
void freeQueue(Queue* q);
int countQueue(Queue q);

void saveQueueToFile(Queue* q, const char* filename);
void loadQueueFromFile(Queue* q, const char* filename);

#endif