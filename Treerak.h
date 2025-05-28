#include <stdio.h>
#include <stdlib.h>
#define BOOLEAN
#ifndef TREERAK_H
#define TREERAK_H
#define MAX_NAMA_RAK 50
#include "items.h"

typedef struct Treerak {
    char type[50];
    Treerak* firstson;
    Treerak* nextbrother;
} Treerak;

// Node untuk Non-Binary Tree Rak
typedef struct NodeRak {
    char namaRak[MAX_NAMA_RAK];
    Listitem* daftarBarangDiRak; // Barang yang ada di rak ini (linked list)
    struct NodeRak** subRak;              // Array pointer ke anak-anak (sub-rak)
    int jumlahSubRak;
    int kapasitasSubRak;                  // Untuk mengelola ukuran dinamis array subRak
    struct NodeRak* parent;               // Pointer ke rak induk
    double jarakDariEntry;                // Untuk menentukan rak terdekat
} NodeRak;

// Struktur untuk Tree Rak itu sendiri (menyimpan root)
typedef struct {
    NodeRak* root;
} TreeRak;

// Fungsi untuk membuat NodeRak baru
NodeRak* CreateNodeRak(const char* nama, double jarak);

// Fungsi untuk menambah sub-rak ke sebuah NodeRak
void tambahSubRak(NodeRak* parent, NodeRak* child);

// Fungsi untuk menambah item ke daftarBarangDiRak pada NodeRak
void tambahItem(NodeRak* rak, item* barang, int stok);

// Fungsi untuk mencari item di rak tertentu dan mengurangi stoknya
ItemNode* ambilItem(NodeRak* rak, const char* idBarang, int jumlah);

// Fungsi untuk mencari NodeRak berdasarkan nama (contoh traversal)
NodeRak* findNodeRak(NodeRak* root, const char* namaRak);

// Fungsi untuk menampilkan struktur rak (misalnya, secara rekursif)
void displayTreeRak(const NodeRak* node, int level);

// Fungsi untuk membersihkan memori TreeRak
void freeTreeRak(NodeRak* node);


#endif