// File: main.c
#include <stdio.h>
#include <stdlib.h>
#include "Supermarket.h" // Asumsi berisi setupAndPopulateSupermarket()
#include "TreeRak.h"     // Asumsi berisi definisi Tree dan fungsi terkait
#include "Keranjang.h"   // Asumsi berisi implementasi keranjang belanja (linked list)

// Fungsi baru untuk sesi belanja yang lebih fokus pada Tree & Linked List
void sesiBelanjaInteraktif(TreeNode* rootSupermarket) {
    Keranjang* keranjangBelanja = createKeranjang();
    char namaPelanggan[50];
    int pilihBelanja;

    printf("\n============================================\n");
    printf("Pelanggan Baru Datang!\nMasukkan nama Anda: ");
    scanf(" %[^\n]", namaPelanggan);
    printf("============================================\n");
    printf("Selamat berbelanja, %s! 🛍️\n", namaPelanggan);

    do {
        printf("\n--- MENU BELANJA: %s ---\n", namaPelanggan);
        printf("1. Lihat Peta & Kunjungi Rak\n");
        printf("2. Lihat Isi Keranjang\n");
        printf("0. Selesai Belanja\n");
        printf("----------------------------------\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihBelanja);

        switch (pilihBelanja) {
            case 1: { // Kunjungi Rak
                tampilkanPetaSupermarket(rootSupermarket); // Tampilkan Tree
                
                char namaRak[MAX_PATH];
                printf("\nMasukkan nama Rak yang ingin dikunjungi: ");
                scanf(" %[^\n]", namaRak);

                TreeNode* rakTujuan = cariRakDenganNama(rootSupermarket, namaRak);

                if (rakTujuan != NULL) {
                    RakData* dataRak = (RakData*)rakTujuan->data;
                    printf("\n📍 Anda berada di: %s\n", dataRak->namaLokasi);
                    
                    // Tampilkan semua item di rak (Linked List)
                    PrintListItem(dataRak->daftarItem);

                    if (!ListItemEmpty(dataRak->daftarItem)) {
                        char idBarang[MAX_ID_BARANG];
                        printf("Masukkan ID barang yang ingin diambil (ketik '0' untuk batal): ");
                        scanf("%s", idBarang);

                        if (strcmp(idBarang, "0") != 0) {
                            AddressItemNode itemDiRak = SearchItem(dataRak->daftarItem, idBarang);

                            if (itemDiRak != NULL) {
                                int jumlahAmbil;
                                printf("Jumlah yang ingin diambil: ");
                                scanf("%d", &jumlahAmbil);

                                // Ambil barang dari rak dan masukkan ke keranjang
                                if (ambilItemDariRak(rakTujuan, idBarang, jumlahAmbil)) {
                                    // Masukkan ke keranjang (Linked List)
                                    tambahBarangKeKeranjang(keranjangBelanja, itemDiRak->dataBarang, jumlahAmbil);
                                    printf("✅ BERHASIL: %d x '%s' dimasukkan ke keranjang.\n", jumlahAmbil, itemDiRak->dataBarang.namabarang);
                                }
                            } else {
                                printf("❌ GAGAL: Barang dengan ID '%s' tidak ada di rak ini.\n", idBarang);
                            }
                        }
                    }
                } else {
                    printf("❌ GAGAL: Rak dengan nama '%s' tidak ditemukan.\n", namaRak);
                }
                break;
            }
            case 2:
                printf("\n--- 🛒 Isi Keranjang %s ---\n", namaPelanggan);
                displayKeranjang(keranjangBelanja);
                printf("--------------------------------\n");
                break;
            case 0:
                printf("\nTerima kasih, %s! Sesi belanja Anda telah berakhir.\n", namaPelanggan);
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihBelanja != 0);

    // Proses checkout sederhana
    if (!isKeranjangEmpty(keranjangBelanja)) {
        printf("\n--- Struk Belanja %s ---\n", namaPelanggan);
        displayKeranjang(keranjangBelanja);
        printf("Total Belanja: Rp %.2f\n", hitungTotalBelanja(keranjangBelanja));
        printf("---------------------------\n");
    }
    
    // Bebaskan memori keranjang setelah selesai
    freeKeranjang(keranjangBelanja);
}


int main() {
    // Inisialisasi layout supermarket (Tree) dan isi dengan item (Linked List di setiap node)
    TreeNode* rootSupermarket = setupAndPopulateSupermarket();
    if (rootSupermarket == NULL) {
        return 1;
    }
    
    int pilih;
    do {
        printf("\n=========================================\n");
        printf("      SELAMAT DATANG DI CHIKAFIKET\n");
        printf("=========================================\n");
        printf(" 1. Mulai Sesi Belanja\n");
        printf(" 2. Tampilkan Peta Supermarket\n");
        printf(" 0. Keluar\n");
        printf("=========================================\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                sesiBelanjaInteraktif(rootSupermarket);
                break;
            case 2:
                tampilkanPetaSupermarket(rootSupermarket);
                break;
            case 0:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("\nPilihan tidak valid.\n");
        }
    } while (pilih != 0);
    
    printf("\nMembersihkan semua memori...\n");
    bebaskanLayoutSupermarket(rootSupermarket);
    printf("Program selesai. Sampai jumpa! 👋\n");

    return 0;
}