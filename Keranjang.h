#ifndef KERANJANG_H
#define KERANJANG_H

#include "avl.h"      // Diperlukan untuk definisi 'Produk'
#include "boolean.h"  // Diperlukan untuk tipe data boolean
#include "tipedata.h"
/**
 * File: keranjang_belanja.h
 * Deskripsi: Header untuk ADT Keranjang Belanja Pelanggan.
 * Diimplementasikan sebagai Linked List untuk fleksibilitas maksimal.
 */
/*
// Node untuk setiap item unik di dalam keranjang
typedef struct KeranjangNode {
    Produk infoProduk;           // Informasi lengkap produk
    int    kuantitas;              // Jumlah produk ini yang ada di keranjang
    struct KeranjangNode *next;  // Pointer ke item berikutnya
} KeranjangNode;

// Struktur utama yang merepresentasikan keranjang belanja
typedef struct  KeranjangBelanja {
    KeranjangNode* head;           // Pointer ke item pertama di keranjang
    int            jumlahItemUnik; // Jumlah jenis produk yang berbeda
    double         totalHarga;     // Total harga semua barang di keranjang
} KeranjangBelanja;
*/

// --- PROTOTYPE FUNGSI KERANJANG BELANJA ---

// Membuat dan mengembalikan pointer ke keranjang belanja baru yang kosong.
KeranjangBelanja* createKeranjang();

// Memeriksa apakah keranjang belanja kosong.
boolean isKeranjangEmpty(KeranjangBelanja* keranjang);
// Menambahkan produk ke keranjang.
// Jika produk sudah ada, kuantitasnya akan ditambah.
// Jika belum ada, item baru akan dibuat.
void tambahProdukKeKeranjang(KeranjangBelanja* keranjang, Produk produk, int kuantitas);
// Mengurangi kuantitas produk dari keranjang.
// Jika kuantitas menjadi nol atau kurang, produk akan dihapus sepenuhnya.
void kurangiProdukDariKeranjang(KeranjangBelanja* keranjang, const char* idProduk, int kuantitas);
// Menampilkan isi keranjang belanja secara rapi.
void displayKeranjang(KeranjangBelanja* keranjang);
// Menghancurkan keranjang dan membebaskan semua memori yang digunakan.
void destroyKeranjang(KeranjangBelanja** keranjang);

#endif // KERANJANG_BELANJA_H