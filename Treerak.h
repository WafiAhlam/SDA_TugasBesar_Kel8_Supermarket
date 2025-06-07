#include <stdio.h>
#include <stdlib.h>
#ifndef TREERAK_H
#define TREERAK_H
#define MAX_NAMA_RAK 50
#include "items.h"

typedef struct Treerak {
    char type[50];
    struct Treerak* firstson;
    struct Treerak* nextbrother;
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
void TambahSubRak(NodeRak* parent, NodeRak* child);

// Fungsi untuk menambah item ke daftarBarangDiRak pada NodeRak
void TambahItem(NodeRak* rak, item* barang, int stok);

// Fungsi untuk mencari item di rak tertentu dan mengurangi stoknya
ItemNode* AmbilItem(NodeRak* rak, const char* idBarang, int jumlah);

// Fungsi untuk mencari NodeRak berdasarkan nama (contoh traversal)
NodeRak* FindNodeRak(NodeRak* root, const char* namaRak);

// Fungsi untuk menampilkan struktur rak (misalnya, secara rekursif)
void DisplayTreeRak(const NodeRak* node, int level);

// Fungsi untuk membersihkan memori TreeRak
void FreeTreeRak(NodeRak* node);


#endif
