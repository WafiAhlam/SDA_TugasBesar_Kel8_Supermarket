#define BOOLEAN
#ifndef items_H
#include <stdio.h> // Untuk NULL dan printf
#include <stdlib.h> // Untuk malloc, free
#include <string.h> // Untuk strncpy

#define MAX_ID_BARANG 20
#define MAX_NAMA_BARANG 50

// Definisi boolean (dari linkedlist.c)
typedef int boolean;
#define true 1
#define false 0

// Definisi Nil (dari linkedlist.c)
#define Nil NULL

// Struktur data untuk item (barang)
typedef struct item {
    char idbarang[MAX_ID_BARANG];
    char namabarang[MAX_NAMA_BARANG];
    double harga;
} item;

// Node untuk daftar item (mengadaptasi ElmtList dari linkedlist.c)
typedef struct ItemNode {
    int stock; // Stok untuk item ini di inventaris
    struct ItemNode* next;
    item dataBarang; // Data item yang sebenarnya
} ItemNode;

// AddressItemNode adalah pointer ke ItemNode (mengadaptasi address dari linkedlist.c)
typedef ItemNode *AddressItemNode;

// Struktur Listitem (mengadaptasi List dari linkedlist.c)
// Menggunakan head sebagai First, dan tail untuk efisiensi InsertLast
typedef struct Listitem {
    char type[50]; // Contoh: "Elektronik", "Makanan", dll.
    AddressItemNode head; // Menggantikan First(L)
    AddressItemNode tail; // Untuk InsertLast yang efisien
} Listitem;

// Prototipe fungsi-fungsi untuk Item dan Listitem
// Mengadaptasi fungsi-fungsi penting dari linkedlist.c

// Fungsi untuk membuat node item baru (mengadaptasi Alokasi)
AddressItemNode CreateItemNode(item barang, int stock);

// Fungsi untuk dealokasi node item (mengadaptasi DeAlokasi)
void DeAlokasiItemNode(AddressItemNode P);

// Fungsi untuk membuat Listitem kosong (mengadaptasi CreateList)
void CreateListItem(Listitem *L, const char* type);

// Fungsi untuk memeriksa apakah Listitem kosong (mengadaptasi ListEmpty)
boolean ListItemEmpty(Listitem L);

// Fungsi untuk menambahkan item ke akhir list (mengadaptasi InsertLast)
void InsertLastItem(Listitem *L, item barang, int stock);

// Fungsi untuk mencari item berdasarkan ID barang (mengadaptasi Search)
// Mengembalikan pointer ke ItemNode jika ditemukan, NULL jika tidak
AddressItemNode SearchItem(Listitem L, const char* idBarang);

// Fungsi untuk menampilkan semua item dalam list (mengadaptasi PrintInfo)
void PrintListItem(Listitem L);

// Fungsi untuk menampilkan detail satu item (sudah ada di item.h asli)
void displayItem(const item* barang);

#endif // ITEMS_H