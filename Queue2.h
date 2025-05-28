/*File header untuk ADT Queue*/

#ifndef queue2_h
#define queue_h
#include "boolean.h"
#include "linked.h"
#define NBElement 10


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