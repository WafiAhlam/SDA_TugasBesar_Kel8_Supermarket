#include <stdio.h>
#include <stdlib.h>

// Include semua ADT dan Modul Menu
#include "TreeRak.h"
#include "avl.h"
#include "tumpukan.h"
#include "kasir.h"      // -- PENAMBAHAN 1: Include header untuk Antrian Kasir --
#include "admin.h"
#include "pelanggan.h"

// Deklarasi fungsi helper dari admin.c (jika ada)
void clearScreen();
void pressEnterToContinue(); // Tambahkan deklarasi ini jika belum ada di header

int main() {
    // 1. Inisialisasi semua struktur data utama di sini
    RakBTree* databaseProdukAVL = NULL;                     // Database utama produk (AVL)
    TreeNode* layoutSupermarket = buatLayoutSupermarket();    // Peta rak fisik (Non-Binary Tree)
    RakTumpukan* rakTumpukan = createRakTumpukan("Rak Promosi Utama"); // Rak tumpukan (Stack)
    
    // -- PENAMBAHAN 2: Inisialisasi Antrian Kasir (Queue) --
    AntrianKasir* antrianKasir = createAntrian();

    if (layoutSupermarket == NULL || rakTumpukan == NULL || antrianKasir == NULL) {
        printf("Gagal memuat peta supermarket. Program berhenti.\n");
        return 1;
    }

    int pilihan;
    do {
        clearScreen();
        printf("\n====================================\n");
        printf("      SELAMAT DATANG DI CHIKAFIKET\n");
        printf("====================================\n");
        printf("1. Masuk sebagai Admin\n");
        printf("2. Masuk sebagai Pelanggan\n");
        printf("0. Keluar\n");
        printf("====================================\n");
        printf("Pilih menu: ");

        if (scanf("%d", &pilihan) != 1) {
            pilihan = -1; // Input tidak valid
        }
        while(getchar() != '\n'); // Selalu bersihkan buffer setelah scanf

        switch (pilihan) {
            case 1:
                // -- PENAMBAHAN 3: Mengoper AntrianKasir ke fungsi menu admin --
                jalankanModeAdmin(&databaseProdukAVL, layoutSupermarket, rakTumpukan, antrianKasir);
                break;
            case 2:
                // -- PENAMBAHAN 3: Mengoper AntrianKasir ke fungsi menu pelanggan --
                // -- PERBAIKAN PENTING: Pelanggan hanya perlu membaca AVL, jadi kirim pointer biasa --
                menuPelanggan(layoutSupermarket, databaseProdukAVL, rakTumpukan, antrianKasir);
                break;
            case 0:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("\nPilihan tidak valid. Coba lagi.\n");
                pressEnterToContinue();
        }
    } while (pilihan != 0);

    // 2. Bersihkan semua memori sebelum program berakhir
    printf("\nMembersihkan memori...\n");
    deleteTree(&databaseProdukAVL);             // Hapus AVL Tree
    bebaskanLayoutSupermarket(layoutSupermarket); // Hapus Non-Binary Tree

    // -- PENAMBAHAN 4: Membersihkan memori Antrian dan Rak Tumpukan --
    destroyRakTumpukan(&rakTumpukan);
    destroyAntrian(&antrianKasir);

    printf("Program selesai. Sampai jumpa! :) \n");

    return 0;
}