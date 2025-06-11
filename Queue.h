/*File header untuk ADT Queue*/

#ifndef QUEUE_H
#define QUEUE_H
#include "boolean.h"
#include "linked.h"
#include "pelanggan.h"
#define NBElement 10

typedef Pelanggan infotype;

typedef struct Queue {
    address front;
    address rear;
} Queue;


void CreateQueue (Queue *Q);
boolean is_Empty (Queue Q);
boolean is_Full (Queue Q);
void EnQueue (Queue *Q, infotype X);
void deQueue (Queue *Q, infotype *X);
void PrintQueue(Queue q);

#endif