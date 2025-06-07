#include <stdio.h>
#include <stdlib.h>
#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "treerak.h"  // Untuk mengakses struktur rak
#include "items.h" // Untuk mengakses info item
#include "Kasir.h"

// Struktur utama Supermarket yang mungkin menampung tree rak dan antrian kasir
typedef struct {
    TreeRak* sistemRak;
    // Mungkin ada beberapa antrian kasir, bisa berupa array AntrianKasir*
    AntrianKasir** daftarKasir;
    int jumlahKasir;
    // Daftar master semua item yang tersedia di supermarket (opsional)
    // LinkedListMasterItem* masterItemList;
} Supermarket;

// Fungsi-fungsi Admin/Supermarket
// Inisialisasi Supermarket
Supermarket* initSupermarket(int jumlahKasir);

// Admin: Memeriksa stok barang di rak tertentu
int ViewStokBarang(const NodeRak* rak, const char* idBarang);

// Menampilkan harga item (bisa mencari di rak atau master list)
double getHargaItem(const TreeRak* rakSystem, const char* idBarang);

// Pelanggan selesai belanja dan masuk antrian kasir
void pelangganMasukAntrian(Supermarket* supermarket, Pelanggan* pelanggan, int nomorKasir);

// Proses checkout pelanggan dari kasir
double prosesCheckout(AntrianKasir* kasir); // Mengembalikan total belanjaan

// Menemukan rak terdekat (implementasi tergantung bagaimana 'jarakDariEntry' digunakan)
NodeRak* findRakTerdekat(const TreeRak* rakSystem); // Ini contoh, detailnya perlu dirancang

// Membersihkan seluruh memori Supermarket
void closeSupermarket(Supermarket* supermarket);

// Memastika bahwa terdapat rak di dalam rak Node yang sudah di inisialisasi
// Sebenenarnya tidak begitu penting unutk digunakan dalam program ini hanya saja agar secara realistis dapat di buat dala

#endif