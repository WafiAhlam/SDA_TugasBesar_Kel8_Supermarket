#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pelanggan.h"
#include "Keranjang.h"
#include "tumpukan.h"

// Deklarasi fungsi helper dari file lain
void clearScreen();
void pressEnterToContinue();

// Implementasi fungsi utama menu pelanggan
void menuPelanggan(TreeNode* rootSupermarket, RakBTree** rootAVL, RakTumpukan* rakTumpukan) {
    Pelanggan pelanggan;
    printf("\nMasukkan nama Anda: ");
    scanf("%49s", pelanggan.nama);
    while(getchar() != '\n');

    // Setiap pelanggan baru mendapatkan keranjang baru
    pelanggan.keranjang = createKeranjang();
    
    int pilihan;
    do {
        clearScreen();
        printf("=========================================\n");
        printf("            MENU PELANGGAN\n");
        printf("    Selamat datang, %s!\n", pelanggan.nama);
        printf("=========================================\n");
        printf("1. Lihat Peta & Isi Rak Supermarket\n");
        printf("2. Ambil Barang dari Rak Promosi (POP from Stack)\n");
        printf("3. Lihat Keranjang Belanja (Riwayat Pengambilan)\n");
        printf("0. Selesai Belanja (Checkout)\n");
        printf("=========================================\n");
        printf("Pilihan Anda: ");

        if (scanf("%d", &pilihan) != 1) {
            pilihan = -1;
        }
        while(getchar() != '\n');

        switch (pilihan) {
            case 1:
                clearScreen();
                // Menampilkan peta dan rak tumpukan
                tampilkanPetaSupermarket(rootSupermarket);
                displayRakTumpukan(rakTumpukan);
                pressEnterToContinue();
                break;
            case 2:
                { // Blok baru untuk deklarasi variabel lokal
                    clearScreen();
                    printf("--- Mengambil Barang dari Rak Promosi ---\n");
                    displayRakTumpukan(rakTumpukan);

                    Produk produkDikeluarkan;
                    // Lakukan POP dari rak
                    if (popFromRak(rakTumpukan, &produkDikeluarkan)) {
                        printf("-> Anda mengambil: '%s'.\n", produkDikeluarkan.nama);
                        // Tambahkan produk yang di-POP ke keranjang belanja
                        tambahProdukKeKeranjang(pelanggan.keranjang, produkDikeluarkan, 1);
                    }
                    pressEnterToContinue();
                }
                break;
            case 3:
                clearScreen();
                // Display keranjang berfungsi sebagai riwayat belanja
                displayKeranjang(pelanggan.keranjang);
                pressEnterToContinue();
                break;
            case 0:
                clearScreen();
                printf("--- Proses Checkout ---\n");
                displayKeranjang(pelanggan.keranjang);
                if (!isKeranjangEmpty(pelanggan.keranjang)) {
                    printf("\nTerima kasih telah berbelanja, %s!\n", pelanggan.nama);
                    printf("Total belanja Anda adalah: %.0f\n", pelanggan.keranjang->totalHarga);
                    saveCustomerReceipt(pelanggan); // Simpan struk
                } else {
                    printf("\nAnda tidak membeli apa-apa. Sampai jumpa lagi!\n");
                }
                // Hancurkan keranjang setelah selesai
                destroyKeranjang(&pelanggan.keranjang);
                pressEnterToContinue();
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                pressEnterToContinue();
        }

    } while (pilihan != 0);
}

// Implementasi fungsi simpan struk yang sudah diperbaiki
void saveCustomerReceipt(Pelanggan p) {
    char filename[100];
    sprintf(filename, "struk_%s.txt", p.nama);
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuat file struk untuk %s\n", p.nama);
        return;
    }
    
    time_t now = time(NULL);
    char* dt = ctime(&now);

    fprintf(file, "=======================================\n");
    fprintf(file, "         STRUK BELANJA - CHIKAFIKET\n");
    fprintf(file, "=======================================\n");
    fprintf(file, "Pelanggan : %s\n", p.nama);
    fprintf(file, "Waktu     : %s", dt); // ctime sudah punya newline
    fprintf(file, "---------------------------------------\n");
    fprintf(file, "Barang yang Dibeli:\n");

    // Iterasi melalui KeranjangBelanja (linked list), bukan stack
    KeranjangNode* current = p.keranjang->head;
    while (current != NULL) {
        fprintf(file, "- %-25s x%d (Rp %.0f)\n", 
            current->infoProduk.nama, 
            current->kuantitas, 
            current->infoProduk.harga * current->kuantitas);
        current = current->next;
    }

    fprintf(file, "---------------------------------------\n");
    fprintf(file, "TOTAL BELANJA : Rp %.0f\n", p.keranjang->totalHarga);
    fprintf(file, "=======================================\n");
    fprintf(file, "      Terima Kasih Telah Berbelanja!   \n");
    fprintf(file, "=======================================\n");
    
    fclose(file);
    printf("Struk belanja telah disimpan ke file: %s\n", filename);
}