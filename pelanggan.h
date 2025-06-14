// File: pelanggan.h (REVISED)
#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <stdio.h>
#include <stdlib.h>
#include "Keranjang.h" 
#include "TreeRak.h"
#include "tumpukan.h"

typedef struct Pelanggan {
    char nama[50];
    char waktuDatang[50];
    KeranjangBelanja* keranjang;
} Pelanggan;

// ... (sisa deklarasi fungsi)
void menuPelanggan(TreeNode* rootSupermarket, RakBTree** rootAVL, RakTumpukan* rakTumpukan); // Perlu akses ke AVL juga
void saveCustomerReceipt(Pelanggan p);

#endif