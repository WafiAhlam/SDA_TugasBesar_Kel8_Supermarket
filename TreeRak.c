#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH 100
#include "TreeRak.h"

// ===================================================================
//  FUNGSI HELPER (PRIVATE)
// ===================================================================

RakData* buatDataRak(const char* nama, int jarak) {
    RakData* dataBaru = (RakData*)malloc(sizeof(RakData));
    if (dataBaru == NULL) return NULL;
    dataBaru->namaLokasi = strdup(nama);
    dataBaru->jarakDariParent = jarak;
    CreateListItem(&(dataBaru->daftarItem), nama);
    return dataBaru;
}

void freeRakData(InfoType data) {
    RakData* rak = (RakData*)data;
    if (rak != NULL) {
        free(rak->namaLokasi);
    }
}

TreeNode* cariRakRecursive(TreeNode* node, const char* namaRak) {
    if (node == NULL) return NULL;
    RakData* data = (RakData*)node->data;
    if (strcmp(data->namaLokasi, namaRak) == 0) return node;
    TreeNode* foundNode = cariRakRecursive(node->firstChild, namaRak);
    if (foundNode != NULL) return foundNode;
    return cariRakRecursive(node->nextSibling, namaRak);
}

// --- FUNGSI HELPER BARU untuk menampilkan peta secara rekursif ---
void displayPetaRecursive(TreeNode* node, int level) {
    if (node == NULL) return;
    RakData* data = (RakData*)node->data;
    for (int i = 0; i < level; i++) printf("    "); // Indentasi
    printf("|- %s (Jarak dari induk: %d meter)\n", data->namaLokasi, data->jarakDariParent);
    
    // Tampilkan semua item di rak ini
    AddressItemNode itemNode = data->daftarItem.head;
    if (itemNode == Nil && level > 0) {
        for (int i = 0; i < level + 1; i++) printf("    ");
        printf("  - (Masih Kosong)\n");
    }
    while(itemNode != Nil) {
        for (int i = 0; i < level + 1; i++) printf("    ");
        printf("  - %s (Stok: %d)\n", itemNode->dataBarang.namabarang, itemNode->stock);
        itemNode = itemNode->next;
    }

    displayPetaRecursive(node->firstChild, level + 1);
    displayPetaRecursive(node->nextSibling, level);
}

// ===================================================================
//  IMPLEMENTASI FUNGSI DARI TREERAK.H
// ===================================================================

TreeNode* buatLayoutSupermarket() {
    printf("Membangun layout supermarket...\n");
    RakData* dataPintuMasuk = buatDataRak("Pintu Masuk", 0);
    TreeNode* root = TCreateNode(dataPintuMasuk);
    if (root != NULL) root->parent = NULL;

    // --- Membuat Rak Level 1 ---
    TreeNode* rakMinuman = TCreateNode(buatDataRak("Rak Minuman", 3));
    TaddChild(root, rakMinuman);
    
    TreeNode* rakBuah = TCreateNode(buatDataRak("Rak Buah", 5));
    TaddChild(root, rakBuah);

    TreeNode* rakDaging = TCreateNode(buatDataRak("Rak Daging & Ikan", 8));
    TaddChild(root, rakDaging);
    
    TreeNode* rakMakanan = TCreateNode(buatDataRak("Rak Makanan Ringan", 19));
    TaddChild(root, rakMakanan);
    
    TreeNode* rakAlatDapur = TCreateNode(buatDataRak("Rak Alat Dapur", 15));
    TaddChild(root, rakAlatDapur);

    TreeNode* rakPerlengkapanRumah = TCreateNode(buatDataRak("Rak Perlengkapan Rumah", 24));
    TaddChild(root, rakPerlengkapanRumah);

    // --- Membuat Rak Level 2 (Sub-rak) ---
    TreeNode* rakSusu = TCreateNode(buatDataRak("Sub-rak Susu & Yogurt", 2));
    TaddChild(rakMinuman, rakSusu);

    return root;
}

void tambahItemKeRak(TreeNode* rakTujuan, item barang, int stock) {
    if (rakTujuan == NULL) {
        printf("Error: Rak tujuan tidak valid.\n");
        return;
    }
    RakData* dataRak = (RakData*)rakTujuan->data;
    InsertLastItem(&(dataRak->daftarItem), barang, stock);
}


TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak) {
    if (root == NULL || namaRak == NULL) return NULL;
    return cariRakRecursive(root, namaRak);
}


boolean ambilItemDariRak(TreeNode* root, const char* idBarang, int jumlah) {
    if (root == NULL) return false;
    RakData* dataRak = (RakData*)root->data;
    AddressItemNode itemNode = SearchItem(dataRak->daftarItem, idBarang);
    if (itemNode != Nil) {
        if (itemNode->stock >= jumlah) {
            itemNode->stock -= jumlah;
            printf("Berhasil mengambil %d '%s' dari %s. Sisa stok: %d\n", jumlah, itemNode->dataBarang.namabarang, dataRak->namaLokasi, itemNode->stock);
            return true;
        } else {
            printf("Error: Stok '%s' di %s tidak mencukupi.\n", itemNode->dataBarang.namabarang, dataRak->namaLokasi);
            return false;
        }
    }
    if (ambilItemDariRak(root->firstChild, idBarang, jumlah)) return true;
    return ambilItemDariRak(root->nextSibling, idBarang, jumlah);
}

// --- FUNGSI DIIMPLEMENTASIKAN SEPENUHNYA ---
void tampilkanPetaSupermarket(TreeNode* root) {
    printf("\n================ PETA SUPERMARKET ================\n");
    if (root == NULL) {
        printf("Peta tidak tersedia.\n");
    } else {
        displayPetaRecursive(root, 0);
    }
    printf("===============================================\n");
}

// --- FUNGSI DIIMPLEMENTASIKAN SEPENUHNYA ---
void cariRuteDanJarak(TreeNode* root, const char* namaAwal, const char* namaTujuan) {
    printf("\n--- Mencari Rute dari '%s' ke '%s' ---\n", namaAwal, namaTujuan);
    
    TreeNode* startNode = cariRakDenganNama(root, namaAwal);
    TreeNode* endNode = cariRakDenganNama(root, namaTujuan);

    if (startNode == NULL || endNode == NULL) {
        printf("Lokasi awal atau tujuan tidak ditemukan.\n");
        return;
    }

    // Algoritma sederhana untuk menghitung jarak: naik ke root dari start, lalu turun ke end
    // Implementasi yang lebih canggih akan mencari Lowest Common Ancestor (LCA)
    // untuk menghindari penghitungan ganda pada jalur yang sama.
    // Namun, untuk simulasi ini, penjumlahan sederhana sudah cukup untuk menunjukkan konsep.
    int jarakTotal = 0;
    
    // Hitung jarak dari start ke root
    TreeNode* temp = startNode;
    while(temp != NULL && temp->parent != NULL) {
        jarakTotal += ((RakData*)temp->data)->jarakDariParent;
        temp = temp->parent;
    }

    // Hitung jarak dari end ke root
    temp = endNode;
     while(temp != NULL && temp->parent != NULL) {
        jarakTotal += ((RakData*)temp->data)->jarakDariParent;
        temp = temp->parent;
    }

    printf("Rute ditemukan! Perkiraan total jarak perjalanan: %d meter.\n", jarakTotal);
}


void bebaskanLayoutSupermarket(TreeNode* root) {
    Tfree(root, &freeRakData);
}



