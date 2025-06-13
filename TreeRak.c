#include "TreeRak.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Pastikan ini ada untuk strcmp, strdup
#define MAX_PATH 100 // Pastikan definisi ini ada

// ===================================================================
//  FUNGSI HELPER (PRIVATE) UNTUK LAYOUT RAK (NON-BINARY TREE)
// ===================================================================

// Fungsi untuk membuat data RakData baru
// Revitalisasi: Memastikan CreateListItem dipanggil tanpa argumen type
RakData* buatDataRak(const char* nama, int jarak) {
    RakData* dataBaru = (RakData*)malloc(sizeof(RakData));
    if (dataBaru == NULL) {
        fprintf(stderr, "Error: Gagal alokasi memori untuk RakData.\n");
        return NULL;
    }
    dataBaru->namaLokasi = strdup(nama); // Duplikasi string nama lokasi
    if (dataBaru->namaLokasi == NULL) {
        fprintf(stderr, "Error: Gagal alokasi memori untuk namaLokasi.\n");
        free(dataBaru);
        return NULL;
    }
    dataBaru->jarakDariParent = jarak;
    CreateListItem(&(dataBaru->daftarItem)); // Memanggil CreateListItem tanpa argumen type
    return dataBaru;
}

// Fungsi untuk membebaskan memori RakData
void freeRakData(InfoType data) {
    RakData* rak = (RakData*)data;
    if (rak != NULL) {
        free(rak->namaLokasi); // Bebaskan memori untuk nama lokasi
        // TODO: Anda mungkin juga perlu membebaskan item dalam daftarItem jika dialokasikan secara dinamis
        // For now, assuming ItemNode is freed when Listitem is destroyed or items are removed.
    }
}

// Fungsi rekursif untuk mencari node rak berdasarkan nama
TreeNode* cariRakRecursive(TreeNode* node, const char* namaRak) {
    if (node == NULL) return NULL;
    RakData* data = (RakData*)node->data;
    if (strcmp(data->namaLokasi, namaRak) == 0) return node;
    TreeNode* foundNode = cariRakRecursive(node->firstChild, namaRak);
    if (foundNode != NULL) return foundNode;
    return cariRakRecursive(node->nextSibling, namaRak);
}

// Fungsi rekursif untuk mencetak layout tree dengan konektor ASCII
void printTreeRecursive(TreeNode* node, char* prefix, boolean isLast, int totalJarak) {
    if (node == NULL) return;

    printf("%s", prefix);

    RakData* data = (RakData*)node->data;
    if (strcmp(data->namaLokasi, "Pintu Masuk") == 0) {
        printf("[+] %s\n", data->namaLokasi);
    } else {
        printf(isLast ? "\\-- " : "+-- ");
        printf("%s (Jarak: %d m, Total: %d m)\n", data->namaLokasi, data->jarakDariParent, totalJarak);
    }

    // Menampilkan daftar item di rak ini
    // REVISI: Menggunakan PrintListItem yang sudah dimodifikasi untuk Produk
    AddressItemNode itemNode = data->daftarItem.head;
    while(itemNode != Nil) {
        printf("%s%s    - %s (Stok: %d)\n", prefix, isLast ? "     " : "|    ", itemNode->dataProduk.nama, itemNode->stock); // Mengakses dataProduk.nama
        itemNode = itemNode->next;
    }

    char newPrefix[MAX_PATH];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, isLast ? "     " : "|    "); // Menambahkan awalan ASCII yang sesuai untuk level berikutnya

    TreeNode* child = node->firstChild;
    while (child != NULL) {
        boolean isLastChild = (child->nextSibling == NULL);
        RakData* childData = (RakData*)child->data; // Cast ke RakData untuk akses jarakDariParent
        printTreeRecursive(child, newPrefix, isLastChild, totalJarak + childData->jarakDariParent);
        child = child->nextSibling;
    }
}

// Fungsi rekursif untuk mengatur pointer parent (tidak berubah)
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

// Fungsi untuk membuat layout supermarket (Non-Binary Tree)
TreeNode* buatLayoutSupermarket() {
    printf("Membangun layout supermarket...\n");
    TreeNode* root = TCreateNode(buatDataRak("Pintu Masuk", 0));
    if (root != NULL) root->parent = NULL;

    // Rak utama
    TreeNode* rakMakanan = TCreateNode(buatDataRak("Rak Makanan", 5));
    TaddChild(root, rakMakanan);

    TreeNode* rakMinuman = TCreateNode(buatDataRak("Rak Minuman", 5));
    TaddChild(root, rakMinuman);

    TreeNode* rakKecantikan = TCreateNode(buatDataRak("Rak Kecantikan", 5));
    TaddChild(root, rakKecantikan);

    TreeNode* rakBumbuDapur = TCreateNode(buatDataRak("Rak Bumbu Dapur", 5));
    TaddChild(root, rakBumbuDapur);

    TreeNode* rakBeautyProduct = TCreateNode(buatDataRak("Rak Beauty & Product", 5));
    TaddChild(root, rakBeautyProduct);

    // Sub-rak Rak Makanan
    TreeNode* makananRingan = TCreateNode(buatDataRak("Makanan Ringan", 2));
    TreeNode* makananPokok = TCreateNode(buatDataRak("Makanan Pokok", 2));
    TaddChild(rakMakanan, makananRingan);
    TaddChild(rakMakanan, makananPokok);

    // Sub-rak Rak Minuman
    TreeNode* airPutih = TCreateNode(buatDataRak("Air Putih", 2));
    TreeNode* jus = TCreateNode(buatDataRak("Jus", 2));
    TaddChild(rakMinuman, airPutih);
    TaddChild(rakMinuman, jus);

    // Sub-rak Rak Bumbu Dapur
    TreeNode* kecap = TCreateNode(buatDataRak("Kecap", 2));
    TreeNode* saos = TCreateNode(buatDataRak("Saos", 2));
    TaddChild(rakBumbuDapur, kecap);
    TaddChild(rakBumbuDapur, saos);

    // Sub-rak Rak Beauty & Product
    TreeNode* lipstik = TCreateNode(buatDataRak("Lipstik", 2));
    TreeNode* bedak = TCreateNode(buatDataRak("Bedak", 2));
    TaddChild(rakBeautyProduct, lipstik);
    TaddChild(rakBeautyProduct, bedak);

    // Item dalam Makanan Ringan (contoh: ini adalah sub-rak untuk merek atau jenis tertentu)
    // PENTING: Node-node ini BUKAN PRODUK. Mereka adalah LOKASI/KATEGORI.
    // Produk itu sendiri akan ditambahkan ke Listitem dalam RakData ini.
    TreeNode* chitatoRak = TCreateNode(buatDataRak("Chitato Area", 1)); // Rak khusus chitato
    TreeNode* momogiRak = TCreateNode(buatDataRak("Momogi Area", 1));   // Rak khusus momogi
    TaddChild(makananRingan, chitatoRak);
    TaddChild(makananRingan, momogiRak);

    // Sub-rak untuk varian rasa (tetap sebagai lokasi, bukan produk)
    TaddChild(chitatoRak, TCreateNode(buatDataRak("Chitato Rasa Keju", 1)));
    TaddChild(chitatoRak, TCreateNode(buatDataRak("Chitato Rasa Sapi Panggang", 1)));
    TaddChild(momogiRak, TCreateNode(buatDataRak("Momogi Rasa Jagung Bakar", 1)));

    // Item dalam Air Putih
    TaddChild(airPutih, TCreateNode(buatDataRak("Rak Vit", 1)));
    TaddChild(airPutih, TCreateNode(buatDataRak("Rak Aqua", 1)));
    TaddChild(airPutih, TCreateNode(buatDataRak("Rak Le Mineral", 1)));

    // Item dalam Jus
    TaddChild(jus, TCreateNode(buatDataRak("Rak Buavita", 1)));

    // Item dalam Kecap
    TaddChild(kecap, TCreateNode(buatDataRak("Rak Kecap ABC", 1)));
    TaddChild(kecap, TCreateNode(buatDataRak("Rak Kecap Bango", 1)));
    TaddChild(kecap, TCreateNode(buatDataRak("Rak Kecap Rania", 1)));

    // Item dalam Saos
    TaddChild(saos, TCreateNode(buatDataRak("Rak Saos Indofood", 1)));
    TaddChild(saos, TCreateNode(buatDataRak("Rak Saos Belibis", 1)));
    TaddChild(saos, TCreateNode(buatDataRak("Rak Saos Sasa", 1)));

    // Item dalam Lipstik
    TaddChild(lipstik, TCreateNode(buatDataRak("Rak Make Over Lipstik", 1)));
    TaddChild(lipstik, TCreateNode(buatDataRak("Rak Implora Lipstik", 1)));
    TaddChild(lipstik, TCreateNode(buatDataRak("Rak Maybelline Lipstik", 1)));

    // Item dalam Bedak
    TaddChild(bedak, TCreateNode(buatDataRak("Rak Wardah Bedak", 1)));
    TaddChild(bedak, TCreateNode(buatDataRak("Rak Luxcrime Bedak", 1)));
    TaddChild(bedak, TCreateNode(buatDataRak("Rak Emma Bedak", 1)));

    // Tambahan: Subrak wardah di rakKecantikan (jika ini kategori merek)
    TreeNode* wardahKecantikan = TCreateNode(buatDataRak("Wardah Produk", 2));
    TaddChild(rakKecantikan, wardahKecantikan);
    TaddChild(wardahKecantikan, TCreateNode(buatDataRak("Wardah Lipstik", 1)));
    TaddChild(wardahKecantikan, TCreateNode(buatDataRak("Wardah Bedak", 1)));


    setParentPointersRecursive(root);
    printf("Layout supermarket berhasil dibangun.\n");
    return root;
}

// Fungsi untuk menambahkan item (Produk) ke Listitem di dalam RakData dari rak tujuan
// Revitalisasi: Menerima Produk, bukan 'item' lama
void tambahItemKeRak(TreeNode* rakTujuan, Produk produk, int stock) {
    if (rakTujuan == NULL) {
        printf("Error: Gagal menambahkan '%s' karena rak tujuan tidak ditemukan.\n", produk.nama);
        return;
    }
    RakData* dataRak = (RakData*)rakTujuan->data;
    // PENTING: Jika produk sudah ada di Listitem rak ini, Anda mungkin ingin mengupdate stoknya, bukan menambah node baru.
    // Untuk saat ini, kita akan selalu menambah baru. Logika update stok dapat ditambahkan di SearchItem/InsertLastItem jika perlu.
    InsertLastItem(&(dataRak->daftarItem), produk, stock);
    printf("Berhasil menambahkan %d '%s' (ID: %s) ke rak '%s'.\n", stock, produk.nama, produk.idProduk, dataRak->namaLokasi);
}

// Fungsi untuk mencari node rak berdasarkan nama rak
TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak) {
    if (root == NULL || namaRak == NULL) return NULL;
    return cariRakRecursive(root, namaRak);
}

// Fungsi untuk mencari rak yang berisi produk tertentu (berdasarkan idProduk)
// Revitalisasi: Menggunakan idProduk (string) untuk pencarian
TreeNode* cariRakDenganIdBarang(TreeNode* root, const char* idProduk) {
    if (root == NULL) return NULL;
    RakData* dataRak = (RakData*)root->data;
    // Gunakan SearchItem yang sudah dimodifikasi untuk mencari berdasarkan idProduk
    if (SearchItem(dataRak->daftarItem, (char*)idProduk) != Nil) { // Cast const char* to char* if SearchItem expects non-const
        return root; // Produk ditemukan di rak ini
    }
    // Lanjutkan pencarian di anak-anak dan saudara
    TreeNode* child = root->firstChild;
    while(child != NULL) {
        TreeNode* foundNode = cariRakDenganIdBarang(child, idProduk);
        if (foundNode != NULL) {
            return foundNode;
        }
        child = child->nextSibling;
    }
    return NULL; // Produk tidak ditemukan di tree ini
}

// Fungsi untuk mengambil item (Produk) dari Listitem di dalam RakData dari rak tujuan
// Revitalisasi: Menggunakan idProduk (string) untuk pengambilan
boolean ambilItemDariRak(TreeNode* rakTujuan, const char* idProduk, int jumlah, RakBTree *globalProductAVLTree) {
    if (rakTujuan == NULL) return false;
    RakData* dataRak = (RakData*)rakTujuan->data;
    AddressItemNode itemNode = SearchItem(dataRak->daftarItem, (char*)idProduk); // Cari produk di list rak

    if (itemNode != Nil) {
        if (itemNode->stock >= jumlah) {
            itemNode->stock -= jumlah; // Kurangi stok di rak
            printf("Berhasil mengambil %d '%s' (ID: %s) dari '%s'. Sisa stok: %d\n",
                   jumlah, itemNode->dataProduk.nama, itemNode->dataProduk.idProduk, dataRak->namaLokasi, itemNode->stock);
            
            // Opsional: Perbarui stok global di AVL Tree produk jika ada konsep stok global
            // RakBTree *globalProductNode = searchProduk(globalProductAVLTree, (char*)idProduk);
            // if (globalProductNode) {
            //     globalProductNode->info.stok -= jumlah; // Ini akan mengurangi stok di AVL Tree
            // }

            return true;
        } else {
            printf("Error: Stok '%s' (ID: %s) di '%s' tidak mencukupi. Tersedia: %d, Diminta: %d.\n",
                   itemNode->dataProduk.nama, itemNode->dataProduk.idProduk, dataRak->namaLokasi, itemNode->stock, jumlah);
            return false;
        }
    }
    printf("Error: Produk dengan ID '%s' tidak ditemukan di rak '%s'.\n", idProduk, dataRak->namaLokasi);
    return false;
}

// Fungsi publik untuk menampilkan peta supermarket (tidak banyak berubah)
void tampilkanPetaSupermarket(TreeNode* root) {
    printf("\n================= PETA SUPERMARKET ================\n");
    if (root == NULL) {
        printf("Peta tidak tersedia.\n");
    } else {
        printTreeRecursive(root, "", true, 0);
    }
    printf("=================================================\n\n");
}

// Fungsi untuk menampilkan jarak dari Pintu Masuk ke rak tujuan (tidak banyak berubah)
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

// Fungsi untuk membebaskan memori layout supermarket (tidak banyak berubah)
void bebaskanLayoutSupermarket(TreeNode* root) {
    Tfree(root, &freeRakData);
}

// Fungsi untuk mencari data item (Produk) di seluruh pohon layout rak
// Revitalisasi: Mengembalikan AddressItemNode yang berisi Produk
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idProdukCari) {
    if (root == NULL) return NULL;
    RakData* dataRak = (RakData*)root->data;
    AddressItemNode foundNode = SearchItem(dataRak->daftarItem, (char*)idProdukCari); // Cari di Listitem rak saat ini
    if (foundNode != NULL) return foundNode;
    
    // Cari di anak-anak
    TreeNode* child = root->firstChild;
    while (child != NULL) {
        AddressItemNode resultFromChild = findItemDataOnTree(child, idProdukCari);
        if (resultFromChild != NULL) return resultFromChild;
        child = child->nextSibling;
    }
    return NULL; // Tidak ditemukan
}