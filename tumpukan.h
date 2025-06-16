#ifndef TUMPUKAN_H
#define TUMPUKAN_H

#include "avl.h" // Diperlukan untuk definisi 'Produk'
#include "boolean.h" // Diperlukan untuk tipe data boolean
#include "tipedata.h"
/**
 * File: rak_tumpukan.h
 * Deskripsi: Header untuk ADT Stack (tumpukan) yang merepresentasikan rak LIFO.
 * - Admin melakukan PUSH.
 * - Pelanggan melakukan POP.
 */
/*
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
*/

// --- PROTOTYPE FUNGSI STACK ---

/*
IS: Memori heap tersedia. nama adalah string yang valid untuk nama rak.
FS: Sebuah objek RakTumpukan baru telah dibuat dan diinisialisasi (top = NULL, count = 0, namaRak disalin). Pointer ke objek baru ini dikembalikan.

Creator: Marelly Salsa Kasih Risky
*/
RakTumpukan* createRakTumpukan(const char* nama);

/*
IS: rak terdefinisi, bisa kosong atau berisi item.
FS: Mengembalikan nilai TRUE jika top dari rak adalah NULL, dan FALSE jika sebaliknya. State dari rak tidak berubah.

Creator: Marelly Salsa Kasih Risky
*/
boolean isRakTumpukanEmpty(RakTumpukan* rak);

/*
IS: rak adalah pointer ke Stack yang valid. produk adalah data yang akan ditambahkan.
FS: Sebuah node baru yang berisi data produk telah ditambahkan ke bagian atas (top) dari tumpukan. Atribut count pada rak bertambah satu.

Creator: Marelly Salsa Kasih Risky
*/
void pushToRak(RakTumpukan* rak, Produk produk);

/*
IS: rak adalah pointer ke Stack yang valid. produkDikeluarkan adalah pointer ke variabel Produk untuk menampung hasil.
FS: Jika rak tidak kosong, node teratas dihapus, datanya disalin ke produkDikeluarkan, dan count berkurang. Fungsi mengembalikan TRUE. Jika rak kosong, state tidak berubah dan fungsi mengembalikan FALSE.

Creator: Marelly Salsa Kasih Risky
*/
boolean popFromRak(RakTumpukan* rak, Produk* produkDikeluarkan);

/*
IS: rak terdefinisi.
FS: Seluruh isi dari tumpukan telah tercetak ke layar secara berurutan dari atas (top) ke bawah. State dari rak tidak berubah.

Creator: Marelly Salsa Kasih Risky
*/
void displayRakTumpukan(RakTumpukan* rak);

/*
IS: rak adalah pointer-ke-pointer dari sebuah objek RakTumpukan yang valid.
FS: Semua node di dalam tumpukan dan objek RakTumpukan itu sendiri telah dibebaskan dari memori (free). Pointer asli yang ditunjuk oleh 'rak' sekarang bernilai NULL.

Creator: Marelly Salsa Kasih Risky
*/
void destroyRakTumpukan(RakTumpukan** rak);


/*
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
*/
#endif