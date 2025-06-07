#include "NonBinaryTree.h"
#include <stdlib.h>

// Membuat node pohon baru
TreeNode* TCreateNode(InfoType data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return NULL; // Gagal alokasi memori
    }
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Menambahkan node child sebagai anak dari parent
void TaddChild(TreeNode* parent, TreeNode* child) {
    if (parent == NULL || child == NULL) {
        return; // Tidak melakukan apa-apa jika parent atau child NULL
    }
    if (parent->firstChild == NULL) {
        parent->firstChild = child; // Menambahkan sebagai anak pertama
    } else {
        // Menemukan sibling terakhir
        TreeNode* current = parent->firstChild;
        while (current->nextSibling != NULL) {
            current = current->nextSibling;
        }
        current->nextSibling = child; // Menambahkan child sebagai sibling
    }
}

// Memeriksa apakah pohon kosong
bool TisEmpty(TreeNode* root) {
    return root == NULL;
}

// Mencari node dengan data tertentu menggunakan fungsi perbandingan
TreeNode* Tsearch(TreeNode* root, InfoType dataToFind, int (*compare)(InfoType data1, InfoType data2)) {
    if (root == NULL) {
        return NULL;
    }
    // Periksa node saat ini
    if (compare(root->data, dataToFind) == 0) {
        return root;
    }
    // Cari di anak-anak
    TreeNode* found = Tsearch(root->firstChild, dataToFind, compare);
    if (found != NULL) {
        return found;
    }
    // Cari di sibling
    return Tsearch(root->nextSibling, dataToFind, compare);
}

// Menghitung jumlah total node di pohon
int TgetNodeCount(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    // 1 untuk node saat ini
    int count = 1;
    // Iterasi melalui semua anak dan jumlahkan node mereka secara rekursif
    TreeNode* child = root->firstChild;
    while (child != NULL) {
        count += TgetNodeCount(child); // Panggil rekursif untuk setiap anak
        child = child->nextSibling;    // Pindah ke anak berikutnya
    }
    return count;
}

// Menghitung jumlah daun di pohon
int TLeafCount(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    // Jika tidak punya anak, ini adalah daun
    if (root->firstChild == NULL) {
        return 1 + TLeafCount(root->nextSibling);
    }
    // Jika punya anak, lanjutkan ke anak dan sibling
    return TLeafCount(root->firstChild) + TLeafCount(root->nextSibling);
}

// Mendapatkan kedalaman/tinggi pohon
int TDepth(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    // Cari kedalaman maksimum dari anak-anak
    int maxChildDepth = 0;
    TreeNode* current = root->firstChild;
    while (current != NULL) {
        int childDepth = TDepth(current);
        if (childDepth > maxChildDepth) {
            maxChildDepth = childDepth;
        }
        current = current->nextSibling;
    }
    return 1 + maxChildDepth;
}

// Menjalankan fungsi visit pada setiap node secara PreOrder
void TPreOrder(TreeNode* root, void (*visit)(TreeNode* node)) {
    if (root == NULL) {
        return;
    }
    // Kunjungi node saat ini
    visit(root);
    // Kunjungi anak-anak
    TPreOrder(root->firstChild, visit);
    // Kunjungi sibling
    TPreOrder(root->nextSibling, visit);
}

// Membebaskan memori pohon
void Tfree(TreeNode* root, void (*freeData)(InfoType data)) {
    if (root == NULL) {
        return;
    }
    // Bebaskan anak-anak
    Tfree(root->firstChild, freeData);
    // Bebaskan sibling
    Tfree(root->nextSibling, freeData);

    if (freeData != NULL) {
        freeData(root->data);
    }
    free(root);
}