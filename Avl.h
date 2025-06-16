// File: avl.h
#ifndef AVL_H
#define AVL_H

#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "tipedata.h"

// Struktur untuk menyimpan informasi produk (DEFINISI PRODUK ADA DI SINI)
/*
typedef struct {
    char idProduk[20]; // Misalnya, barcode atau SKU
    char nama[100];
    float harga;
    int stok;
} Produk;

// Node untuk AVL Tree yang akan menyimpan data Produk
typedef struct RakBTree {
    Produk info;
    struct RakBTree *left;
    struct RakBTree *right;
    int height;
} RakBTree;
*/

/*
IS: Node N terdefinisi, bisa berupa NULL atau node yang valid.
FS: Mengembalikan nilai integer tinggi dari node N. Jika N adalah NULL, mengembalikan 0. Tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
int height(RakBTree *N);

/*
IS: Variabel integer a dan b memiliki nilai.
FS: Mengembalikan nilai integer yang lebih besar antara a dan b.

Creator: Wafi Ahlam Rizqulloh
*/
int max(int a, int b);

/*
IS: Subtree yang berakar di y tidak seimbang dan berat ke kiri (left-heavy). y->left tidak NULL.
FS: Struktur subtree telah dirotasi ke kanan. Node yang tadinya anak kiri y menjadi root baru. Pointer dan tinggi node yang terlibat telah diperbarui. Mengembalikan pointer ke root baru dari subtree yang telah dirotasi.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree *rightRotate(RakBTree *y);

/*
IS: Subtree yang berakar di x tidak seimbang dan berat ke kanan (right-heavy). x->right tidak NULL.
FS: Struktur subtree telah dirotasi ke kiri. Node yang tadinya anak kanan x menjadi root baru. Pointer dan tinggi node yang terlibat telah diperbarui. Mengembalikan pointer ke root baru dari subtree yang telah dirotasi.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree *leftRotate(RakBTree *x);

/*
IS: Node N terdefinisi.
FS: Mengembalikan selisih integer antara tinggi subtree kiri dan subtree kanan dari N. Tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
int getBalance(RakBTree *N);

/*
IS: Data produkBaru terdefinisi. Memori heap tersedia.
FS: Sebuah node RakBTree baru telah dialokasikan di memori. Node tersebut diisi dengan info produkBaru, pointer anak di-set ke NULL, dan tinggi di-set ke 1. Pointer ke node baru ini dikembalikan.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree *newRakBTree(Produk produkBaru);

/*
IS: struct Produk A dan B terdefinisi.
FS: Mengembalikan hasil perbandingan string dari idProduk A dan B menggunakan strcmp.

Creator: Wafi Ahlam Rizqulloh
*/
int compareProduk(Produk produkA, Produk produkB);

/*
IS: node adalah root dari sebuah subtree (bisa NULL).
FS: Mengembalikan pointer ke node dengan nilai terkecil (paling kiri) dalam subtree tersebut. Tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree* minValueNode(RakBTree* node);

/*
IS: node adalah root dari AVL tree (bisa NULL). produk adalah data baru yang akan disisipkan.
FS: Node baru yang berisi data produk telah ditambahkan ke tree sesuai aturan BST. Tree tetap dalam keadaan seimbang (balanced) setelah melalui proses pengecekan balance factor dan rotasi jika diperlukan. Pointer ke root tree (yang mungkin baru) dikembalikan.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree *insertProduk(RakBTree *node, Produk produk);

/*
IS: root adalah pointer ke root dari AVL tree. idProdukCari adalah ID produk yang akan dicari.
FS: Jika produk ditemukan, mengembalikan pointer ke node RakBTree yang berisi produk tersebut. Jika tidak, mengembalikan NULL. Tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree *searchProduk(RakBTree *root, const char* idProdukCari);

/*
IS: root adalah pointer ke root dari AVL tree. idProdukHapus adalah ID produk yang akan dihapus.
FS: Node yang berisi produk dengan ID yang cocok telah dihapus dari tree. Tree tetap dalam keadaan seimbang (balanced) setelah melalui proses pengecekan balance factor dan rotasi jika diperlukan. Pointer ke root tree (yang mungkin baru) dikembalikan.

Creator: Wafi Ahlam Rizqulloh
*/
RakBTree* deleteProduk(RakBTree* root, const char* idProdukHapus);

/*
IS: root adalah pointer ke root dari AVL tree.
FS: Semua informasi produk di dalam tree telah tercetak ke layar secara terurut berdasarkan idProduk (in-order). Tree tidak berubah.
Pemanfaatan dari traversal.

Creator: Wafi Ahlam Rizqulloh
*/
void inOrderProduk(RakBTree *root);

/*
IS: node adalah pointer-ke-pointer dari root tree. Tree bisa kosong atau berisi node.
FS: Semua node di dalam tree telah dibebaskan dari memori (free). Pointer root asli yang ditunjuk oleh 'node' sekarang bernilai NULL.

Creator: Wafi Ahlam Rizqulloh
*/
void deleteTree(RakBTree **node);

/*
// --- Deklarasi Fungsi AVL Tree ---
int height(RakBTree *N);
int max(int a, int b);
RakBTree *newRakBTree(Produk produkBaru);
int getBalance(RakBTree *N);
RakBTree *rightRotate(RakBTree *y);
RakBTree *leftRotate(RakBTree *x);
int compareProduk(Produk produkA, Produk produkB);
RakBTree *insertProduk(RakBTree *node, Produk produk);
RakBTree *searchProduk(RakBTree *root, const char* idProdukCari);
RakBTree* deleteProduk(RakBTree* root, const char* idProdukHapus);
RakBTree* minValueNode(RakBTree* node);
void inOrderProduk(RakBTree *root); //Pemanfaatan dari traversal
void deleteTree(RakBTree **node);
*/
#endif 