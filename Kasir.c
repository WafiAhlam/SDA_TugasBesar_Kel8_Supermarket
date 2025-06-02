#include <stdio.h>
#include "queue.h"
#include "keranjang.h"  

// Statistik kasir
double totalPemasukan = 0;
int totalPelangganDilayani = 0;

// Fungsi tambah pelanggan ke antrian
void tambahPelanggan(Queue *Q, infotype pelanggan) 
{
    EnQueue(Q, pelanggan);
    printf("Pelanggan %s ditambahkan ke antrian.\n", pelanggan.nama);
}

// Fungsi proses pelanggan di depan antrian
void prosesPelanggan(Queue *Q) 
{
    if (is_Empty(*Q)) 
    {
        printf("Antrian kosong, tidak ada pelanggan yang diproses.\n");
        return;
    }

    infotype pelanggan;
    deQueue(Q, &pelanggan);

    double totalBelanja = getTotalHargaKeranjang(pelanggan.KPelanggan);

    printf("Pelanggan %s telah dilayani. Total belanja: %.2f\n", pelanggan.nama, totalBelanja);

    totalPemasukan += totalBelanja;
    totalPelangganDilayani++;
}

// Fungsi tampilkan antrian
void tampilkanAntrian(Queue Q) 
{
    PrintQueue(Q);
}

// Fungsi tampilkan statistik kasir
// void tampilkanStatistik() {
//     printf("Total pemasukan: %d\n", totalPemasukan);
//     printf("Total pelanggan dilayani: %d\n", totalPelangganDilayani);
//     if (totalPelangganDilayani > 0) {
//         printf("Rata-rata belanja per pelanggan: %.2f\n",
//                (float)totalPemasukan / totalPelangganDilayani);
//     } else {
//         printf("Belum ada pelanggan yang dilayani.\n");
//     }
// }
