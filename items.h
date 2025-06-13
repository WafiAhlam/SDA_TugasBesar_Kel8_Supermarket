#ifndef ITEMS_H
#define ITEMS_H

#include "boolean.h" // Asumsi boolean.h sudah ada
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include avl.h untuk mendapatkan definisi Produk
#include "Avl.h" // <<< PENTING: Pastikan ini mengarah ke file avl.h yang benar

// Tidak perlu mendefinisikan 'item' terpisah jika kita menggunakan 'Produk' dari avl.h
// struct item {
//     char idbarang[20];
//     char namabarang[100];
//     float harga;
// };
// typedef struct item item;

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

// --- Deklarasi Fungsi Listitem ---
void CreateListItem(Listitem *L); // Tidak perlu type parameter
boolean ListItemEmpty(Listitem L);
AddressItemNode CreateItemNode(Produk produk, int stock); // Menerima Produk
void DeallocateListItem(Listitem *L);
void InsertLastItem(Listitem *L, Produk produk, int stock); // Menerima Produk
AddressItemNode SearchItem(Listitem L, char* idProdukCari); // Menerima idProduk (string)
void PrintListItem(Listitem L);
void displayItem(const Produk* produk); // Menerima pointer ke Produk

#endif // ITEMS_H