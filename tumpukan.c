#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tumpukan.h"
#include "boolean.h"

// Membuat rak tumpukan baru yang kosong.
RakTumpukan* createRakTumpukan(const char* nama) {
    RakTumpukan* rak = (RakTumpukan*) malloc(sizeof(RakTumpukan));
    if (rak == NULL) {
        perror("Gagal alokasi memori untuk RakTumpukan");
        return NULL;
    }
    rak->top = NULL;
    rak->count = 0;
    strncpy(rak->namaRak, nama, 49);
    rak->namaRak[49] = '\0'; // Memastikan null-terminated
    return rak;
}

// Memeriksa apakah rak kosong.
boolean isRakTumpukanEmpty(RakTumpukan* rak) {
    return (rak->top == NULL);
}

// Menambah produk ke atas tumpukan (untuk Admin).
void pushToRak(RakTumpukan* rak, Produk produk) {
    NodeTumpukan* newNode = (NodeTumpukan*) malloc(sizeof(NodeTumpukan));
    if (newNode == NULL) {
        perror("Gagal alokasi memori untuk NodeTumpukan");
        return;
    }
    newNode->info = produk;
    newNode->next = rak->top;
    rak->top = newNode;
    rak->count++;
    printf("Admin meletakkan '%s' ke rak '%s'.\n", produk.nama, rak->namaRak);
}

// Mengambil produk dari atas tumpukan (untuk Pelanggan).
boolean popFromRak(RakTumpukan* rak, Produk* produkDikeluarkan) {
    if (isRakTumpukanEmpty(rak)) {
        printf("Rak '%s' kosong, tidak ada yang bisa diambil.\n", rak->namaRak);
        return false;
    }

    NodeTumpukan* temp = rak->top;
    *produkDikeluarkan = temp->info; // Salin data produk yang di-pop

    rak->top = rak->top->next;
    free(temp);
    rak->count--;

    printf("Pelanggan mengambil '%s' dari rak '%s'.\n", produkDikeluarkan->nama, rak->namaRak);
    return true;
}

// Menampilkan semua isi rak dari atas ke bawah.
void displayRakTumpukan(RakTumpukan* rak) {
    printf("\n--- Isi Rak Tumpukan: %s ---\n", rak->namaRak);
    if (isRakTumpukanEmpty(rak)) {
        printf("Rak ini kosong.\n");
    } else {
        NodeTumpukan* current = rak->top;
        int i = 1;
        printf("(Paling Atas)\n");
        while (current != NULL) {
            printf("%d. %s (ID: %s)\n", i, current->info.nama, current->info.idProduk);
            current = current->next;
            i++;
        }
        printf("(Paling Bawah)\n");
    }
    printf("--------------------------------\n");
}

// Menghancurkan rak dan membebaskan semua memori.
void destroyRakTumpukan(RakTumpukan** rak) {
    if (*rak == NULL) return;

    Produk dummy;
    while (!isRakTumpukanEmpty(*rak)) {
        popFromRak(*rak, &dummy); // Gunakan pop untuk menghapus dan membebaskan node
    }
    free(*rak);
    *rak = NULL;
}