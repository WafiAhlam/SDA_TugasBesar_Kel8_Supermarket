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

// ... (sisa deklarasi fungsi)
void menuPelanggan(TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir);
void saveCustomerReceipt(Pelanggan p);
void sesiBelanjaInteraktif(Pelanggan* pelanggan, TreeNode* rootLayout, RakBTree* rootAVL, RakTumpukan* rakPromosi, AntrianKasir* antrianKasir);
void menuAmbilDariRakFisik(KeranjangBelanja* keranjang, TreeNode* rootLayout, RakBTree* rootAVL);
void menuAmbilDariRakPromosi(KeranjangBelanja* keranjang, RakTumpukan* rakPromosi);
void menuMasukAntrian(AntrianKasir* antrian, Pelanggan* pelanggan);
void saveCustomerReceipt(Pelanggan p); // Definisinya ada di bawah
#endif