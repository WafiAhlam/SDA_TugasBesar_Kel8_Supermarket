#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "pelanggan.h" 

// Membuat queue kosong
void createQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Mengecek apakah queue kosong
bool isQueueEmpty(Queue q) {
    return (q.front == NULL && q.rear == NULL);
}

// /*Memeriksa apakah queue penuh */
// boolean is_Full (Queue Q)
// {
// 	int count = 0;
//     address p = Q.front;

//     while(p != NULL) 
//     {
//         count++;
//         if (count == NBElement) 
//         {
//             return true;
//         }
//         p = p->next;
//     }
//     return false;
// }

// Mengalokasi node baru
QueueNode* newNode(infotype data) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

/*Melekukan insertion pada queue*/
void EnQueue(Queue *Q, infotype X) 
{
    if (is_Full(*Q)) return;

    address add = Alokasi(X);
    if (add != NULL) 
    {
        add->next = NULL;

        if (is_Empty(*Q)) 
        {
            Q->front = add;
            Q->rear = add;
        } else {
            Q->rear->next = add;
            Q->rear = add;
        }
    }
}

/*Melakukan deletion pada queue*/
void deQueue(Queue *Q, infotype *X) 
{
    if (is_Empty(*Q)) return;
    address del = Q->front;
    *X = del->info;
    Q->front = Q->front->next;
    if (Q->front == NULL) 
    {
        Q->rear = NULL;
    }
    free(del);
}


void PrintQueue(Queue q) {
    address cursor = q.front;

    if (is_Empty(q)) 
    {
        printf("Antrian kosong...\n");
        return;
    }

    printf("Antrian sekarang:\n");
    while (cursor != NULL) 
    {
        printf("- %s\n", cursor->info.nama);
        cursor = cursor->next;
    }
}

// Menghapus seluruh antrian
void freeQueue(Queue* q) {
    infotype temp;
    while (dequeue(q, &temp)) {
        // Jika perlu bebaskan alokasi tambahan (misal: string malloc di nama)
    }
}