#include <stdio.h>
#include "Kasir.h"
#include "Keranjang.h"

// Menambahkan pelanggan ke antrian
void tambahPelanggan(Queue* Q, infotype pelanggan) {
    enqueue(Q, pelanggan);
    printf("Pelanggan %s ditambahkan ke antrian.\n", pelanggan.nama);
}

// Memproses pelanggan terdepan di antrian
void prosesPelanggan(Queue* Q) {
    if (isQueueEmpty(*Q)) {
    printf("Antrian kosong, tidak ada pelanggan yang diproses.\n");
    return;
    }

    infotype pelanggan;
    if (dequeue(Q, &pelanggan)) {
    double total = getTotalHargaKeranjang(pelanggan.KPelanggan);
    printf("Pelanggan %s telah dilayani.\n", pelanggan.nama);
    printf("Total belanja: Rp %.2f\n", total);

    saveCustomerReceipt(pelanggan); // Simpan struk

    // Hapus keranjang dari memori
    if (pelanggan.KPelanggan != NULL) {
        freeKeranjang(pelanggan.KPelanggan);
        free(pelanggan.KPelanggan);
        }
    }
}

// Menampilkan seluruh antrian
void tampilkanAntrian(Queue Q) {
printQueue(Q);
}
