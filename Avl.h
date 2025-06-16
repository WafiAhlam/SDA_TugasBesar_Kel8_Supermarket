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

#endif 