#include <stdio.h>
#include "pelanggan.h"

void pelangganMenu() {
    int pilihan;
    do {
        printf("\n=== MENU PELANGGAN ===\n");
        printf("1. Lihat Produk\n");
        printf("2. Tambah ke Keranjang\n");
        printf("3. Lihat Keranjang\n");
        printf("4. Checkout\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                printf("-> Fitur lihat produk (belum diimplementasi).\n");
                break;
            case 2:
                printf("-> Tambah ke keranjang (belum diimplementasi).\n");
                break;
            case 3:
                printf("-> Lihat keranjang (belum diimplementasi).\n");
                break;
            case 4:
                printf("-> Checkout (belum diimplementasi).\n");
                break;
            case 0:
                printf("-> Keluar.\n");
                break;
            default:
                printf("-> Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

void menuPelanggan(TreeNode* rootSupermarket) {
    printf(">> Masuk ke Menu Pelanggan <<\n");
    pelangganMenu(); // panggil menu pelanggan yang kamu buat
}
