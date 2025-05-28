#ifndef KERANJANG_H
#define KERANJANG_H

#include "items.h" // Bergantung pada item.h

// Node untuk stack keranjang
typedef struct NodeKeranjang {
    item* barang; // Data yang disimpan adalah Item
    struct NodeKeranjang* next;
} NodeKeranjang;

// Struktur Stack Keranjang
typedef struct {
    NodeKeranjang* top;
    int count; // Jumlah item dalam keranjang
} Keranjang;

// Inisialisasi keranjang
Keranjang* createKeranjang();

// Operasi Stack
// Menambah item ke keranjang
void pushKeranjang(Keranjang* keranjang, item* barang);

// Mengeluarkan item dari keranjang
item* popKeranjang(Keranjang* keranjang); // Mengembalikan Item yang di-pop

// Melihat item teratas tanpa mengeluarkan
item* peekKeranjang(const Keranjang* keranjang);

// Memeriksa apakah keranjang kosong
int isKeranjangEmpty(const Keranjang* keranjang);

// Menghitung total harga dalam keranjang
double getTotalHargaKeranjang(const Keranjang* keranjang);

// Membersihkan semua item dari keranjang (free memory)
void clearKeranjang(Keranjang* keranjang);
void displayKeranjang(const Keranjang* keranjang);

#endif // KERANJANG_H