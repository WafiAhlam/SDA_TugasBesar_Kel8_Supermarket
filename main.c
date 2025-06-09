#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Supermarket.h" // Modul baru untuk setup!
#include "TreeRak.h"       // Tetap diperlukan untuk fungsi-fungsi seperti tampilkanPeta, dll.
#include "Queue.h"
#include "Keranjang.h"
#include "pelanggan.h"
#include "Kasir.h"

// Deklarasi fungsi helper. Idealnya ini dipindah ke TreeRak.h/.c
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idBarang);

int main() 
{
    // ==========================================================
    // SETUP SUPERMARKET MENJADI SATU PANGGILAN FUNGSI
    // Semua kerumitan pembuatan item dan rak ada di dalam Supermarket.c
    // ==========================================================
    TreeNode* rootSupermarket = setupAndPopulateSupermarket();
    if (rootSupermarket == NULL) {
        return 1; // Pesan error sudah ditampilkan di dalam fungsi setup
    }

    // ====================================================================
    // SIMULASI UTAMA (Tidak ada perubahan di sini)
    // main.c sekarang hanya fokus pada alur menu interaktif.
    // ====================================================================
    Queue antrianPelanggan;
    CreateQueue(&antrianPelanggan);

    int pilih;
    do {

        printf("\n");
        printf("=========================================\n");
        printf("      SELAMAT DATANG DI CHIKAFIKET       \n");
        printf("=========================================\n\n");

         printf("=========================================\n");
        printf("          MENU UTAMA SIMULASI             \n");
        printf("=========================================\n");
        printf(" 1. Pelanggan Baru Datang & Belanja      \n");
        printf(" 2. Tampilkan Peta Supermarket           \n");
        printf(" 3. Cari Rute & Jarak Antar Rak          \n");
        printf(" 4. Proses Pelanggan Berikutnya di Kasir \n");
        printf(" 5. Tampilkan Antrian Pelanggan           \n");
        printf(" 0. Keluar                               \n");
        printf("=========================================\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);
        printf("\n");

        switch (pilih) {
            case 1: { // Pelanggan Baru Datang
                infotype pelangganBaru;
                printf("\n============================================\n");
                printf("Masukkan nama pelanggan: ");
                scanf(" %[^\n]", pelangganBaru.nama);
                printf("\n============================================\n");

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
                    printf("\n============================================\n");
                    //

                    if (ambilItemDariRak(rootSupermarket, idBarang, jumlahAmbil)) {
                        AddressItemNode nodeItemData = findItemDataOnTree(rootSupermarket, idBarang);
                        if (nodeItemData != NULL) {
                            for (int i = 0; i < jumlahAmbil; i++) {
                                pushKeranjang(pelangganBaru.KPelanggan, &nodeItemData->dataBarang);
                            }
                            
                           
                            printf(">> BERHASIL: '%s' x%d dimasukkan ke keranjang.\n", nodeItemData->dataBarang.namabarang, jumlahAmbil);
                            printf("\n============================================\n");
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
            case 3: {
                char namaAwal[50], namaTujuan[50];
                printf("\n--- Navigasi Rute ---\n");
                tampilkanPetaSupermarket(rootSupermarket);
                printf("Masukkan Lokasi Awal (contoh: Pintu Masuk): ");
                scanf(" %[^\n]", namaAwal);
                printf("Masukkan Lokasi Tujuan (contoh: Rak Daging & Ikan): ");
                scanf(" %[^\n]", namaTujuan);
                cariRuteDanJarak(rootSupermarket, namaAwal, namaTujuan);
                break;
            }
            case 4:
                prosesPelanggan(&antrianPelanggan);
                break;
            case 5:
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

// Implementasi findItemDataOnTree (Idealnya dipindah ke TreeRak.c)
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
