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

// Menambahkan data ke antrian
void enqueue(Queue* q, infotype data) {
    QueueNode* node = newNode(data);
    if (node == NULL) {
        printf("Gagal mengalokasi memori.\n");
        return;
    }

    if (isQueueEmpty(*q)) {
        q->front = node;
        q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

// Menghapus data dari antrian
bool dequeue(Queue* q, infotype* dataOut) {
    if (isQueueEmpty(*q)) {
        return false;
    }

    QueueNode* temp = q->front;
    *dataOut = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return true;
}

// Menampilkan isi queue
void printQueue(Queue q) {
    QueueNode* curr = q.front;
    if (isQueueEmpty(q)) {
        printf("Antrian kosong.\n");
        return;
    }

    printf("Daftar antrian:\n");
    while (curr != NULL) {
        printf("- %s datang pada %s\n", curr->data.nama, curr->data.waktuDatang);
        curr = curr->next;
    }
}

// Menghapus seluruh antrian
void freeQueue(Queue* q) {
    infotype temp;
    while (dequeue(q, &temp)) {
        if (temp.KPelanggan != NULL) {
            freeKeranjang(temp.KPelanggan); 
            free(temp.KPelanggan);          
        }
    }
}
