#include "TreeRak.h" // Untuk layout supermarket (Non-Binary Tree)
#include "avl.h"     // Untuk manajemen produk (AVL Tree)
#include <stdio.h>
#include <string.h>

// Deklarasi global untuk AVL Tree produk
RakBTree *globalProductAVLTree = NULL; // Ini akan menyimpan semua produk

int main() {
    // --- 1. Inisialisasi AVL Tree Produk Global ---
    // Tambahkan beberapa produk ke AVL Tree
    Produk p1 = {"A001", "Sabun Mandi", 15000.0, 500};
    Produk p2 = {"B002", "Shampo Anti Ketombe", 25000.0, 300};
    Produk p3 = {"C003", "Pasta Gigi", 12000.0, 400};
    Produk p4 = {"A005", "Susu Full Cream", 28000.0, 250};
    Produk p5 = {"B001", "Kopi Hitam", 10000.0, 180};
    Produk p6 = {"C004", "Beras 5kg", 60000.0, 100};

    globalProductAVLTree = insertProduk(globalProductAVLTree, p1);
    globalProductAVLTree = insertProduk(globalProductAVLTree, p2);
    globalProductAVLTree = insertProduk(globalProductAVLTree, p3);
    globalProductAVLTree = insertProduk(globalProductAVLTree, p4);
    globalProductAVLTree = insertProduk(globalProductAVLTree, p5);
    globalProductAVLTree = insertProduk(globalProductAVLTree, p6);

    printf("--- Daftar Produk Global (dari AVL Tree) ---\n");
    inOrderProduk(globalProductAVLTree);
    printf("\n");

    // --- 2. Bangun Layout Supermarket (Non-Binary Tree) ---
    TreeNode* layoutSupermarketRoot = buatLayoutSupermarket();
    
    // --- 3. Tambahkan Stok Produk ke Rak Spesifik ---
    // Cari rak "Rak Beauty & Product"
    TreeNode* rakBeautyProduct = cariRakDenganNama(layoutSupermarketRoot, "Rak Beauty & Product");
    if (rakBeautyProduct) {
        // Ambil data produk dari AVL Tree global untuk ditambahkan ke rak
        RakBTree *sabunNode = searchProduk(globalProductAVLTree, "A001");
        if (sabunNode) {
            tambahItemKeRak(rakBeautyProduct, sabunNode->info, 20); // Tambahkan 20 sabun ke rak ini
        } else {
            printf("Produk A001 tidak ditemukan di AVL Tree global.\n");
        }

        RakBTree *shampoNode = searchProduk(globalProductAVLTree, "B002");
        if (shampoNode) {
            tambahItemKeRak(rakBeautyProduct, shampoNode->info, 15); // Tambahkan 15 shampo
        } else {
            printf("Produk B002 tidak ditemukan di AVL Tree global.\n");
        }
    }

    // Cari rak "Makanan Ringan"
    TreeNode* makananRinganRak = cariRakDenganNama(layoutSupermarketRoot, "Makanan Ringan");
    if (makananRinganRak) {
        RakBTree *kopiNode = searchProduk(globalProductAVLTree, "B001");
        if (kopiNode) {
            tambahItemKeRak(makananRinganRak, kopiNode->info, 30); // Tambahkan 30 kopi
        } else {
            printf("Produk B001 tidak ditemukan di AVL Tree global.\n");
        }
    }

    printf("\n--- Peta Supermarket dengan Barang di Rak ---\n");
    tampilkanPetaSupermarket(layoutSupermarketRoot);

    // --- 4. Pelanggan Mengambil Barang ---
    printf("\n--- Pelanggan Mengambil Barang ---\n");
    TreeNode* rakTujuanSabun = cariRakDenganIdBarang(layoutSupermarketRoot, "A001");
    if (rakTujuanSabun) {
        ambilItemDariRak(rakTujuanSabun, "A001", 5, globalProductAVLTree); // Ambil 5 sabun
    }

    TreeNode* rakTujuanKopi = cariRakDenganIdBarang(layoutSupermarketRoot, "B001");
    if (rakTujuanKopi) {
        ambilItemDariRak(rakTujuanKopi, "B001", 10, globalProductAVLTree); // Ambil 10 kopi
    }
    
    // Coba ambil barang yang tidak ada atau stok kurang
    ambilItemDariRak(rakTujuanSabun, "A001", 100, globalProductAVLTree); // Coba ambil lebih dari stok
    ambilItemDariRak(rakTujuanSabun, "Z999", 1, globalProductAVLTree); // Coba ambil produk tidak ada

    printf("\n--- Peta Supermarket Setelah Pengambilan Barang ---\n");
    tampilkanPetaSupermarket(layoutSupermarketRoot);


    // --- 5. Bebaskan Memori ---
    bebaskanLayoutSupermarket(layoutSupermarketRoot);
    deleteTree(globalProductAVLTree); // Bebaskan memori AVL Tree
    globalProductAVLTree = NULL;

    return 0;
}