/**
 * File: admin.c (REVISED & UPDATED)
 * Deskripsi: Implementasi menu dan fungsionalitas untuk admin, termasuk manajemen antrian.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "tumpukan.h"
// --- PENAMBAHAN HEADER ---
#include "kasir.h"
#include "pelanggan.h"


// Struct untuk data admin, bisa tetap di sini atau dipindah ke admin.h jika perlu
typedef struct {
    char username[50];
    char password[50];
} Admin;


// --- FUNGSI HELPER UNTUK TAMPILAN & INPUT ---
void clearScreen() {
    // Gunakan "cls" untuk Windows, "clear" untuk Linux/macOS.
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    // Membersihkan buffer input yang mungkin tersisa dari scanf
    while(getchar() != '\n');
    getchar(); // Menunggu user menekan Enter
}


// --- FUNGSI LOGIN & REGISTRASI (Tidak Diubah) ---
int isUsernameExist(const char* username) {
    FILE* file = fopen("admin_data.txt", "r");
    if (!file) return 0;
    Admin temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) != EOF) {
        if (strcmp(temp.username, username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void registerAdmin() {
    clearScreen();
    Admin newAdmin;
    printf("=== REGISTRASI ADMIN ===\n");
    printf("Masukkan username baru: ");
    scanf("%49s", newAdmin.username);

    if (isUsernameExist(newAdmin.username)) {
        printf("\nUsername sudah terdaftar!\n");
        pressEnterToContinue();
        return;
    }

    printf("Masukkan password baru: ");
    scanf("%49s", newAdmin.password);

    FILE* file = fopen("admin_data.txt", "a");
    if (file == NULL) {
        printf("\nGagal membuka file data admin!\n");
        pressEnterToContinue();
        return;
    }
    fprintf(file, "%s %s\n", newAdmin.username, newAdmin.password);
    fclose(file);
    printf("\nRegistrasi berhasil!\n");
    pressEnterToContinue();
}

int loginAdmin() {
    clearScreen();
    Admin login;
    printf("=== LOGIN ADMIN ===\n");
    printf("Masukkan username: ");
    scanf("%49s", login.username);
    printf("Masukkan password: ");
    scanf("%49s", login.password);

    FILE* file = fopen("admin_data.txt", "r");
    if (file == NULL) {
        printf("\nBelum ada admin terdaftar!\n");
        pressEnterToContinue();
        return 0;
    }

    Admin temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) != EOF) {
        if (strcmp(login.username, temp.username) == 0 && strcmp(login.password, temp.password) == 0) {
            fclose(file);
            printf("\nLogin berhasil. Selamat datang, %s!\n", login.username);
            pressEnterToContinue();
            return 1;
        }
    }

    fclose(file);
    printf("\nLogin gagal. Username atau password salah.\n");
    pressEnterToContinue();
    return 0;
}


// --- FUNGSI MENU UTAMA ADMIN ---

// Deklarasi agar prosesMenuAdmin bisa dipanggil dari jalankanModeAdmin
void prosesMenuAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir);


// Fungsi ini yang akan dipanggil dari main.c
void jalankanModeAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir) {
    int pilihan;
    do {
        clearScreen();
        printf("=========================\n");
        printf("      MODE ADMIN\n");
        printf("=========================\n");
        printf("1. Login\n");
        printf("2. Registrasi Admin Baru\n");
        printf("0. Kembali ke Menu Utama\n");
        printf("=========================\n");
        printf("Pilihan Anda: ");
        
        if (scanf("%d", &pilihan) != 1) {
            pilihan = -1;
        }
        while(getchar() != '\n'); // Clear buffer

        switch(pilihan) {
            case 1:
                if (loginAdmin()) {
                    // --- PERUBAHAN ---
                    // Mengoper antrianKasir ke prosesMenuAdmin
                    prosesMenuAdmin(rootAVL, rootLayout, rakTumpukan, antrianKasir);
                }
                break;
            case 2:
                registerAdmin();
                break;
            case 0:
                printf("\nKembali ke menu utama...\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                pressEnterToContinue();
        }
    } while (pilihan != 0);
}

// --- PERUBAHAN SIGNATURE ---
// Menambahkan AntrianKasir* antrianKasir sebagai parameter
void prosesMenuAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir) {
    int pilihan;
    do {
        clearScreen();
        printf("==========================================\n");
        printf("               MENU UTAMA ADMIN\n");
        printf("==========================================\n");
        printf("1. Tambah Produk Baru ke Database\n");
        printf("2. Hapus Produk dari Database\n");
        printf("3. Lihat Semua Produk (Database AVL)\n");
        printf("4. Tambah Stok Produk ke Rak Fisik\n");
        printf("5. Lihat Peta Layout Supermarket\n");
        printf("6. Isi Rak Promosi (PUSH ke Stack)\n");
        // --- PENAMBAHAN OPSI MENU ---
        printf("7. Lihat Antrian Kasir\n");
        printf("8. Layani Pelanggan dari Antrian\n");
        printf("0. Logout\n");
        printf("==========================================\n");
        printf("Pilihan Anda: ");
        
        if (scanf("%d", &pilihan) != 1) {
            pilihan = -1;
        }
        while(getchar() != '\n');

        switch(pilihan) {
            case 1:
                menuTambahProduk(rootAVL);
                break;
            case 2:
                menuHapusProduk(rootAVL, rootLayout);
                break;
            case 3:
                menuLihatProduk(*rootAVL);
                break;
            case 4:
                menuTambahStokKeRak(*rootAVL, rootLayout);
                break;
            case 5:
                menuLihatPeta(rootLayout);
                break;
            case 6:
                menuPushProdukKeTumpukan(*rootAVL, rakTumpukan);
                break;
            // --- PENAMBAHAN CASE BARU ---
            case 7:
                clearScreen();
                displayAntrian(antrianKasir);
                pressEnterToContinue();
                break;
            case 8:
                menuLayaniPelanggan(antrianKasir);
                break;
            case 0:
                printf("\nLogout dari sesi admin...\n");
                pressEnterToContinue();
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                pressEnterToContinue();
        }
    } while (pilihan != 0);
}

void menuPushProdukKeTumpukan(RakBTree* rootAVL, RakTumpukan* rakTumpukan) {
    // Versi yang sudah diperbaiki dari jawaban sebelumnya
    clearScreen();
    char idProduk[20];
    
    printf("--- Isi Rak Promosi (Stack) ---\n");
    
    printf("Masukkan ID Produk yang akan diletakkan di rak promosi: ");
    scanf("%19s", idProduk);
    
    RakBTree* nodeProduk = searchProduk(rootAVL, idProduk);
    if (nodeProduk == NULL) {
        printf("\nError: Produk dengan ID '%s' tidak ada di database.\n", idProduk);
    } else {
        pushToRak(rakTumpukan, nodeProduk->info);
        printf("\nProduk '%s' berhasil diletakkan di paling atas rak promosi.\n", nodeProduk->info.nama);
    }

    printf("\nKondisi Rak Promosi Saat Ini:\n");
    displayRakTumpukan(rakTumpukan); 

    pressEnterToContinue();
}

// --- FUNGSI UNTUK SETIAP OPSI MENU ADMIN (Tidak Diubah) ---
void menuTambahProduk(RakBTree** rootAVL) {
    clearScreen();
    Produk p;
    printf("--- Tambah Produk Baru ---\n");
    printf("Masukkan ID Produk (e.g., BR001): ");
    scanf("%19s", p.idProduk);
    printf("Masukkan Nama Produk: ");
    scanf(" %[^\n]", p.nama);
    printf("Masukkan Harga Produk: ");
    scanf("%f", &p.harga);
    printf("Masukkan Stok Awal Global: ");
    scanf("%d", &p.stok);

    *rootAVL = insertProduk(*rootAVL, p);
    printf("\nProduk '%s' berhasil ditambahkan ke database AVL.\n", p.nama);
    pressEnterToContinue();
}

void menuHapusProduk(RakBTree** rootAVL, TreeNode* rootLayout) {
    clearScreen();
    char idHapus[20];
    printf("--- Hapus Produk dari Database ---\n");
    printf("Masukkan ID Produk yang akan dihapus: ");
    scanf("%19s", idHapus);

    if (searchProduk(*rootAVL, idHapus) == NULL) {
        printf("\nProduk dengan ID '%s' tidak ditemukan.\n", idHapus);
    } else {
        *rootAVL = deleteProduk(*rootAVL, idHapus);
        printf("\nProduk dengan ID '%s' telah dihapus dari database AVL.\n", idHapus);
    }
    pressEnterToContinue();
}

void menuLihatProduk(RakBTree* rootAVL) {
    clearScreen();
    printf("--- DAFTAR SEMUA PRODUK (Sorted by ID) ---\n\n");
    if (rootAVL == NULL) {
        printf("Database produk masih kosong.\n");
    } else {
        inOrderProduk(rootAVL);
    }
    printf("\n------------------------------------------\n");
    pressEnterToContinue();
}

void menuTambahStokKeRak(RakBTree* rootAVL, TreeNode* rootLayout) { 
    clearScreen();
    char idProduk[20], namaRak[100];
    int jumlahStok;
    printf("--- Tambah Stok ke Rak Fisik ---\n");
    printf("Masukkan ID Produk: ");
    scanf("%19s", idProduk);

    RakBTree* nodeProduk = searchProduk(rootAVL, idProduk);
    if (nodeProduk == NULL) {
        printf("\nError: Produk dengan ID '%s' tidak ada di database.\n", idProduk);
    } else {
        printf("Masukkan Nama Rak Tujuan (e.g., 'Chitato Area'): ");
        scanf(" %[^\n]", namaRak);
        TreeNode* nodeRak = cariRakDenganNama(rootLayout, namaRak);

        if (nodeRak == NULL) {
            printf("\nError: Rak dengan nama '%s' tidak ditemukan.\n", namaRak);
        } else {
            printf("Masukkan jumlah stok yang akan ditaruh di rak: ");
            scanf("%d", &jumlahStok);
            tambahItemKeRak(nodeRak, nodeProduk->info, jumlahStok);
        }
    }
    pressEnterToContinue();
}

void menuLihatPeta(TreeNode* rootLayout) {
    clearScreen();
    tampilkanPetaSupermarket(rootLayout);
    pressEnterToContinue();
}

// --- FUNGSI MELAYANI PELANGGAN (DIPERBARUI) ---
void menuLayaniPelanggan(AntrianKasir* antrian) {
    clearScreen();
    printf("--- Layani Pelanggan ---\n");
    displayAntrian(antrian); // Tampilkan antrian saat ini

    Pelanggan pelangganDilayani;

    if (dequeuePelanggan(antrian, &pelangganDilayani)) {
        printf("\nMelayani pelanggan: %s\n", pelangganDilayani.nama);
        
        // Proses keranjang belanjanya
        displayKeranjang(pelangganDilayani.keranjang);
        printf("\nTotal yang harus dibayar: %.0f\n", pelangganDilayani.keranjang->totalHarga);
        printf("--- PEMBAYARAN DIPROSES ---\n");
        printf("Pembayaran berhasil. Terima kasih!\n\n");

        // --- PENAMBAHAN: Simpan struk belanja ---
        saveCustomerReceipt(pelangganDilayani);

        // Setelah selesai, keranjang pelanggan dihancurkan
        destroyKeranjang(&(pelangganDilayani.keranjang));
    }
    // Jika antrian kosong, pesan error sudah dicetak di dalam dequeuePelanggan

    pressEnterToContinue();
}