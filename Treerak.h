#ifndef TREERAK_H
#define TREERAK_H

#include "items.h" // items.h sekarang seharusnya meng-include avl.h untuk definisi Produk
#include "NonBinaryTree.h" // Untuk definisi TreeNode, TCreateNode, TaddChild, dll.
// #define MAXPATH 100 // Lebih baik didefinisikan di .c file atau di header utilitas umum jika diperlukan

// Struktur untuk menyimpan data per Rak (node di Non-Binary Tree Layout)
typedef struct {
    char* namaLokasi;       // Nama lokasi rak (misal: "Rak Makanan", "Rak Buah")
    int jarakDariParent;    // Jarak dari rak induknya
    Listitem daftarItem;    // Linked List dari Produk yang ada di rak ini beserta stoknya
} RakData;

// --- DEKLARASI FUNGSI-FITUR LAYOUT SUPERMARKET (NON-BINARY TREE) ---

// Fungsi untuk membuat layout/pohon supermarket utama
// Mengembalikan pointer ke root TreeNode dari layout
TreeNode* buatLayoutSupermarket();

// Fungsi untuk menampilkan peta visual supermarket (struktur tree)
void tampilkanPetaSupermarket(TreeNode* root);

// Fungsi untuk mencari dan menampilkan rute serta jarak antara dua lokasi rak
// (Implementasi perlu ditambahkan di treerak.c jika belum ada)
void cariRuteDanJarak(TreeNode* root, const char* namaAwal, const char* namaTujuan);

// Fungsi untuk menambahkan produk ke Listitem di dalam RakData dari rak tujuan
// Menerima Produk (bukan 'item' lama) dan jumlah stok
void tambahItemKeRak(TreeNode* rakTujuan, Produk produk, int stock);

// Fungsi untuk mencari node rak (lokasi) berdasarkan namanya
// Mengembalikan pointer ke TreeNode jika ditemukan, NULL jika tidak
TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak);

// Fungsi untuk mengambil item (produk) dari Listitem di dalam RakData dari rak tujuan
// Parameter tambahan: root AVL Tree produk global untuk memperbarui stok total (opsional)
// Mengembalikan boolean: TRUE jika berhasil, FALSE jika gagal (stok kurang/barang tidak ada)
// PENTING: Anda perlu menyediakan parameter RakBTree *globalProductAVLTree saat memanggil ini di .c file
boolean ambilItemDariRak(TreeNode* rakTujuan, const char* idProduk, int jumlah, RakBTree *globalProductAVLTree);

// Fungsi untuk membebaskan semua memori yang dialokasikan untuk layout supermarket
void bebaskanLayoutSupermarket(TreeNode* root);

// Fungsi untuk menampilkan jarak dari Pintu Masuk ke lokasi rak tertentu
void tampilkanJarakDariEntry(TreeNode* root, const char* namaTujuan);

// Fungsi untuk mencari data produk (ItemNode yang berisi Produk) di seluruh pohon layout rak
// Mengembalikan AddressItemNode jika ditemukan, NULL jika tidak
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idProduk);

// Fungsi untuk mencari TreeNode (rak) yang berisi produk dengan ID tertentu
// Mengembalikan pointer ke TreeNode (rak) jika ditemukan, NULL jika tidak
TreeNode* cariRakDenganIdBarang(TreeNode* root, const char* idProduk);

// Fungsi rekursif untuk mengatur pointer parent pada setiap node tree
void setParentPointersRecursive(TreeNode* node);

#endif // TREERAK_H