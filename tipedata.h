// Struct dasar untuk Produk

// File: supermarket.h (BARU - The One Header to Rule Them All)
#ifndef tipedata_H
#define tipedata_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BOOLEAN.H"
#define TRUE 1
#define FALSE 0
#define Nil NULL


typedef struct {
    char idProduk[20];
    char nama[100];
    float harga;
    int stok;
} Produk;

// Struct untuk Node AVL Tree
typedef struct RakBTree {
    Produk info;
    struct RakBTree *left;
    struct RakBTree *right;
    int height;
} RakBTree;

// Struct untuk Keranjang Belanja (Linked List)
typedef struct KeranjangNode {
    Produk infoProduk;
    int kuantitas;
    struct KeranjangNode *next;
} KeranjangNode;

typedef struct {
    KeranjangNode* head;
    int jumlahItemUnik;
    double totalHarga;
} KeranjangBelanja;

// Struct untuk Pelanggan (yang akan masuk antrian)
typedef struct {
    char nama[50];
    KeranjangBelanja* keranjang;
} Pelanggan;

// Struct untuk Antrian Kasir (Queue)
typedef struct AntrianNode {
    Pelanggan dataPelanggan;
    struct AntrianNode* next;
} AntrianNode;

typedef struct {
    AntrianNode* head;
    AntrianNode* tail;
    int jumlahPelanggan;
} AntrianKasir;

// Struct untuk Rak Tumpukan (Stack)
typedef struct NodeTumpukan {
    Produk info;
    struct NodeTumpukan* next;
} NodeTumpukan;

typedef struct {
    NodeTumpukan* top;
    int count;
    char namaRak[50];
} RakTumpukan;

// Struct untuk Peta Supermarket (Non-Binary Tree)
typedef struct ItemNode {
    Produk dataProduk;
    int stock;
    struct ItemNode *next;
} ItemNode;
typedef ItemNode* AddressItemNode;

typedef struct {
    AddressItemNode head;
    AddressItemNode tail;
} Listitem;

typedef struct {
    char* namaLokasi;
    int jarakDariParent;
    Listitem daftarItem;
} RakData;

#endif