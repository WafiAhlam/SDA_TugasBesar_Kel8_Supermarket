#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Supermarket.h"
#include "TreeRak.h"
#include "Queue.h"
#include "Keranjang.h"
#include "pelanggan.h"
#include "Kasir.h"

int main() 
{
    TreeNode* rootSupermarket = setupAndPopulateSupermarket();
    if (rootSupermarket == NULL) {
        return 1;
    }
    
    Queue antrianPelanggan;
    CreateQueue(&antrianPelanggan);

    int pilih;
    do {
        printf("\n");
        printf("=========================================\n");
        printf("       SELAMAT DATANG DI CHIKAFIKET      \n");
        printf("=========================================\n\n");

        printf("=========================================\n");
        printf("           MENU UTAMA SIMULASI           \n");
        printf("=========================================\n");
        printf(" 1. Pelanggan Baru & Mulai Sesi Belanja  \n");
        printf(" 2. Tampilkan Peta Supermarket (Lihat Saja)\n");
        printf(" 3. Cek Jarak Rak dari Pintu Masuk     \n");
        printf(" 4. Proses Pelanggan Berikutnya di Kasir \n");
        printf(" 5. Tampilkan Antrian Pelanggan          \n");
        printf(" 0. Keluar                               \n");
        printf("=========================================\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);
        printf("\n");

        switch (pilih) {
            case 1: { // Sesi Belanja Interaktif
                infotype pelangganBaru;
                printf("\n============================================\n");
                printf("Pelanggan Baru Datang!\nMasukkan nama pelanggan: ");
                scanf(" %[^\n]", pelangganBaru.nama);
                pelangganBaru.KPelanggan = createKeranjang();
                printf("============================================\n");
                printf("Selamat berbelanja, %s!\n", pelangganBaru.nama);

                int pilihBelanja;
                do {
                    printf("\n--- Sesi Belanja untuk %s ---\n", pelangganBaru.nama);
                    printf("1. Cari & Ambil Barang (berdasarkan ID)\n");
                    printf("2. Tampilkan Peta Supermarket\n");
                    printf("3. Lihat Isi Keranjang\n");
                    printf("0. Selesai Belanja & ke Kasir\n");
                    printf("----------------------------------\n");
                    printf("Pilihan Anda: ");
                    scanf("%d", &pilihBelanja);

                    switch (pilihBelanja) {
                        case 1: { // Cari & Ambil Barang
                            char idBarang[MAX_ID_BARANG];
                            printf("\nMasukkan ID barang yang ingin dicari: ");
                            scanf("%s", idBarang);

                            // Langkah 1: Langsung cari di rak mana barang dengan ID itu berada.
                            TreeNode* rakBarang = cariRakDenganIdBarang(rootSupermarket, idBarang);

                            // Langkah 2: Jika rak ditemukan (tidak NULL), lanjutkan proses.
                            if (rakBarang != NULL) {
                                RakData* dataRak = (RakData*)rakBarang->data;
                                AddressItemNode nodeItemData = SearchItem(dataRak->daftarItem, idBarang);

                                printf("\n>> Barang '%s' ditemukan di lokasi:\n", nodeItemData->dataBarang.namabarang);
                                
                                // Tampilkan info jarak rak tersebut.
                                tampilkanJarakDariEntry(rootSupermarket, dataRak->namaLokasi);

                                // REVISI: Melanjutkan alur untuk mengambil barang.
                                int jumlahAmbil;
                                printf("\nJumlah yang ingin diambil: ");
                                scanf("%d", &jumlahAmbil);

                                // Memanggil fungsi ambilItemDariRak yang sudah diperbaiki.
                                if (ambilItemDariRak(rakBarang, idBarang, jumlahAmbil)) {
                                    for (int i = 0; i < jumlahAmbil; i++) {
                                        pushKeranjang(pelangganBaru.KPelanggan, &nodeItemData->dataBarang);
                                    }
                                    printf(">> BERHASIL: '%s' x%d dimasukkan ke keranjang.\n", nodeItemData->dataBarang.namabarang, jumlahAmbil);
                                }
                            } else {
                                // Jika rakBarang adalah NULL, berarti barang tidak ditemukan.
                                printf(">> Maaf, barang dengan ID '%s' tidak ditemukan di rak manapun.\n", idBarang);
                            }
                            break;
                        }
                        case 2:
                            tampilkanPetaSupermarket(rootSupermarket);
                            break;
                        case 3:
                            printf("\n--- Isi Keranjang %s ---\n", pelangganBaru.nama);
                            displayKeranjang(pelangganBaru.KPelanggan);
                            printf("--------------------------------\n");
                            break;
                        case 0:
                            printf("\n--- %s selesai berbelanja dan menuju kasir. ---\n", pelangganBaru.nama);
                            break;
                        default:
                            printf("Pilihan tidak valid.\n");
                    }
                } while (pilihBelanja != 0);
                
                tambahPelanggan(&antrianPelanggan, pelangganBaru);
                break;
            }
            case 2:
                tampilkanPetaSupermarket(rootSupermarket);
                break;
            case 3: {
                char namaTujuan[50];
                printf("\n--- Cek Jarak dari Pintu Masuk ---\n");
                tampilkanPetaSupermarket(rootSupermarket); 
                printf("Masukkan Lokasi Tujuan (contoh: Rak Sayuran): ");
                scanf(" %[^\n]", namaTujuan);
                tampilkanJarakDariEntry(rootSupermarket, namaTujuan);
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
    
    printf("\nMembersihkan semua memori...\n");
    bebaskanLayoutSupermarket(rootSupermarket);
    printf("Program selesai. Selamat tinggal!\n");

    return 0;
}
