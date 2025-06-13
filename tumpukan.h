#ifndef TUMPUKAN_H
#define TUMPUKAN_H

#include "avl.h" // Diperlukan untuk definisi 'Produk'
#include "boolean.h" // Diperlukan untuk tipe data boolean

/**
 * File: rak_tumpukan.h
 * Deskripsi: Header untuk ADT Stack (tumpukan) yang merepresentasikan rak LIFO.
 * - Admin melakukan PUSH.
 * - Pelanggan melakukan POP.
 */

// Node untuk tumpukan
typedef struct NodeTumpukan {
    Produk info;
    struct NodeTumpukan* next;
} NodeTumpukan;

// Struktur utama untuk Stack (Rak Tumpukan)
typedef struct {
    NodeTumpukan* top;
    int count;
    char namaRak[50];
} RakTumpukan;


// --- PROTOTYPE FUNGSI STACK ---

// Membuat rak tumpukan baru yang kosong.
RakTumpukan* createRakTumpukan(const char* nama);

// Memeriksa apakah rak kosong.
boolean isRakTumpukanEmpty(RakTumpukan* rak);

// Menambah produk ke atas tumpukan (untuk Admin).
void pushToRak(RakTumpukan* rak, Produk produk);

// Mengambil produk dari atas tumpukan (untuk Pelanggan).
// Mengembalikan TRUE jika berhasil, FALSE jika rak kosong.
// Produk yang di-pop akan disimpan di 'produkDikeluarkan'.
boolean popFromRak(RakTumpukan* rak, Produk* produkDikeluarkan);

// Menampilkan semua isi rak dari atas ke bawah.
void displayRakTumpukan(RakTumpukan* rak);

// Menghancurkan rak dan membebaskan semua memori.
void destroyRakTumpukan(RakTumpukan** rak);

#endif