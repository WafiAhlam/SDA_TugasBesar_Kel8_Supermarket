#ifndef SUPERMARKET_H
#define SUPERMARKET_H
#include "TreeRak.h" // Perlu definisi TreeNode

/**
 * @brief Fungsi utama untuk setup. 
 * Fungsi ini akan membangun layout pohon rak dan mengisinya dengan semua item awal.
 * Ini adalah satu-satunya fungsi yang perlu dipanggil dari main.c untuk persiapan.
 * * @return TreeNode* Pointer ke akar (root) dari pohon supermarket yang sudah lengkap.
 */
TreeNode* setupAndPopulateSupermarket();

#endif // SUPERMARKET_H
