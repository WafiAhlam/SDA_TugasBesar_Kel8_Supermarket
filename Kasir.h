#ifndef KASIR_H
#define KASIR_H
#include "Pelanggan.h"
#include "queue.h"
#include "keranjang.h"

// Variabel global untuk statistik kasir
extern double totalPemasukan;
extern int totalPelangganDilayani;

// Menambahkan pelanggan ke antrian
void tambahPelanggan(Queue *Q, infotype pelanggan);

// Memproses pelanggan di depan antrian
void prosesPelanggan(Queue *Q);

// Menampilkan seluruh antrian pelanggan
void tampilkanAntrian(Queue Q);

// Menampilkan statistik kasir
// void tampilkanStatistik();

#endif // KASIR_H










#endif