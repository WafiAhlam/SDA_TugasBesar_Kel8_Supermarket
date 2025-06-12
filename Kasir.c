#include <stdio.h>
#include "queue.h"
#include "keranjang.h"  

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

    // double totalBelanja = getTotalHargaKeranjang(pelanggan.KPelanggan);

    //printf("Pelanggan %s telah dilayani. Total belanja: %.2f\n", pelanggan.nama, totalBelanja);
}

// Fungsi tampilkan antrian
void tampilkanAntrian(Queue Q) 
{
    PrintQueue(Q);
}
