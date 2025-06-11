// File: item.c
#include "items.h"

// Fungsi untuk membuat Listitem kosong
void CreateListItem(Listitem *L) {
    L->head = Nil;
    L->tail = Nil;
    // printf yang ada sebelumnya dihapus agar lebih bersih
}

// Fungsi untuk memeriksa apakah Listitem kosong
boolean ListItemEmpty(Listitem L) {
    return (L->head == Nil);
}

// Fungsi untuk membuat node item baru
AddressItemNode CreateItemNode(item barang, int stock) {
    AddressItemNode newNode = (AddressItemNode)malloc(sizeof(ItemNode));
    if (newNode != Nil) {
        newNode->dataBarang = barang;
        newNode->stock = stock;
        newNode->next = Nil;
    }
    return newNode;
}

// Fungsi untuk menambahkan item ke akhir list
void InsertLastItem(Listitem *L, item barang, int stock) {
    AddressItemNode P = CreateItemNode(barang, stock);
    if (P != Nil) {
        if (ListItemEmpty(*L)) {
            L->head = P;
            L->tail = P;
        } else {
            L->tail->next = P;
            L->tail = P;
        }
        // printf yang ada sebelumnya dihapus
    }
}

// Fungsi untuk mencari item berdasarkan ID barang
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

// Fungsi untuk menampilkan semua item dalam sebuah list (rak)
void PrintListItem(Listitem L) {
    AddressItemNode P = L.head;
    if (ListItemEmpty(L)) {
        printf("Rak ini kosong.\n");
    } else {
        int i = 1;
        printf("----------------------------------\n");
        printf("Daftar Barang di Lokasi ini:\n");
        while (P != Nil) {
            printf("%d. %s (ID: %s, Stok: %d, Harga: %.0f)\n", 
                   i, P->dataBarang.namabarang, P->dataBarang.idbarang, P->stock, P->dataBarang.harga);
            i++;
            P = P->next;
        }
        printf("----------------------------------\n");
    }
}

// Fungsi untuk menampilkan detail satu item (tidak banyak berubah)
void displayItem(const item* barang) {
    printf("ID: %s, Nama: %s, Harga: %.2f",
           barang->idbarang, barang->namabarang, barang->harga);
}