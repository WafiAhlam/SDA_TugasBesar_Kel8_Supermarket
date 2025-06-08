#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Supermarket.h"

// Fungsi helper untuk membuat item kita pindahkan ke sini agar rapi.
item buatContohItem(const char* id, const char* nama, double harga) {
    item newItem;
    strncpy(newItem.idbarang, id, sizeof(newItem.idbarang) - 1);
    newItem.idbarang[sizeof(newItem.idbarang) - 1] = '\0';
    
    strncpy(newItem.namabarang, nama, sizeof(newItem.namabarang) - 1);
    newItem.namabarang[sizeof(newItem.namabarang) - 1] = '\0';

    newItem.harga = harga;
    return newItem;
}


// Implementasi dari fungsi utama setup
TreeNode* setupAndPopulateSupermarket() {
    // ==========================================================
    // BAGIAN 1: MEMBUAT LAYOUT DASAR
    // ==========================================================
    printf("Selamat Datang di Program Simulasi Supermarket!\n");
    // Memanggil fungsi dari TreeRak.c untuk membuat kerangka pohon
    TreeNode* rootSupermarket = buatLayoutSupermarket();
    if (rootSupermarket == NULL) {
        fprintf(stderr, "Gagal membuat layout supermarket. Program berhenti.\n");
        return NULL;
    }

    // ==========================================================
    // BAGIAN 2: MENGISI RAK DENGAN KATALOG BARANG
    // ==========================================================
    printf("\n--- Mengisi Barang (Katalog) ke Rak ---\n");
    item itemApel = buatContohItem("APL01", "Apel Fuji Premium", 25000.0);
    item itemSirsak = buatContohItem("SI35K", "Sirsak Sulawesi", 18000.0);
    item itemSemangka = buatContohItem("SE45KA", "Semangka Depok", 34000.0);
    item itemSusu = buatContohItem("SUS01", "Susu UHT Coklat 1L", 18000.0);
    item itemYogurt = buatContohItem("YO84", "Yogurt Cimory", 19000.0);
    item itemSoda = buatContohItem("SO43", "Soda asal Indonesia", 5000.0);
    item itemDaging = buatContohItem("DAG01", "Daging Sapi Sirloin", 120000.0);
    item itemDagong = buatContohItem("DAG02", "Daging Wagyu A6", 5000000.0);

    // Cari rak tujuan
    TreeNode* rakBuah = cariRakDenganNama(rootSupermarket, "Sub-rak Buah");
    TreeNode* rakMinuman = cariRakDenganNama(rootSupermarket, "Rak Minuman");
    TreeNode* rakDaging = cariRakDenganNama(rootSupermarket, "Rak Daging & Ikan");

    // Tambahkan item ke rak
    if (rakBuah) tambahItemKeRak(rakBuah, itemApel, 100);
    if (rakBuah) tambahItemKeRak(rakBuah, itemSirsak, 30);
    if (rakBuah) tambahItemKeRak(rakBuah, itemSemangka, 23);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemYogurt, 38);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemSoda, 45);
    if (rakMinuman) tambahItemKeRak(rakMinuman, itemSusu, 80);
    if (rakDaging) tambahItemKeRak(rakDaging, itemDagong, 3);
    if (rakDaging) tambahItemKeRak(rakDaging, itemDaging, 30);
    
    printf("\nSetup Supermarket Selesai. Katalog barang telah dimuat.\n");
    tampilkanPetaSupermarket(rootSupermarket);

    return rootSupermarket;
}
