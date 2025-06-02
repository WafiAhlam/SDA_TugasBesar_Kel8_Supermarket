/*File header untuk ADT Queue*/

#ifndef QUEUE_H
#define QUEUE_H
#include "boolean.h"
#include "linked.h"
#define NBElement 10

typedef Pelanggan infotype;

//typedef struct {          //buat total keranjang pelanggan
//    char nama[50];        //bisa juga misal admin mau nyimpen data pelanggan (nama sama total belanja)
//    int totalBelanja;     
//} infotype;

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

//Fungsi untuk admin
//int TotalPemasukan(Queue Q);
//float RataRataPemasukan(Queue Q);
//int JumlahPelangganDilayani(Queue Q);

#endif