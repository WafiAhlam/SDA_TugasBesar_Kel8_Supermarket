// File: pelanggan.h (REVISED)
#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <stdio.h>
#include <stdlib.h>
#include "Keranjang.h" 
#include "TreeRak.h"
#include "tumpukan.h"
#include "Kasir.h"
#include "tipedata.h"

/*
typedef struct Pelanggan {
    char nama[50];
    char waktuDatang[50];
    KeranjangBelanja* keranjang;
} Pelanggan;
*/

/*
IS: Sistem berada di menu utama. Semua struktur data global (rootLayout, rootAVL, rakTumpukan, antrianKasir) telah diinisialisasi.
FS: Sesi pelanggan telah berakhir, baik dengan checkout (data pelanggan masuk ke antrian) atau dibatalkan. Program kembali ke loop menu utama.

Creator: Marelly Salsa Kasih Risky
*/
void menuPelanggan(TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir);

/*
IS: Data Pelanggan p, termasuk keranjang belanjanya yang sudah final, tersedia di memori.
FS: Sebuah file teks (.txt) struk belanja telah dibuat di disk. File ini berisi rincian pembelian dari keranjang belanja Pelanggan p. State data di dalam memori program tidak berubah.

Creator: Marelly Salsa Kasih Risky
*/
void saveCustomerReceipt(Pelanggan p);

/*
IS: Struct Pelanggan telah dibuat dengan nama dan sebuah KeranjangBelanja yang masih kosong. Semua data global supermarket tersedia.
FS: Sesi belanja interaktif untuk pelanggan tersebut berakhir. Keranjang belanja telah dimasukkan ke dalam antrian kasir (jika checkout) atau telah dihancurkan (jika dibatalkan).

Creator: Marelly Salsa Kasih Risky
*/
void sesiBelanjaInteraktif(Pelanggan* pelanggan, TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakPromosi, AntrianKasir* antrianKasir);

/*
IS: Pelanggan sedang dalam sesi belanja. keranjang, rootLayout, dan rootAVL berada dalam keadaan sebelum item diambil.
FS: Jika produk valid dan stok mencukupi, stok produk di dalam rootLayout (pada rak yang dipilih) telah berkurang, dan produk tersebut ditambahkan ke keranjang. Jika gagal, keadaan struktur data tidak berubah dan sebuah pesan eror ditampilkan.

Creator: Wafi Ahlam Rizqulloh
*/
void menuAmbilDariRakFisik(KeranjangBelanja* keranjang, TreeNode* rootLayout, RakBTree* rootAVL);

/*
IS: Pelanggan sedang dalam sesi belanja. keranjang dan rakPromosi (Stack) berada dalam keadaan sebelum item diambil.
FS: Jika rakPromosi tidak kosong, item teratasnya telah dihapus (di-pop) dan ditambahkan ke keranjang belanja. Jika rakPromosi kosong, keadaan struktur data tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void menuAmbilDariRakPromosi(KeranjangBelanja* keranjang, RakTumpukan* rakPromosi);

/*
IS: Pelanggan telah selesai memilih barang dan memiliki KeranjangBelanja. antrianKasir berada dalam keadaan sebelum pelanggan ini masuk.
FS: Data Pelanggan (nama dan keranjangnya) telah ditambahkan ke akhir antrianKasir (enqueued). Jumlah pelanggan di antrian bertambah.

Creator: Wafi Ahlam Rizqulloh
*/
void menuMasukAntrian(AntrianKasir* antrian, Pelanggan* pelanggan);
 
/*
void menuPelanggan(TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir);
void saveCustomerReceipt(Pelanggan p);
void sesiBelanjaInteraktif(Pelanggan* pelanggan, TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakPromosi, AntrianKasir* antrianKasir);
void menuAmbilDariRakFisik(KeranjangBelanja* keranjang, TreeNode* rootLayout, RakBTree* rootAVL);
void menuAmbilDariRakPromosi(KeranjangBelanja* keranjang, RakTumpukan* rakPromosi);
void menuMasukAntrian(AntrianKasir* antrian, Pelanggan* pelanggan);
void saveCustomerReceipt(Pelanggan p); // Definisinya ada di bawah
*/
#endif