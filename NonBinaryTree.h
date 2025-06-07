#include <stdio.h>
#include <stdlib.h>
#ifndef NONBINARYTREE_H
#define NONBINARYTREE_h
#include <stdbool.h>

// -----------------------------------------------------------------------------
// Informasi tambahan mengenai tipe data univ dengan nantinya saat di cetak gunakan casting jika perlu
// KUNCI UTAMA: Menggunakan 'void*' untuk data generik.
// Fungsinya dapat menyimpan pointer ke TIPE DATA APAPUN 
// (struct RakData, int, char*, dll) di dalam pohon.
// -----------------------------------------------------------------------------
typedef void* InfoType;
typedef struct TreeNode {
    InfoType data; // Pointer generik untuk menyimpan data spesifik aplikasi
    struct TreeNode* firstChild;
    struct TreeNode* nextSibling; 
} TreeNode;

TreeNode* TCreateNode(InfoType data);
void TaddChild(TreeNode* parent, TreeNode* child);
bool TisEmpty(TreeNode* root);
TreeNode* Tsearch(TreeNode* root, InfoType dataToFind, int (*compare)(InfoType data1, InfoType data2));
int TgetNodeCount(TreeNode* root);
int TLeafCount(TreeNode* root);
int TDepth(TreeNode* root);
void TPreOrder(TreeNode* root, void (*visit)(TreeNode* node));
void Tfree(TreeNode* root, void (*freeData)(InfoType data));


#endif