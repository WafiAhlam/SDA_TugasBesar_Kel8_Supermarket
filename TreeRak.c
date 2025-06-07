#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeRak.h"

// ===================================================================
//  FUNGSI HELPER (PRIVATE)
//  Fungsi-fungsi ini hanya digunakan di dalam file ini.
// ===================================================================

/**
 * @brief Helper untuk membuat dan mengalokasikan memori untuk RakData.
 * Ini adalah "muatan" spesifik untuk setiap node di pohon kita.
 */
RakData* buatDataRak(const char* nama, int jarak) {
    // 1. Alokasikan memori untuk struct RakData
    RakData* dataBaru = (RakData*)malloc(sizeof(RakData));
    if (dataBaru == NULL) return NULL;

    // 2. Isi datanya
    dataBaru->namaLokasi = strdup(nama); // strdup untuk menyalin string dengan aman
    dataBaru->jarakDariParent = jarak;

    // 3. Panggil fungsi dari modul 'items' untuk menginisialisasi list item di rak ini
    CreateListItem(&(dataBaru->daftarItem), nama);

    return dataBaru;
}

/**
 * @brief Helper untuk membebaskan memori dari sebuah RakData.
 * Fungsi ini akan kita berikan ke Tfree() agar tahu cara membersihkan data kita.
 */
void freeRakData(InfoType data) {
    RakData* rak = (RakData*)data;
    if (rak != NULL) {
        free(rak->namaLokasi); // Bebaskan string nama yang di-strdup
        // Asumsi ada fungsi untuk mendealokasi semua node di list item
        // DeallocateAllItems(&rak->daftarItem); 
        // Karena struct Listitem tidak dialokasikan secara dinamis, kita tidak perlu free(rak).
    }
}

// Helper untuk traversal dan mencari rak berdasarkan nama.
TreeNode* cariRakRecursive(TreeNode* node, const char* namaRak) {
    if (node == NULL) {
        return NULL;
    }
    RakData* data = (RakData*)node->data;
    if (strcmp(data->namaLokasi, namaRak) == 0) {
        return node; // Ditemukan
    }
    // Cari di anak
    TreeNode* foundNode = cariRakRecursive(node->firstChild, namaRak);
    if (foundNode != NULL) {
        return foundNode;
    }
    // Cari di saudara
    return cariRakRecursive(node->nextSibling, namaRak);
}

// ===================================================================
//  IMPLEMENTASI FUNGSI DARI TREERAK.H
// ===================================================================

TreeNode* buatLayoutSupermarket() {
    printf("Membangun layout supermarket...\n");

    // --- Membuat Node Root (Pintu Masuk) ---
    RakData* dataPintuMasuk = buatDataRak("Pintu Masuk", 0);
    TreeNode* root = TCreateNode(dataPintuMasuk);
    if (root != NULL) root->parent = NULL;

    // --- Membuat Rak Level 1 ---
    TreeNode* rakSayuran = TCreateNode(buatDataRak("Rak Sayuran & Buah", 5));
    TaddChild(root, rakSayuran);

    TreeNode* rakDaging = TCreateNode(buatDataRak("Rak Daging & Ikan", 5));
    TaddChild(root, rakDaging);
    
    TreeNode* rakMinuman = TCreateNode(buatDataRak("Rak Minuman", 7));
    TaddChild(root, rakMinuman);

    // --- Membuat Rak Level 2 (Sub-rak) ---
    TreeNode* rakBuah = TCreateNode(buatDataRak("Sub-rak Buah", 2));
    TaddChild(rakSayuran, rakBuah);

    printf("Layout supermarket berhasil dibuat.\n");
    return root;
}


void tambahItemKeRak(TreeNode* rakTujuan, item barang, int stock) {
    if (rakTujuan == NULL) {
        printf("Error: Rak tujuan tidak valid.\n");
        return;
    }
    // 1. Ambil data spesifik rak dari node generik
    RakData* dataRak = (RakData*)rakTujuan->data;
    // 2. Panggil fungsi dari modul 'items' untuk menambahkan barang ke list
    InsertLastItem(&(dataRak->daftarItem), barang, stock);
}


TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak) {
    if (root == NULL || namaRak == NULL) return NULL;
    return cariRakRecursive(root, namaRak);
}


boolean ambilItemDariRak(TreeNode* root, const char* idBarang, int jumlah) {
    if (root == NULL) return false;

    // Cari di rak saat ini dulu
    RakData* dataRak = (RakData*)root->data;
    AddressItemNode itemNode = SearchItem(dataRak->daftarItem, idBarang);

    if (itemNode != Nil) { // Item ditemukan di rak ini
        if (itemNode->stock >= jumlah) {
            itemNode->stock -= jumlah;
            printf("Berhasil mengambil %d '%s' dari %s. Sisa stok: %d\n",
                   jumlah, itemNode->dataBarang.namabarang, dataRak->namaLokasi, itemNode->stock);
            return true;
        } else {
            printf("Error: Stok '%s' di %s tidak mencukupi (tersedia: %d, diminta: %d).\n",
                   itemNode->dataBarang.namabarang, dataRak->namaLokasi, itemNode->stock, jumlah);
            return false;
        }
    }

    // Jika tidak ada, lanjutkan pencarian ke anak dan saudara secara rekursif
    if (ambilItemDariRak(root->firstChild, idBarang, jumlah)) {
        return true;
    }
    return ambilItemDariRak(root->nextSibling, idBarang, jumlah);
}


void tampilkanPetaSupermarket(TreeNode* root) {
    // Implementasi detail untuk ini memerlukan fungsi rekursif dengan level indentasi
    // Ini adalah contoh sederhana
    printf("\n================ PETA SUPERMARKET ================\n");
    // (Implementasi detail untuk traversal dan printing bisa ditambahkan di sini)
    // Untuk saat ini, kita akan memberitahu pengguna bahwa fitur ini ada.
    printf("Fitur untuk menampilkan peta detail dengan item sedang dalam pengembangan.\n");
    printf("===============================================\n");
}


void cariRuteDanJarak(TreeNode* root, const char* namaAwal, const char* namaTujuan) {
    printf("\n--- Mencari Rute dari '%s' ke '%s' ---\n", namaAwal, namaTujuan);
    // (Logika pathfinding seperti mencari LCA dan menghitung jarak adalah kompleks
    // dan bisa menjadi fitur lanjutan yang diimplementasikan di sini)
    printf("Fitur pencarian rute sedang dalam pengembangan.\n");
}


void bebaskanLayoutSupermarket(TreeNode* root) {
    // Panggil fungsi free generik, berikan fungsi spesifik kita untuk membersihkan RakData
    Tfree(root, &freeRakData);
}
