#ifndef KASIR_H
#define KASIR_H

#include "Keranjang.h" // Butuh definisi KeranjangBelanja
#include "boolean.h"
#include "pelanggan.h"
#include "tipedata.h"
/*
// Node untuk linked list Queue
typedef struct AntrianNode {
    Pelanggan dataPelanggan;
    struct AntrianNode* next;
} AntrianNode;

// Struktur utama untuk ADT Queue
typedef struct {
    AntrianNode* head;
    AntrianNode* tail;
    int jumlahPelanggan;
} AntrianKasir;
*/

// --- PROTOTYPE FUNGSI ANTRIAN KASIR (QUEUE) ---

// Membuat antrian kasir baru yang kosong
AntrianKasir* createAntrian();

// Memeriksa apakah antrian kosong
boolean isAntrianKosong(AntrianKasir* antrian);

// Menambahkan pelanggan ke akhir antrian (enqueue)
void enqueuePelanggan(AntrianKasir* antrian, Pelanggan pelanggan);

// Mengeluarkan pelanggan dari depan antrian (dequeue)
// Mengembalikan TRUE jika berhasil, FALSE jika antrian kosong
boolean dequeuePelanggan(AntrianKasir* antrian, Pelanggan* pelangganDilayani);

// Menampilkan semua pelanggan yang sedang mengantri
void displayAntrian(AntrianKasir* antrian);

// Menghancurkan antrian dan membebaskan memori
void destroyAntrian(AntrianKasir** antrian);

#endif // KASIR_H