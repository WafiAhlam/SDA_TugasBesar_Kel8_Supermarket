#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "pelanggan.h" 

// Membuat queue kosong
void createQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0; // kalo mau ada maks pelanggan
}

// Mengecek apakah queue kosong
bool isQueueEmpty(Queue q) {
    return (q.front == NULL && q.rear == NULL);
}

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
    if (countQueue(*q) >= MAX_PELANGGAN_KASIR) {
        printf("Antrian penuh. Maksimal %d pelanggan.\n", MAX_PELANGGAN_KASIR);
        return;
    }

    // untuk waktu datang
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(data.waktuDatang, sizeof(data.waktuDatang), "%Y-%m-%d %H:%M:%S", t);

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
    q->count++;
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
    q->count--;
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

// kalo mau ada maks pelanggan
int countQueue(Queue q) {
    return q.count;
}

void saveQueueToFile(Queue* q, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file %s untuk penulisan.\n", filename);
        return;
    }

    QueueNode* current = q->front;
    while (current != NULL) {
        fprintf(file, "%s|%s\n", current->data.nama, current->data.waktuDatang);
        current = current->next;
    }

    fclose(file);
}

void loadQueueFromFile(Queue* q, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s untuk pembacaan.\n", filename);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        Pelanggan p;
        sscanf(line, "%49[^|]|%49[^\n]", p.nama, p.waktuDatang);
        p.KPelanggan = NULL; 
        enqueue(q, p);
    }

    fclose(file);
}