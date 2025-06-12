
#include <stdio.h>
#include <stdlib.h>
#include "TreeRak.h"       // Untuk struktur Tree
#include "Supermarket.h"   // Untuk setupAndPopulateSupermarket()
#include "admin.h"         // Asumsi ada menuAdmin()
#include "pelanggan.h"     // Asumsi ada menuPelanggan()

int main() {
    // Inisialisasi layout supermarket (Tree)
    TreeNode* rootSupermarket = setupAndPopulateSupermarket();
    if (rootSupermarket == NULL) {
        printf("Gagal memuat peta supermarket.\n");
        return 1;
    }

    int pilihan;
    do {
        printf("\n====================================\n");
        printf("    SELAMAT DATANG DI CHIKAFIKET\n");
        printf("====================================\n");
        printf(" 1. Masuk sebagai Admin\n");
        printf(" 2. Masuk sebagai Pelanggan\n");
        printf(" 0. Keluar\n");
        printf("====================================\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("\n-- Masuk ke Mode Admin --\n");
                menuAdmin(rootSupermarket);
                break;
            case 2:
                printf("\n-- Masuk ke Mode Pelanggan --\n");
                menuPelanggan(rootSupermarket);
                break;
            case 0:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }

    } while (pilihan != 0);

    // Bersihkan Tree setelah keluar
    printf("\nMembersihkan memori...\n");
    bebaskanLayoutSupermarket(rootSupermarket);
    printf("Program selesai. Sampai jumpa! 👋\n");

    return 0;
}
