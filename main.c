#include <stdio.h>
#include <stdlib.h>
#include "linked.h"
#include "Queue.h"
#include "Kasir.h"
#include "stack2.h"
#include "Treerak.h"
#include "Keranjang.h"
#include "pelanggan.h"

int main() 
{

    //keranjang kasih 
    Keranjang* keranjang = createKeranjang();
  
    char inputID[MAX_ID_BARANG];
    printf("Masukkan ID barang yang ingin dibeli: ");
    scanf("%s", inputID);

    AddressItemNode found = SearchItem(listMakanan, inputID);
    if (found != NULL) {
        pushKeranjang(keranjang, &found->dataBarang);
        printf("Barang berhasil dimasukkan ke keranjang.\n");
    } else {
        printf("Barang tidak ditemukan.\n");
    }

    displayKeranjang(keranjang);

    printf("\nMengeluarkan barang terakhir dari keranjang...\n");
    item* dikeluarkan = popKeranjang(keranjang);
    if (dikeluarkan != NULL) {
        printf("Barang '%s' dikeluarkan dari keranjang.\n", dikeluarkan->namabarang);
    }

    displayKeranjang(keranjang);

    double total = getTotalHargaKeranjang(keranjang);
    printf("Total belanja sekarang: %.2f\n", total);

    clearKeranjang(keranjang);
    free(keranjang);

    //Queue Chinta
    Queue antrianPelanggan;
    CreateQueue(&antrianPelanggan);

    int pilih;
    do {
        printf("\n=== Simulasi Kasir ===\n");
        printf("1. Tambah pelanggan ke antrian\n");
        printf("2. Proses pelanggan berikutnya\n");
        printf("3. Tampilkan antrian\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: {
                infotype pelangganBaru;

                printf("Masukkan nama pelanggan: ");
                scanf(" %[^\n]", pelangganBaru.nama);

                pelangganBaru.KPelanggan = createKeranjang();

                char tambahBarang;
                do {
                    char idBarang[MAX_ID_BARANG];
                    printf("Masukkan ID barang: ");
                    scanf("%s", idBarang);

                    AddressItemNode found = SearchItem(listMakanan, idBarang);
                    if (found != NULL) {
                        pushKeranjang(pelangganBaru.KPelanggan, &found->dataBarang);
                        printf("Barang berhasil dimasukkan ke keranjang.\n");
                    } else {
                        printf("Barang tidak ditemukan.\n");
                    }

                    printf("Tambah barang lagi? (y/n): ");
                    scanf(" %c", &tambahBarang);
                } while (tambahBarang == 'y' || tambahBarang == 'Y');

                tambahPelanggan(&antrianPelanggan, pelangganBaru);
                break;
            }
            case 2:
                prosesPelanggan(&antrianPelanggan);
                break;
            case 3:
                tampilkanAntrian(antrianPelanggan);
                break;
            case 0:
                printf("Keluar dari program...\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilih != 0);

    return 0;
}