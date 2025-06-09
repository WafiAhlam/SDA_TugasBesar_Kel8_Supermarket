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
    // REVISI: Menggunakan nama fungsi yang benar 'CreateListItem' dan menghapus output berlebih.
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

// REVISI TOTAL: Mengganti karakter Unicode dengan ASCII agar kompatibel di semua terminal.
void printTreeRecursive(TreeNode* node, char* prefix, boolean isLast, int totalJarak) {
    if (node == NULL) return;

    printf("%s", prefix);

    RakData* data = (RakData*)node->data;
    if (strcmp(data->namaLokasi, "Pintu Masuk") == 0) {
        // Menggunakan ASCII untuk root
        printf("[+] %s\n", data->namaLokasi);
    } else {
        // Menggunakan konektor ASCII: `+--` untuk cabang dan `\--` untuk cabang terakhir
        printf(isLast ? "\\-- " : "+-- ");
        printf("%s (Jarak: %d m, Total: %d m)\n", data->namaLokasi, data->jarakDariParent, totalJarak);
    }

    AddressItemNode itemNode = data->daftarItem.head;
    while(itemNode != Nil) {
        // Mencetak awalan lagi dengan konektor ASCII `|`
        printf("%s%s   - %s (Stok: %d)\n", prefix, isLast ? "    " : "|  ", itemNode->dataBarang.namabarang, itemNode->stock);
        itemNode = itemNode->next;
    }

    char newPrefix[MAX_PATH];
    strcpy(newPrefix, prefix);
    // Menambahkan awalan ASCII yang sesuai untuk level berikutnya
    strcat(newPrefix, isLast ? "    " : "|  ");

    TreeNode* child = node->firstChild;
    while (child != NULL) {
        boolean isLastChild = (child->nextSibling == NULL);
        RakData* childData = (RakData*)child->data;
        printTreeRecursive(child, newPrefix, isLastChild, totalJarak + childData->jarakDariParent);
        child = child->nextSibling;
    }
}

void setParentPointersRecursive(TreeNode* node) {
    if (node == NULL) return;
    
    TreeNode* child = node->firstChild;
    while (child != NULL) {
        child->parent = node;
        setParentPointersRecursive(child);
        child = child->nextSibling;
    }
}


// ===================================================================
//  IMPLEMENTASI FUNGSI DARI TREERAK.H
// ===================================================================

TreeNode* buatLayoutSupermarket() {
    printf("Membangun layout supermarket sesuai diagram...\n");
    TreeNode* root = TCreateNode(buatDataRak("Pintu Masuk", 0));
    if (root != NULL) root->parent = NULL;
    TreeNode* rakMinuman = TCreateNode(buatDataRak("Rak Minuman", 3));
    TaddChild(root, rakMinuman);
    TreeNode* rakBuah = TCreateNode(buatDataRak("Rak Buah", 5));
    TaddChild(root, rakBuah);
    TreeNode* rakDaging = TCreateNode(buatDataRak("Rak Daging", 5));
    TaddChild(rakMinuman, rakDaging);
    TreeNode* rakMakanan = TCreateNode(buatDataRak("Rak Makanan", 8));
    TaddChild(rakMinuman, rakMakanan);
    TreeNode* rakAlatDapur = TCreateNode(buatDataRak("Rak Alat Dapur", 10));
    TaddChild(rakMinuman, rakAlatDapur);
    TreeNode* rakSayuran = TCreateNode(buatDataRak("Rak Sayuran", 8));
    TaddChild(rakBuah, rakSayuran);
    TreeNode* rakPerlengkapanRumah = TCreateNode(buatDataRak("Rak Perlengkapan Rumah", 15));
    TaddChild(rakAlatDapur, rakPerlengkapanRumah);
    TaddChild(rakMinuman, TCreateNode(buatDataRak("Sub-rak Soda & Jus", 2)));
    TaddChild(rakDaging, TCreateNode(buatDataRak("Sub-rak Daging Merah", 1)));
    TaddChild(rakMakanan, TCreateNode(buatDataRak("Sub-rak Makanan Ringan", 1)));
    TaddChild(rakBuah, TCreateNode(buatDataRak("Sub-rak Buah Lokal", 2)));
    TaddChild(rakSayuran, TCreateNode(buatDataRak("Sub-rak Sayuran Daun", 1)));
    TaddChild(rakPerlengkapanRumah, TCreateNode(buatDataRak("Sub-rak Pembersih", 2)));

    setParentPointersRecursive(root);
    
    printf("Layout supermarket berhasil dibangun sesuai diagram.\n");
    return root;
}

void tambahItemKeRak(TreeNode* rakTujuan, item barang, int stock) {
    if (rakTujuan == NULL) {
        printf("Error: Gagal menambahkan '%s' karena rak tujuan tidak ditemukan.\n", barang.namabarang);
        return;
    }
    RakData* dataRak = (RakData*)rakTujuan->data;
    InsertLastItem(&(dataRak->daftarItem), barang, stock);
}

TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak) {
    if (root == NULL || namaRak == NULL) return NULL;
    return cariRakRecursive(root, namaRak);
}

TreeNode* cariRakDenganIdBarang(TreeNode* root, const char* idBarang) {
    if (root == NULL) return NULL;
    RakData* dataRak = (RakData*)root->data;
    if (SearchItem(dataRak->daftarItem, idBarang) != Nil) {
        return root;
    }
    TreeNode* child = root->firstChild;
    while(child != NULL) {
        TreeNode* foundNode = cariRakDenganIdBarang(child, idBarang);
        if (foundNode != NULL) {
            return foundNode;
        }
        child = child->nextSibling;
    }
    return NULL;
}

boolean ambilItemDariRak(TreeNode* rakTujuan, const char* idBarang, int jumlah) {
    if (rakTujuan == NULL) return false;
    RakData* dataRak = (RakData*)rakTujuan->data;
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
    return false;
}

// REVISI: Fungsi publik ini sekarang memanggil helper visual yang baru.
void tampilkanPetaSupermarket(TreeNode* root) {
    printf("\n================= PETA SUPERMARKET ================\n");
    if (root == NULL) {
        printf("Peta tidak tersedia.\n");
    } else {
        // Memulai proses penggambaran pohon dari root.
        printTreeRecursive(root, "", true, 0); 
    }
    printf("=================================================\n\n");
}

void tampilkanJarakDariEntry(TreeNode* root, const char* namaTujuan) {
    printf("\n--- Menghitung Jarak dari Pintu Masuk ke '%s' ---\n", namaTujuan);
    TreeNode* nodeTujuan = cariRakDenganNama(root, namaTujuan);
    if (nodeTujuan == NULL) {
        printf("Lokasi tujuan '%s' tidak ditemukan.\n", namaTujuan);
        return;
    }
    int jarakTotal = 0;
    TreeNode* temp = nodeTujuan;
    while(temp != NULL && temp->parent != NULL) {
        jarakTotal += ((RakData*)temp->data)->jarakDariParent;
        temp = temp->parent;
    }
    printf("Jarak dari Pintu Masuk ke '%s' adalah: %d meter.\n", namaTujuan, jarakTotal);
}

void bebaskanLayoutSupermarket(TreeNode* root) {
    Tfree(root, &freeRakData);
}

AddressItemNode findItemDataOnTree(TreeNode* root, const char* idBarang) {
    if (root == NULL) return NULL;
    RakData* dataRak = (RakData*)root->data;
    AddressItemNode foundNode = SearchItem(dataRak->daftarItem, idBarang);
    if (foundNode != NULL) return foundNode;
    TreeNode* child = root->firstChild;
    while (child != NULL) {
        AddressItemNode resultFromChild = findItemDataOnTree(child, idBarang);
        if (resultFromChild != NULL) return resultFromChild;
        child = child->nextSibling;
    }
    return NULL;
}
