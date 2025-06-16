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


/*
IS: Memori heap tersedia untuk dialokasikan.
FS: Sebuah objek KeranjangBelanja baru telah dibuat di memori dengan head menunjuk ke NULL, jumlahItemUnik=0, dan totalHarga=0.0. Pointer ke objek baru ini dikembalikan.

Creator: Wafi Ahlam Rizqulloh
*/
KeranjangBelanja* createKeranjang();

/*
IS: keranjang terdefinisi, bisa kosong atau berisi item.
FS: Mengembalikan nilai TRUE jika head dari keranjang adalah NULL, dan FALSE jika tidak. State dari keranjang tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
boolean isKeranjangEmpty(KeranjangBelanja* keranjang);

/*
IS: keranjang dan produk terdefinisi. kuantitas adalah integer positif.
FS: Jika produk sudah ada di keranjang, kuantitasnya bertambah. Jika belum ada, sebuah node baru yang berisi produk tersebut ditambahkan ke dalam keranjang. totalHarga keranjang telah diperbarui.

Creator: Wafi Ahlam Rizqulloh
*/
void tambahProdukKeKeranjang(KeranjangBelanja* keranjang, Produk produk, int kuantitas);

/*
IS: keranjang terdefinisi. idProduk adalah ID yang akan dikurangi. kuantitas adalah integer positif.
FS: Jika produk ditemukan, kuantitasnya di keranjang berkurang. Jika kuantitas menjadi 0 atau kurang, node produk tersebut dihapus sepenuhnya dari keranjang. totalHarga keranjang telah diperbarui.

Creator: Wafi Ahlam Rizqulloh
*/
void kurangiProdukDariKeranjang(KeranjangBelanja* keranjang, const char* idProduk, int kuantitas);

/*
IS: keranjang terdefinisi.
FS: Seluruh isi dari keranjang (nama produk, kuantitas, harga, subtotal, dan total) telah tercetak ke layar dengan format yang rapi. State dari keranjang tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void displayKeranjang(KeranjangBelanja* keranjang);

/*
IS: keranjang adalah pointer-ke-pointer dari sebuah objek KeranjangBelanja yang valid.
FS: Semua node di dalam keranjang dan objek KeranjangBelanja itu sendiri telah dibebaskan dari memori (free). Pointer asli yang ditunjuk oleh 'keranjang' sekarang bernilai NULL.

Creator: Wafi Ahlam Rizqulloh
*/
void destroyKeranjang(KeranjangBelanja** keranjang);

/*
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
*/
#endif // KERANJANG_BELANJA_H