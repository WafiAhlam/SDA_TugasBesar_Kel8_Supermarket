#ifndef ITEMS_H
#define ITEMS_H

#include "boolean.h" // Asumsi boolean.h sudah ada
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include avl.h untuk mendapatkan definisi Produk
#include "Avl.h" // <<< PENTING: Pastikan ini mengarah ke file avl.h yang benar
#include "tipedata.h"
// Tidak perlu mendefinisikan 'item' terpisah jika kita menggunakan 'Produk' dari avl.h
// struct item {
//     char idbarang[20];
//     char namabarang[100];
//     float harga;
// };
// typedef struct item item;

/*
// Node untuk Linked List item di dalam setiap rak
// Sekarang ItemNode akan menyimpan salinan Produk dan stoknya di rak tersebut
typedef struct ItemNode {
    Produk dataProduk; // Menggunakan Produk dari avl.h
    int stock;
    struct ItemNode *next;
} ItemNode;

typedef ItemNode *AddressItemNode;
#define Nil NULL // Definisi untuk pointer kosong

// Struktur List untuk menyimpan daftar item dalam sebuah rak
typedef struct {
    AddressItemNode head;
    AddressItemNode tail;
} Listitem;
*/

/*
IS: L adalah pointer ke Listitem sembarang.
FS: Listitem L telah diinisialisasi sebagai list kosong, di mana head dan tail-nya menunjuk ke NULL.

Creator: Wafi Ahlam Rizqulloh
*/
void CreateListItem(Listitem *L);

/*
IS: L adalah Listitem yang terdefinisi.
FS: Mengembalikan nilai TRUE jika L kosong (head == NULL), dan FALSE jika sebaliknya. State dari L tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
boolean ListItemEmpty(Listitem L);

/*
IS: data produk dan nilai stock terdefinisi. Memori heap tersedia.
FS: Sebuah node baru (AddressItemNode) telah dialokasikan di memori dan diisi dengan data produk dan stok. Pointer ke node baru ini dikembalikan. Jika alokasi gagal, mengembalikan NULL.

Creator: Wafi Ahlam Rizqulloh
*/
AddressItemNode CreateItemNode(Produk produk, int stock);

/*
IS: L adalah pointer ke Listitem yang valid, bisa kosong atau berisi.
FS: Semua node item di dalam list L telah dibebaskan dari memori (free). List L menjadi list kosong (head dan tail di-set ke NULL).

Creator: Wafi Ahlam Rizqulloh
*/
void DeallocateListItem(Listitem *L);

/*
IS: L adalah pointer ke Listitem yang valid. produk dan stock terdefinisi.
FS: Sebuah node item baru telah dibuat dan ditambahkan di akhir dari list L. Pointer tail dari L telah diperbarui untuk menunjuk ke node baru tersebut.

Creator: Wafi Ahlam Rizqulloh
*/
void InsertLastItem(Listitem *L, Produk produk, int stock);

/*
IS: L adalah Listitem yang terdefinisi. idProdukCari adalah string ID yang akan dicari.
FS: Mengembalikan pointer (AddressItemNode) ke node item jika ditemukan, dan NULL jika tidak. State dari list L tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
AddressItemNode SearchItem(Listitem L, const char* idProdukCari);

/*
IS: L adalah Listitem yang terdefinisi.
FS: Seluruh isi dari list (nama produk, ID, stok, harga) telah tercetak ke layar. State dari list L tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void PrintListItem(Listitem L);

/*
IS: produk adalah pointer ke struct Produk yang valid.
FS: Detail dari produk (ID, Nama, Harga) telah tercetak ke layar. State dari produk tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void displayItem(const Produk* produk);

/*
IS: L adalah pointer ke Listitem yang valid. idProduk dan jumlah terdefinisi.
FS: Jika produk ditemukan di dalam list dan stoknya mencukupi, maka stok produk tersebut telah berkurang dan fungsi mengembalikan TRUE. Jika tidak, state list tidak berubah dan fungsi mengembalikan FALSE.

Creator: Wafi Ahlam Rizqulloh
*/
boolean kurangiStokItem(Listitem* L, const char* idProduk, int jumlah);

/*
// --- Deklarasi Fungsi Listitem ---
void CreateListItem(Listitem *L); // Tidak perlu type parameter
boolean ListItemEmpty(Listitem L);
AddressItemNode CreateItemNode(Produk produk, int stock); // Menerima Produk
void DeallocateListItem(Listitem *L);
void InsertLastItem(Listitem *L, Produk produk, int stock); // Menerima Produk
AddressItemNode SearchItem(Listitem L, const char* idProdukCari); // Menerima idProduk (string)
void PrintListItem(Listitem L);
void displayItem(const Produk* produk); // Menerima pointer ke Produk
boolean kurangiStokItem(Listitem* L, const char* idProduk, int jumlah);
*/
#endif // ITEMS_H