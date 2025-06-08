#include "Keranjang.h"
#include <stdio.h>
#include <stdlib.h>

Keranjang* createKeranjang() {
    Keranjang* newKeranjang = (Keranjang*) malloc(sizeof(Keranjang));
    if (newKeranjang != NULL) {
        newKeranjang->top = NULL;
        newKeranjang->count = 0;
    }
    return newKeranjang;
}

// --- FUNGSI DIPERBAIKI ---
void pushKeranjang(Keranjang* keranjang, item* barang) {
    // 1. Alokasikan memori untuk Node di keranjang
    NodeKeranjang* newNode = (NodeKeranjang*) malloc(sizeof(NodeKeranjang));
    // PERBAIKAN: Keluar jika alokasi GAGAL (== NULL)
    if (newNode == NULL) {
        perror("Gagal alokasi NodeKeranjang");
        return;
    }

    // 2. Alokasikan memori BARU untuk data item itu sendiri
    newNode->barang = (item*) malloc(sizeof(item));
    if (newNode->barang == NULL) {
        perror("Gagal alokasi item di dalam keranjang");
        free(newNode); // Jangan lupa free node jika alokasi item gagal
        return;
    }

    // 3. Salin data dari sumber ke memori baru di keranjang
    *(newNode->barang) = *barang;

    // 4. Hubungkan node baru ke stack
    newNode->next = keranjang->top;
    keranjang->top = newNode;
    keranjang->count++;
}

item* popKeranjang(Keranjang* keranjang) {
    if (keranjang->top == NULL) {
        return NULL; // Stack kosong
    }

    NodeKeranjang* temp = keranjang->top;
    item* barangDikeluarkan = temp->barang;
    
    keranjang->top = temp->next;
    free(temp); // Hanya free NodeKeranjang
    keranjang->count--;

    return barangDikeluarkan;
}

item* peekKeranjang(const Keranjang* keranjang) {
    if (keranjang->top == NULL) {
        return NULL;
    }
    return keranjang->top->barang;
}

int isKeranjangEmpty(const Keranjang* keranjang) {
    return keranjang->top == NULL;
}

// --- FUNGSI DIPERBAIKI ---
double getTotalHargaKeranjang(const Keranjang* keranjang) {
    double total = 0.0;
    NodeKeranjang* current = keranjang->top;
    while (current != NULL) {
        // PERBAIKAN: Menjumlahkan harga dari setiap item
        total += current->barang->harga; 
        current = current->next;
    }
    return total;
}

void clearKeranjang(Keranjang* keranjang) {
    while (!isKeranjangEmpty(keranjang)) {
        item* barangDibuang = popKeranjang(keranjang);
        free(barangDibuang); // Penting untuk mencegah memory leak
    }
}

// --- FUNGSI DIPERBAIKI ---
void displayKeranjang(const Keranjang* keranjang) {
    if (isKeranjangEmpty(keranjang)) {
        printf("Keranjang kosong.\n");
        return;
    }

    printf("--- Isi Keranjang ---\n");
    NodeKeranjang* current = keranjang->top;
    int index = 1;
    while (current != NULL) {
        item* barang = current->barang;
        // PERBAIKAN: Format string disesuaikan dengan data yang ada
        printf("%d. %s (Harga: %.2f)\n", index++, barang->namabarang, barang->harga);
        current = current->next;
    }
    printf("---------------------\n");
    printf("Total Belanja: %.2f\n", getTotalHargaKeranjang(keranjang));
}
