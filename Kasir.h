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
/*
IS: Memori heap tersedia untuk alokasi.
FS: Sebuah objek AntrianKasir baru telah dibuat dan diinisialisasi (head dan tail = NULL, jumlahPelanggan = 0). Pointer ke objek baru ini dikembalikan.

Creator: Wafi Ahlam Rizqulloh
*/
AntrianKasir* createAntrian();

/*
IS: antrian terdefinisi, bisa kosong atau berisi pelanggan.
FS: Mengembalikan nilai TRUE jika head dari antrian adalah NULL, dan FALSE jika sebaliknya. State dari antrian tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
boolean isAntrianKosong(AntrianKasir* antrian);

/*
IS: antrian dan data pelanggan terdefinisi.
FS: Sebuah node baru yang berisi data pelanggan telah ditambahkan ke akhir (tail) dari antrian. jumlahPelanggan pada antrian bertambah satu.

Creator: Wafi Ahlam Rizqulloh
*/
void enqueuePelanggan(AntrianKasir* antrian, Pelanggan pelanggan);

/*
IS: antrian terdefinisi, bisa kosong atau berisi. pelangganDilayani adalah pointer ke variabel Pelanggan.
FS: Jika antrian tidak kosong, node terdepan (head) dihapus, datanya disalin ke pelangganDilayani, dan jumlahPelanggan berkurang. Fungsi mengembalikan TRUE. Jika kosong, fungsi mengembalikan FALSE dan state tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
boolean dequeuePelanggan(AntrianKasir* antrian, Pelanggan* pelangganDilayani);

/*
IS: antrian terdefinisi.
FS: Semua nama pelanggan di dalam antrian telah tercetak ke layar secara berurutan dari head ke tail. State dari antrian tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void displayAntrian(AntrianKasir* antrian);

/*
IS: antrian adalah pointer-ke-pointer dari sebuah objek AntrianKasir yang valid.
FS: Semua node di dalam antrian dan objek AntrianKasir itu sendiri telah dibebaskan dari memori. Pointer asli yang ditunjuk oleh 'antrian' sekarang bernilai NULL.

Creator: Wafi Ahlam Rizqulloh
*/
void destroyAntrian(AntrianKasir** antrian);


/*
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
*/
#endif // KASIR_H