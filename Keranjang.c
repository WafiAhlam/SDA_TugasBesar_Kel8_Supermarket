#include "Keranjang.h"
#include <stdio.h>
#include <stdlib.h>.

Keranjang* createKeranjang() {
    Keranjang* newKeranjang = (Keranjang*) malloc(sizeof(Keranjang));
    if (newKeranjang != NULL) {
        newKeranjang->top = NULL;
        newKeranjang->count = 0;
    }
    return newKeranjang;
}

void pushKeranjang(Keranjang* keranjang, item* barang) {
    NodeKeranjang* newNode = (NodeKeranjang*) malloc(sizeof(NodeKeranjang));
    if (newNode != NULL) {
        newNode->barang = barang;
        newNode->next = keranjang->top;
        keranjang->top = newNode;
        keranjang->count++;
    }
}

item* popKeranjang(Keranjang* keranjang) {
    if (keranjang->top == NULL) {
        return NULL; // Stack kosong
    }

    NodeKeranjang* temp = keranjang->top;
    item* barang = temp->barang;
    keranjang->top = temp->next;
    free(temp);
    keranjang->count--;
    return barang;
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

double getTotalHargaKeranjang(const Keranjang* keranjang) {
    double total = 0.0;
    NodeKeranjang* current = keranjang->top;
    while (current != NULL) {
        total += current->barang->harga * current->barang->jumlah;
        current = current->next;
    }
    return total;
}

void clearKeranjang(Keranjang* keranjang) {
    while (!isKeranjangEmpty(keranjang)) {
        item* barang = popKeranjang(keranjang);
        free(barang); 
    }
}

void displayKeranjang(const Keranjang* keranjang) {
    if (isKeranjangEmpty(keranjang)) {
        printf("Keranjang kosong.\n");
        return;
    }

    printf("Isi Keranjang:\n");
    NodeKeranjang* current = keranjang->top;
    int index = 1;
    while (current != NULL) {
        item* barang = current->barang;
        printf("%d. %s (Jumlah: %d, Harga: %.2f)\n", index++, barang->nama, barang->jumlah, barang->harga);
        current = current->next;
    }
    printf("Total: %.2f\n", getTotalHargaKeranjang(keranjang));
}