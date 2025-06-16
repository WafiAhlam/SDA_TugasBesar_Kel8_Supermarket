/**
 * File: pelanggan.c (REVISED & ENHANCED)
 * Deskripsi: Implementasi lengkap untuk alur kerja pelanggan, termasuk
 * belanja dari rak fisik dan integrasi dengan antrian kasir.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "items.h"
#include "pelanggan.h"
#include "kasir.h" // Diperlukan untuk mengakses ADT Antrian Kasir

// Deklarasi fungsi helper dari file lain jika diperlukan
void clearScreen();
void pressEnterToContinue();

// Deklarasi fungsi-fungsi menu internal
// Fungsi utama yang dipanggil dari main.c
void menuPelanggan(TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir) {
    Pelanggan pelanggan;
    clearScreen();
    printf("=========================================\n");
    printf("         SELAMAT DATANG DI CHIKAFIKET\n");
    printf("=========================================\n");
    printf("Silakan masukkan nama Anda untuk memulai sesi: ");
    scanf(" %49[^\n]", pelanggan.nama);
    while(getchar() != '\n');

    // Setiap pelanggan baru mendapatkan keranjang belanja kosong
    pelanggan.keranjang = createKeranjang();
    if (pelanggan.keranjang == NULL) {
        printf("Gagal memulai sesi belanja. Coba lagi.\n");
        return;
    }

    // Mulai sesi belanja interaktif
    sesiBelanjaInteraktif(&pelanggan, rootLayout, rootAVL, rakTumpukan, antrianKasir);
}


// Loop menu utama selama pelanggan berbelanja
void sesiBelanjaInteraktif(Pelanggan* pelanggan, TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakPromosi, AntrianKasir* antrianKasir) {
    int pilihan;
    do {
        clearScreen();
        displayKeranjang(pelanggan->keranjang); // Selalu tampilkan isi keranjang saat ini
        printf("\n--- MENU BELANJA [Pelanggan: %s] ---\n", pelanggan->nama);
        printf("1. Lihat Peta Supermarket\n");
        printf("2. Ambil Barang dari Rak Fisik\n");
        printf("3. Ambil Barang dari Rak Promosi (Stack)\n");
        printf("0. Selesai & Masuk Antrian Kasir\n");
        printf("---------------------------------------\n");
        printf("Pilihan Anda: ");

        if (scanf("%d", &pilihan) != 1) {
            pilihan = -1;
        }
        while(getchar() != '\n');

        switch(pilihan) {
            case 1:
                clearScreen();
                tampilkanPetaSupermarket(rootLayout);
                pressEnterToContinue();
                break;
            case 2:
                // Fungsi baru untuk mengambil barang dari rak biasa
                menuAmbilDariRakFisik(pelanggan->keranjang, rootLayout, rootAVL);
                break;
            case 3:
                // Fungsi yang sudah ada, kini lebih rapi
                menuAmbilDariRakPromosi(pelanggan->keranjang, rakPromosi);
                break;
            case 0:
                // Fungsi baru untuk checkout dengan sistem antrian
                menuMasukAntrian(antrianKasir, pelanggan);
                pilihan = 0; // Set pilihan agar loop berhenti setelah masuk antrian
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                pressEnterToContinue();
        }
    } while (pilihan != 0);

    // Jika pelanggan keluar tanpa checkout, keranjang tetap dihancurkan
    if (pelanggan->keranjang != NULL) {
        destroyKeranjang(&(pelanggan->keranjang));
    }
}


// FUNGSI BARU: Mengambil barang dari rak fisik (Non-Binary Tree)
void menuAmbilDariRakFisik(KeranjangBelanja* keranjang, TreeNode* rootLayout, RakBTree* rootAVL) {
    clearScreen();
    char idProduk[20], namaRak[100];
    int jumlahAmbil;

    tampilkanPetaSupermarket(rootLayout);
    printf("\n--- Ambil Barang dari Rak Fisik ---\n");
    printf("Masukkan Nama Rak Tujuan (e.g., 'Chitato Area'): ");
    scanf(" %[^\n]", namaRak);

    TreeNode* nodeRak = cariRakDenganNama(rootLayout, namaRak);
    if (nodeRak == NULL) {
        printf("\nError: Rak '%s' tidak ditemukan.\n", namaRak);
        pressEnterToContinue();
        return;
    }

    printf("Masukkan ID Produk yang akan diambil: ");
    scanf("%19s", idProduk);

    RakBTree* nodeInfoProduk = searchProduk(rootAVL, idProduk);
    if (nodeInfoProduk == NULL) {
        printf("\nError: Produk dengan ID '%s' tidak terdaftar di sistem.\n", idProduk);
        pressEnterToContinue();
        return;
    }

    printf("Masukkan jumlah yang ingin diambil: ");
    scanf("%d", &jumlahAmbil);
    while(getchar() != '\n');

    RakData* dataRak = (RakData*)nodeRak->data;
    if (kurangiStokItem(&(dataRak->daftarItem), idProduk, jumlahAmbil)) {
        tambahProdukKeKeranjang(keranjang, nodeInfoProduk->info, jumlahAmbil);
    }
    pressEnterToContinue();
}


// Fungsi yang sudah ada, dibungkus ulang
void menuAmbilDariRakPromosi(KeranjangBelanja* keranjang, RakTumpukan* rakPromosi) {
    clearScreen();
    printf("--- Mengambil Barang dari Rak Promosi ---\n");
    displayRakTumpukan(rakPromosi);

    Produk produkDikeluarkan;
    if (popFromRak(rakPromosi, &produkDikeluarkan)) {
        printf("-> Anda mengambil: '%s'.\n", produkDikeluarkan.nama);
        tambahProdukKeKeranjang(keranjang, produkDikeluarkan, 1);
    }
    pressEnterToContinue();
}


// FUNGSI BARU: Mengintegrasikan dengan Antrian Kasir (Queue)
void menuMasukAntrian(AntrianKasir* antrian, Pelanggan* pelanggan) {
    clearScreen();
    if (isKeranjangEmpty(pelanggan->keranjang)) {
        printf("Keranjang Anda kosong. Anda tidak perlu mengantri.\n");
    } else {
        printf("--- Menuju Kasir ---\n");
        displayKeranjang(pelanggan->keranjang);
        
        // Membungkus data pelanggan (nama + keranjang) untuk dimasukkan ke antrian
        Pelanggan p;
        strcpy(p.nama, pelanggan->nama);
        p.keranjang = pelanggan->keranjang;
        
        enqueuePelanggan(antrian, p);

        // Setelah pelanggan masuk antrian, sesi belanjanya selesai.
        // Pointer keranjangnya sekarang dimiliki oleh antrian, jadi kita set NULL di sini
        // agar tidak di-destroy dua kali oleh fungsi sesiBelanjaInteraktif.
        pelanggan->keranjang = NULL;

        printf("Anda sekarang berada dalam antrian kasir. Silakan tunggu giliran.\n");
    }
    pressEnterToContinue();
}


// Implementasi fungsi simpan struk (SEHARUSNYA DIPANGGIL DARI SISI KASIR/ADMIN SETELAH DEQUEUE)
void saveCustomerReceipt(Pelanggan p) {
    // ... (kode fungsi ini dari Anda sudah baik, tidak perlu diubah) ...
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
    fprintf(file, "Waktu     : %s", dt);
    fprintf(file, "---------------------------------------\n");
    fprintf(file, "Barang yang Dibeli:\n");

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