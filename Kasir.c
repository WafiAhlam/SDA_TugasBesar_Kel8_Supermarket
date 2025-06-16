#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kasir.h"
#include "pelanggan.h"
#include "BOOLEAN.H"

// Membuat antrian kasir baru yang kosong
AntrianKasir* createAntrian() {
    AntrianKasir* antrian = (AntrianKasir*) malloc(sizeof(AntrianKasir));
    if (antrian == NULL) {
        perror("Gagal alokasi memori untuk AntrianKasir");
        return NULL;
    }
    antrian->head = NULL;
    antrian->tail = NULL;
    antrian->jumlahPelanggan = 0;
    return antrian;
}

// Memeriksa apakah antrian kosong
boolean isAntrianKosong(AntrianKasir* antrian) {
    return (antrian->head == NULL);
}

// Menambahkan pelanggan ke akhir antrian (enqueue)
void enqueuePelanggan(AntrianKasir* antrian, Pelanggan pelanggan) {
    AntrianNode* newNode = (AntrianNode*) malloc(sizeof(AntrianNode));
    if (newNode == NULL) {
        perror("Gagal alokasi memori untuk AntrianNode");
        return;
    }
    newNode->dataPelanggan = pelanggan;
    newNode->next = NULL;

    if (isAntrianKosong(antrian)) {
        // Jika antrian kosong, head dan tail menunjuk ke node baru
        antrian->head = newNode;
        antrian->tail = newNode;
    } else {
        // Jika tidak, tambahkan node baru di belakang tail
        antrian->tail->next = newNode;
        antrian->tail = newNode; // Update tail
    }
    antrian->jumlahPelanggan++;
    printf("\n%s telah masuk ke dalam antrian.\n", pelanggan.nama);
}

// Mengeluarkan pelanggan dari depan antrian (dequeue)
boolean dequeuePelanggan(AntrianKasir* antrian, Pelanggan* pelangganDilayani) {
    if (isAntrianKosong(antrian)) {
        printf("Antrian kosong, tidak ada pelanggan untuk dilayani.\n");
        return FALSE;
    }

    AntrianNode* temp = antrian->head;
    *pelangganDilayani = temp->dataPelanggan; // Salin data pelanggan yang dilayani

    antrian->head = antrian->head->next; // Geser head ke pelanggan berikutnya
    free(temp); // Hapus node pelanggan yang sudah dilayani

    if (antrian->head == NULL) {
        // Jika setelah dequeue antrian menjadi kosong, set tail juga ke NULL
        antrian->tail = NULL;
    }
    antrian->jumlahPelanggan--;
    return TRUE;
}

// Menampilkan semua pelanggan yang sedang mengantri
void displayAntrian(AntrianKasir* antrian) {
    printf("\n--- ANTRIAN KASIR SAAT INI ---\n");
    if (isAntrianKosong(antrian)) {
        printf("Antrian kosong.\n");
    } else {
        printf("Total Pelanggan: %d\n", antrian->jumlahPelanggan);
        printf("Urutan: (Depan) ");
        AntrianNode* current = antrian->head;
        while (current != NULL) {
            printf("[%s] -> ", current->dataPelanggan.nama);
            current = current->next;
        }
        printf("(Belakang)\n");
    }
    printf("-----------------------------\n");
}

// Menghancurkan antrian dan membebaskan memori
void destroyAntrian(AntrianKasir** antrian) {
    // Implementasi ini harus menghancurkan semua keranjang yang mungkin masih ada di antrian
    // Untuk saat ini, kita asumsikan keranjang sudah di-handle saat dequeue
    // ... (kode untuk free semua node) ...
    free(*antrian);
    *antrian = NULL;
}