#include <stdio.h>
#include <stdlib.h>
#define BOOLEAN
#ifndef TREERAK_H
#define TREERAK_H
#define MAX_NAMA_RAK 50
#include "items.h"
#include "NonBinaryTree.h"

/*
// Struktur untuk Tree Rak itu sendiri (menyimpan root)
typedef struct {
    NodeRak* root;
} TreeRak;
*/

typedef struct {
    char* namaLokasi;
    int jarakDariParent; // Jarak dalam meter dari parent node
    Listitem daftarItem;  // Setiap rak memiliki sebuah list item
} RakData;

// ===================================================================
//  DEKLARASI FUNGSI-FITUR SUPERMARKET ("MENU" UNTUK main.c)
// ===================================================================
TreeNode* buatLayoutSupermarket();
void tampilkanPetaSupermarket(TreeNode* root);
void FindRuteDanJarak(TreeNode* root, const char* namaAwal, const char* namaTujuan);
void tambahItemKeRak(TreeNode* rakTujuan, item barang, int stock);
TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak);
void bebaskanLayoutSupermarket(TreeNode* root);

#endif 