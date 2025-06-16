#ifndef TREERAK_H
#define TREERAK_H
#include "tipedata.h"
#include "items.h" // items.h sekarang seharusnya meng-include avl.h untuk definisi Produk
#include "NonBinaryTree.h" // Untuk definisi TreeNode, TCreateNode, TaddChild, dll.
// #define MAXPATH 100 // Lebih baik didefinisikan di .c file atau di header utilitas umum jika diperlukan

// Struktur untuk menyimpan data per Rak (node di Non-Binary Tree Layout)
/*typedef struct {
    char* namaLokasi;       // Nama lokasi rak (misal: "Rak Makanan", "Rak Buah")
    int jarakDariParent;    // Jarak dari rak induknya
    Listitem daftarItem;    // Linked List dari Produk yang ada di rak ini beserta stoknya
} RakData;
*/
// --- DEKLARASI FUNGSI-FITUR LAYOUT SUPERMARKET (NON-BINARY TREE) ---

/*
IS: Memori heap tersedia untuk alokasi.
FS: Sebuah struktur Non-Binary Tree yang merepresentasikan peta/layout supermarket telah dibuat dan diinisialisasi. Pointer ke root tree ("Pintu Masuk") dikembalikan.

Creator: Wafi Ahlam Rizqulloh
*/
TreeNode* buatLayoutSupermarket();

/*
IS: root adalah pointer ke root dari layout supermarket.
FS: Struktur visual dari peta supermarket telah tercetak ke layar. State dari tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void tampilkanPetaSupermarket(TreeNode* root);

/*
IS: root adalah pointer ke root dari layout. namaAwal dan namaTujuan adalah nama lokasi yang ada di dalam tree.
FS: Rute dan total jarak antara lokasi awal dan tujuan tercetak di layar. State dari tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void cariRuteDanJarak(TreeNode* root, const char* namaAwal, const char* namaTujuan);

/*
IS: rakTujuan adalah pointer ke node rak yang valid. produk dan stock terdefinisi.
FS: Stok produk pada 'Listitem' di dalam rakTujuan telah bertambah. Jika produk belum ada di rak tersebut, sebuah node item baru akan dibuat.

Creator: Wafi Ahlam Rizqulloh
*/
void tambahItemKeRak(TreeNode* rakTujuan, Produk produk, int stock);

/*
IS: root adalah pointer ke root dari layout. namaRak adalah nama lokasi yang akan dicari.
FS: Jika ditemukan, mengembalikan pointer ke TreeNode yang memiliki nama lokasi yang cocok. Jika tidak, mengembalikan NULL. State dari tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak);

/*
IS: rakTujuan adalah pointer ke node rak yang valid. idProduk dan jumlah terdefinisi.
FS: Jika produk ada di rak tujuan dan stoknya mencukupi, maka stok produk di dalam 'Listitem' rak tersebut telah berkurang sebanyak 'jumlah' dan fungsi mengembalikan TRUE. Jika tidak, state tidak berubah dan fungsi mengembalikan FALSE.

Creator: Wafi Ahlam Rizqulloh
*/
boolean ambilItemDariRak(TreeNode* rakTujuan, const char* idProduk, int jumlah, RakBTree *globalProductAVLTree);

/*
IS: root adalah pointer ke root dari layout supermarket yang telah dibuat.
FS: Semua node di dalam tree layout beserta data di dalamnya (RakData dan Listitem) telah dibebaskan dari memori.

Creator: Wafi Ahlam Rizqulloh
*/
void bebaskanLayoutSupermarket(TreeNode* root);

/*
IS: root adalah pointer ke root dari layout. namaTujuan adalah nama lokasi tujuan.
FS: Jarak total dari "Pintu Masuk" (root) ke lokasi tujuan telah dihitung dan ditampilkan di layar. State dari tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void tampilkanJarakDariEntry(TreeNode* root, const char* namaTujuan);

/*
IS: root adalah pointer ke root dari layout. idProdukCari adalah ID produk yang dicari.
FS: Jika ditemukan, mengembalikan pointer (AddressItemNode) ke data item yang ada di salah satu rak. Jika tidak, mengembalikan NULL. State dari tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idProduk);

/*
IS: root adalah pointer ke root dari layout. idProduk adalah ID produk yang dicari.
FS: Jika ditemukan, mengembalikan pointer ke TreeNode (rak) yang berisi produk dengan ID tersebut. Jika tidak, mengembalikan NULL. State dari tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
TreeNode* cariRakDenganIdBarang(TreeNode* root, const char* idProduk);

/*
IS: Tree telah dibangun dengan pointer firstChild dan nextSibling. Pointer parent mungkin belum di-set.
FS: Setiap node dalam tree (kecuali root) memiliki pointer 'parent' yang menunjuk ke node induknya dengan benar.

Creator: Wafi Ahlam Rizqulloh
*/
void setParentPointersRecursive(TreeNode* node);

/*
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
void bebaskanLayoutSupermarket(TreeNode* root);
*/

#endif 