#include <stdio.h>
#include <stdlib.h>
#include "TreeRak.h"
#include "avl.h"
#include "admin.h"      
#include "pelanggan.h"
#include "tumpukan.h"

// Deklarasi fungsi helper dari admin.c
void clearScreen();

int main() {
    // 1. Inisialisasi semua struktur data utama di sini
    RakBTree* databaseProdukAVL = NULL; // Database utama produk
    TreeNode* layoutSupermarket = buatLayoutSupermarket(); // Peta fisik
    char tumpukan[100] = "cihuy";
    RakTumpukan* rakTumpukan = createRakTumpukan(tumpukan);
    

    // Anda bisa mengisi beberapa data awal di sini jika perlu
    // Contoh: databaseProdukAVL = insertProduk(databaseProdukAVL, produk1);
    //         tambahItemKeRak(rakTujuan, produk1, 10);

    if (layoutSupermarket == NULL) {
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
                // Panggil fungsi yang mengurus seluruh mode admin
                jalankanModeAdmin(&databaseProdukAVL, layoutSupermarket);
                break;
            case 2:
                // Sama, panggil fungsi yang mengurus seluruh mode pelanggan
                 menuPelanggan(layoutSupermarket, &databaseProdukAVL, rakTumpukan);
                printf("\nMode pelanggan belum terhubung. Silakan implementasikan.\n");
                printf("Tekan Enter untuk kembali...");
                getchar();
                break;
            case 0:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("\nPilihan tidak valid. Coba lagi.\n");
                printf("Tekan Enter untuk kembali...");
                getchar();
        }
    } while (pilihan != 0);

    // 2. Bersihkan semua memori sebelum program berakhir
    printf("\nMembersihkan memori...\n");
    deleteTree(&databaseProdukAVL); // Hapus AVL Tree
    bebaskanLayoutSupermarket(layoutSupermarket); // Hapus Non-Binary Tree
    printf("Program selesai. Sampai jumpa! 👋\n");

    return 0;
}