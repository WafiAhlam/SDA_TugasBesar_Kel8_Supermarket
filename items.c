#include <stdio.h>
#include <string.h>
#include "items.h"
#include <stdlib.h>



#include "item.h" // Menginclude header item.h yang sudah direvisi
#include <stdio.h>
#include <stdlib.h> // Untuk malloc, free
#include <string.h> // Untuk strncpy, strcmp

// Fungsi untuk membuat node item baru (mengadaptasi Alokasi dari linkedlist.c)
// Mengalokasikan memori untuk ItemNode dan menginisialisasi data
AddressItemNode CreateItemNode(item barang, int stock) {
    AddressItemNode newNode = (AddressItemNode)malloc(sizeof(ItemNode));
    if (newNode != Nil) { // Jika alokasi berhasil
        newNode->dataBarang = barang; // Salin struct item
        newNode->stock = stock;       // Set stock
        newNode->next = Nil;          // Next node adalah NULL
    } else {
        perror("Gagal mengalokasikan memori untuk ItemNode");
    }
    return newNode;
}

// Fungsi untuk dealokasi node item (mengadaptasi DeAlokasi dari linkedlist.c)
// Mengembalikan memori node ke sistem
void DeAlokasiItemNode(AddressItemNode P) {
    if (P != Nil) {
        free(P);
    }
}

// Fungsi untuk membuat Listitem kosong (mengadaptasi CreateList dari linkedlist.c)
// Menginisialisasi head dan tail list menjadi NULL
void CreateListItem(Listitem *L, const char* type) {
    L->head = Nil;
    L->tail = Nil;
    strncpy(L->type, type, sizeof(L->type) - 1);
    L->type[sizeof(L->type) - 1] = '\0';
    printf("List item tipe '%s' telah dibuat kosong.\n", L->type);
}

// Fungsi untuk memeriksa apakah Listitem kosong (mengadaptasi ListEmpty dari linkedlist.c)
// Mengembalikan true jika list kosong, false jika tidak
boolean ListItemEmpty(Listitem L) {
    return (L.head == Nil);
}

// Fungsi untuk menambahkan item ke akhir list (mengadaptasi InsertLast dari linkedlist.c)
// Menggunakan tail untuk penambahan yang efisien O(1)
void InsertLastItem(Listitem *L, item barang, int stock) {
    AddressItemNode P = CreateItemNode(barang, stock);
    if (P != Nil) { // Jika alokasi node berhasil
        if (ListItemEmpty(*L)) { // Jika list kosong, node baru menjadi head dan tail
            L->head = P;
            L->tail = P;
        } else { // Jika list tidak kosong, tambahkan setelah tail dan perbarui tail
            L->tail->next = P;
            L->tail = P;
        }
        printf("Item '%s' (ID: %s) ditambahkan ke list.\n", barang.namabarang, barang.idbarang);
    }
}

// Fungsi untuk mencari item berdasarkan ID barang (mengadaptasi Search dari linkedlist.c)
// Mengembalikan pointer ke ItemNode jika ditemukan, NULL jika tidak
AddressItemNode SearchItem(Listitem L, const char* idBarang) {
    AddressItemNode P = L.head;
    while (P != Nil) {
        if (strcmp(P->dataBarang.idbarang, idBarang) == 0) {
            return P; // Item ditemukan
        }
        P = P->next;
    }
    return Nil; // Item tidak ditemukan
}

// Fungsi untuk menampilkan semua item dalam list (mengadaptasi PrintInfo dari linkedlist.c)
void PrintListItem(Listitem L) {
    AddressItemNode P = L.head;
    if (ListItemEmpty(L)) {
        printf("List Item Tipe '%s' Kosong.\n", L.type);
    } else {
        printf("--- Daftar Item Tipe '%s' ---\n", L.type);
        while (P != Nil) {
            displayItem(&(P->dataBarang)); // Tampilkan detail item
            printf("  Stok: %d\n", P->stock);
            P = P->next;
        }
        printf("----------------------------\n");
    }
}

// Fungsi untuk menampilkan detail satu item (sudah ada di item.h asli)
void displayItem(const item* barang) {
    printf("ID: %s, Nama: %s, Harga: %.2f",
           barang->idbarang, barang->namabarang, barang->harga);
}
