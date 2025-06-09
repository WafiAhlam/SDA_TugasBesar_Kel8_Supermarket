#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Supermarket.h"

// Fungsi helper untuk membuat item kita pindahkan ke sini agar rapi.
// (Tidak ada perubahan di fungsi ini)
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
    // (Tidak ada perubahan di sini)
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
    // Definisi item-item (tidak ada perubahan di sini)
    item itemApel = buatContohItem("APL01", "Apel Fuji Premium", 25000.0);
    item itemSirsak = buatContohItem("SI35K", "Sirsak Sulawesi", 18000.0);
    item itemSemangka = buatContohItem("SE45KA", "Semangka Depok", 34000.0);
    item itemSusu = buatContohItem("SUS01", "Susu UHT Coklat 1L", 18000.0);
    item itemYogurt = buatContohItem("YO84", "Yogurt Cimory", 19000.0);
    item itemSoda = buatContohItem("SO43", "Soda asal Indonesia", 5000.0);
    item itemDaging = buatContohItem("DAG01", "Daging Sapi Sirloin", 120000.0);
    item itemDagong = buatContohItem("DAG02", "Daging Wagyu A6", 5000000.0);
    item itemSapu = buatContohItem("SAP01", "Sapu thailand", 500000.0);
    item itemsendok = buatContohItem("SEN01", "Sendok Emas", 1200000.0);
    item itemgarpu = buatContohItem("GAR02", "Garpu Berlian", 700000.0);
    item itemteflon = buatContohItem("TEF03", "Teflon", 900000.0);
    item itemciki = buatContohItem("LAY01", "Lays", 200000.0);
    item itempermen = buatContohItem("PER02", "Bubble Gum", 200000.0);

    // REVISI: Mencari nama rak & sub-rak yang BENAR sesuai struktur baru dari diagram.
    printf("Mencari node rak untuk penempatan barang...\n");
    TreeNode* subRakSodaJus = cariRakDenganNama(rootSupermarket, "Sub-rak Soda & Jus");
    // FIX: Untuk menaruh Susu & Yogurt, kita taruh di "Rak Minuman" sebagai induknya.
    TreeNode* rakMinuman = cariRakDenganNama(rootSupermarket, "Rak Minuman"); 
    TreeNode* subRakBuah = cariRakDenganNama(rootSupermarket, "Sub-rak Buah Lokal");
    TreeNode* subRakDaging = cariRakDenganNama(rootSupermarket, "Sub-rak Daging Merah");
    TreeNode* subRakMakanan = cariRakDenganNama(rootSupermarket, "Sub-rak Makanan Ringan");
    TreeNode* rakAlatDapur = cariRakDenganNama(rootSupermarket, "Rak Alat Dapur");
    TreeNode* subRakPembersih = cariRakDenganNama(rootSupermarket, "Sub-rak Pembersih");

    // REVISI: Menambahkan item ke rak & sub-rak yang lebih spesifik dan benar.
    printf("Menambahkan item ke rak yang sesuai...\n");

    // Menambahkan buah-buahan ke sub-rak buah
    if (subRakBuah) {
        tambahItemKeRak(subRakBuah, itemApel, 100);
        tambahItemKeRak(subRakBuah, itemSirsak, 30);
        tambahItemKeRak(subRakBuah, itemSemangka, 23);
    }
    
    // Menambahkan minuman ke rak dan sub-rak yang sesuai
    if (rakMinuman) {
        tambahItemKeRak(rakMinuman, itemYogurt, 38);
        tambahItemKeRak(rakMinuman, itemSusu, 80);
    }
    if (subRakSodaJus) tambahItemKeRak(subRakSodaJus, itemSoda, 45);

    // Menambahkan daging ke sub-rak daging
    if (subRakDaging) {
        tambahItemKeRak(subRakDaging, itemDagong, 3);
        tambahItemKeRak(subRakDaging, itemDaging, 30);
    }
    
    // Menambahkan makanan ringan ke sub-raknya
    if (subRakMakanan) {
        tambahItemKeRak(subRakMakanan, itempermen, 30);
        tambahItemKeRak(subRakMakanan, itemciki, 30);
    }

    // Menambahkan peralatan dapur ke rak utamanya
    if (rakAlatDapur) {
        tambahItemKeRak(rakAlatDapur, itemsendok, 30);
        tambahItemKeRak(rakAlatDapur, itemgarpu, 30);
        tambahItemKeRak(rakAlatDapur, itemteflon, 30);
    }

    // Menambahkan peralatan rumah tangga ke sub-rak pembersih
    if (subRakPembersih) tambahItemKeRak(subRakPembersih, itemSapu, 30); 
    
    printf("\nSetup Supermarket Selesai. Katalog barang telah dimuat.\n");
    tampilkanPetaSupermarket(rootSupermarket);

    return rootSupermarket;
}
