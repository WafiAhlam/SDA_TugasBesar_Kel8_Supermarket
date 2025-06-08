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

// --- TAMBAHAN: Include header modul baru kita ---
#include "TreeRak.h"

// --- TAMBAHAN: Deklarasi fungsi helper ---
item buatContohItem(const char* id, const char* nama, double harga);
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idBarang);

int main() 
{
    // ==========================================================
    // --- TAMBAHAN: Blok untuk Setup Supermarket ---
    // ==========================================================
    printf("Selamat Datang di Program Simulasi Supermarket!\n");
    TreeNode* rootSupermarket = buatLayoutSupermarket();
    if (rootSupermarket == NULL) {
        fprintf(stderr, "Gagal membuat layout supermarket. Program berhenti.\n");
        return 1;
    }

    printf("\n--- Mengisi Barang ke Rak ---\n");
    item itemApel = buatContohItem("APL01", "Apel Fuji Premium", 25000.0);
    item itemSusu = buatContohItem("SUS01", "Susu UHT Coklat 1L", 18000.0);
    item itemDaging = buatContohItem("DAG01", "Daging Sapi Sirloin", 120000.0);

    TreeNode* rakBuah = cariRakDenganNama(rootSupermarket, "Sub-rak Buah");
    TreeNode* rakMinuman = cariRakDenganNama(rootSupermarket, "Rak Minuman");
    TreeNode* rakDaging = cariRakDenganNama(rootSupermarket, "Rak Daging & Ikan");

    // --- PERBAIKAN: Menggunakan nama fungsi yang benar ---
    if (rakBuah) tambahItemKeRak(rakBuah, itemApel, 100);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemSusu, 80);
    if (rakDaging) tambahItemKeRak(rakDaging, itemDaging, 30);
    
    // --- PERBAIKAN: Menggunakan nama fungsi yang benar ---
    tampilkanPetaSupermarket(rootSupermarket);
    // --- AKHIR BLOK TAMBAHAN ---


    // ====================================================================
    // --- KODE ASLI DIMULAI ---
    // ====================================================================
    
    Keranjang* keranjang = createKeranjang();
    
    char inputID[MAX_ID_BARANG];
    printf("\n--- keranjang ---\n");
    printf("Masukkan barang yang akan dimasukan ke keranjang: ");
    scanf("%s", inputID);

    AddressItemNode found = findItemDataOnTree(rootSupermarket, inputID); 
    if (found != NULL) {
        pushKeranjang(keranjang, &found->dataBarang);
        printf("Barang berhasil dimasukkan ke keranjang.\n");
    } else {
        printf("Barang tidak ditemukan di seluruh supermarket.\n");
    }

    displayKeranjang(keranjang);

    printf("\nMengeluarkan barang terakhir dari keranjang...\n");
    item* dikeluarkan = popKeranjang(keranjang);
    if (dikeluarkan != NULL) {
        printf("Barang '%s' dikeluarkan dari keranjang.\n", dikeluarkan->namabarang);
    }

    displayKeranjang(keranjang);

    double total = getTotalHargaKeranjang(keranjang);
    printf("Total belanja sekarang: %.2f\n", total);

    clearKeranjang(keranjang);
    free(keranjang);

    //Queue Chinta
    Queue antrianPelanggan;
    CreateQueue(&antrianPelanggan);

    int pilih;
    do {
        printf("\n\n=== Simulasi Kasir ===\n");
        printf("1. Pelanggan Baru Datang\n");
        printf("2. Proses Pelanggan di Kasir\n");
        printf("3. Tampilkan Antrian Pelanggan\n");
        printf("4. Tampilkan Peta Supermarket\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: {
                infotype pelangganBaru;
                
                printf("Masukkan nama pelanggan: ");
                scanf(" %[^\n]", pelangganBaru.nama);

                pelangganBaru.KPelanggan = createKeranjang();

                char tambahBarang;
                do {
                    char idBarang[MAX_ID_BARANG];
                    printf("Masukkan ID barang: ");
                    scanf("%s", idBarang);

                    AddressItemNode foundInQueue = findItemDataOnTree(rootSupermarket, idBarang);
                    if (foundInQueue != NULL) {
                        pushKeranjang(pelangganBaru.KPelanggan, &foundInQueue->dataBarang);
                        printf("Barang berhasil dimasukkan ke keranjang pelanggan '%s'.\n", pelangganBaru.nama);
                    } else {
                        printf("Barang tidak ditemukan di seluruh supermarket.\n");
                    }

                    printf("Tambah barang lagi? (y/n): ");
                    scanf(" %c", &tambahBarang);
                } while (tambahBarang == 'y' || tambahBarang == 'Y');

                tambahPelanggan(&antrianPelanggan, pelangganBaru);
                break;
            }
            case 2:
                prosesPelanggan(&antrianPelanggan);
                break;
            case 3:
                tampilkanAntrian(antrianPelanggan);
                break;
            case 4:
                // --- PERBAIKAN: Menggunakan nama fungsi yang benar ---
                tampilkanPetaSupermarket(rootSupermarket);
                break;
            case 0:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilih != 0);
    
    // --- TAMBAHAN: Cleanup untuk memori TreeRak ---
    printf("\nMembersihkan semua memori...\n");
    bebaskanLayoutSupermarket(rootSupermarket);
    printf("Program selesai. Selamat tinggal!\n");

    return 0;
}


// --- TAMBAHAN: Implementasi fungsi helper ---
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
