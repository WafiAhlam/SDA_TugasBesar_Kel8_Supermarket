#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include dari kode yang sudah ada
#include "linked.h"
#include "Queue.h"
#include "Kasir.h"
#include "stack.h"
#include "Keranjang.h"
#include "pelanggan.h"
#include "TreeRak.h"

// Deklarasi fungsi helper
item buatContohItem(const char* id, const char* nama, double harga);
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idBarang);

int main() 
{
    // ==========================================================
    // SETUP SUPERMARKET (Kode ini sudah benar)
    // ==========================================================
    printf("Selamat Datang di Program Simulasi Supermarket!\n");
    TreeNode* rootSupermarket = buatLayoutSupermarket();
    if (rootSupermarket == NULL) {
        fprintf(stderr, "Gagal membuat layout supermarket. Program berhenti.\n");
        return 1;
    }

    printf("\n--- Mengisi Barang ke Rak ---\n");
    item itemApel = buatContohItem("APL01", "Apel Fuji Premium", 25000.0);
    item itemSirsak = buatContohItem("SI35K", "Sirsak Sulawesi", 18000.0);
    item itemSemangka = buatContohItem("SE45KA", "Semangka Depok", 34000.0);
    item itemSusu = buatContohItem("SUS01", "Susu UHT Coklat 1L", 18000.0);
    item itemYogurt = buatContohItem("YO84", "Yogurt Cimory", 19000.0);
    item itemSoda = buatContohItem("SO43", "Soda asal Indonesia", 5000.0);
    item itemDaging = buatContohItem("DAG01", "Daging Sapi Sirloin", 120000.0);
    item itemDagong = buatContohItem("DAG02", "Daging Wagyu A6", 5000000.0);

    TreeNode* rakBuah = cariRakDenganNama(rootSupermarket, "Sub-rak Buah");
    TreeNode* rakMinuman = cariRakDenganNama(rootSupermarket, "Rak Minuman");
    TreeNode* rakDaging = cariRakDenganNama(rootSupermarket, "Rak Daging & Ikan");

    if (rakBuah) tambahItemKeRak(rakBuah, itemApel, 100);
    if (rakBuah) tambahItemKeRak(rakBuah, itemSirsak, 30);
    if (rakBuah) tambahItemKeRak(rakBuah, itemSemangka, 23);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemYogurt, 38);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemSoda, 45);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemSusu, 80);
    if (rakDaging) tambahItemKeRak(rakDaging, itemDagong, 3);
    if (rakDaging) tambahItemKeRak(rakDaging, itemDaging, 30);
    
    tampilkanPetaSupermarket(rootSupermarket);

    // ====================================================================
    // SIMULASI UTAMA
    // ====================================================================
    Queue antrianPelanggan;
    CreateQueue(&antrianPelanggan);

    int pilih;
    do {
        printf("\n\n=== MENU UTAMA SIMULASI ===\n");
        printf("1. Pelanggan Baru Datang & Belanja\n");
        printf("2. Tampilkan Peta Supermarket\n");
        printf("3. Proses Pelanggan Berikutnya di Kasir\n");
        printf("4. Tampilkan Antrian Pelanggan\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: { // Pelanggan Baru Datang
                infotype pelangganBaru;
                
                printf("Masukkan nama pelanggan: ");
                scanf(" %[^\n]", pelangganBaru.nama);

                pelangganBaru.KPelanggan = createKeranjang();

                char tambahBarang;
                do {
                    char idBarang[MAX_ID_BARANG];
                    int jumlahAmbil;
                    printf("\nPelanggan '%s' sedang memilih barang.\n", pelangganBaru.nama);
                    printf("Masukkan ID barang: ");
                    scanf("%s", idBarang);
                    printf("Jumlah yang ingin diambil: ");
                    scanf("%d", &jumlahAmbil);

                    // --- LOGIKA DIPERBAIKI DAN DIBERSIHKAN ---
                    // 1. Coba ambil barang dari rak. Fungsi ini akan mengurangi stok.
                    if (ambilItemDariRak(rootSupermarket, idBarang, jumlahAmbil)) {
                        // 2. Jika berhasil, baru cari data itemnya untuk dimasukkan ke keranjang.
                        AddressItemNode nodeItemData = findItemDataOnTree(rootSupermarket, idBarang);
                        if (nodeItemData != NULL) {
                            // 3. Masukkan ke keranjang sebanyak jumlah yang diambil.
                            for (int i = 0; i < jumlahAmbil; i++) {
                                pushKeranjang(pelangganBaru.KPelanggan, &nodeItemData->dataBarang);
                            }
                            // HANYA SATU PESAN SUKSES DARI MAIN.C
                            printf(">> BERHASIL: '%s' x%d dimasukkan ke keranjang pelanggan '%s'.\n", 
                                   nodeItemData->dataBarang.namabarang, jumlahAmbil, pelangganBaru.nama);
                        }
                    } 
                    
                    printf("Tambah barang lagi untuk '%s'? (y/n): ", pelangganBaru.nama);
                    scanf(" %c", &tambahBarang);
                } while (tambahBarang == 'y' || tambahBarang == 'Y');
                
                printf("\n--- Pelanggan '%s' selesai berbelanja. ---\n", pelangganBaru.nama);
                displayKeranjang(pelangganBaru.KPelanggan);
                printf("-----------------------------------------\n");

                tambahPelanggan(&antrianPelanggan, pelangganBaru);
                break;
            }
            case 2:
                tampilkanPetaSupermarket(rootSupermarket);
                break;
            case 3:
                prosesPelanggan(&antrianPelanggan);
                break;
            case 4:
                tampilkanAntrian(antrianPelanggan);
                break;
            case 0:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilih != 0);
    
    // --- CLEANUP ---
    printf("\nMembersihkan semua memori...\n");
    bebaskanLayoutSupermarket(rootSupermarket);
    printf("Program selesai. Selamat tinggal!\n");

    return 0;
}


// Implementasi fungsi helper (sudah benar)
item buatContohItem(const char* id, const char* nama, double harga) {
    item newItem;
    strncpy(newItem.idbarang, id, sizeof(newItem.idbarang) - 1);
    newItem.idbarang[sizeof(newItem.idbarang) - 1] = '\0';
    
    strncpy(newItem.namabarang, nama, sizeof(newItem.namabarang) - 1);
    newItem.namabarang[sizeof(newItem.namabarang) - 1] = '\0';

    newItem.harga = harga;
    return newItem;
}

AddressItemNode findItemDataOnTree(TreeNode* root, const char* idBarang) {
    if (root == NULL) {
        return NULL;
    }
    RakData* dataRak = (RakData*)root->data;
    AddressItemNode foundNode = SearchItem(dataRak->daftarItem, idBarang);
    if (foundNode != NULL) {
        return foundNode;
    }
    TreeNode* child = root->firstChild;
    while (child != NULL) {
        AddressItemNode resultFromChild = findItemDataOnTree(child, idBarang);
        if (resultFromChild != NULL) {
            return resultFromChild;
        }
        child = child->nextSibling;
    }
    return NULL;
}
