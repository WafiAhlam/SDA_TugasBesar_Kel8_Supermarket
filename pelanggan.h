#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <stdio.h>
#include <stdlib.h>
#include "Keranjang.h"
#include "TreeRak.h"


typedef struct Pelanggan {
    char nama[50];
    Keranjang* KPelanggan;
} Pelanggan;

void pelangganMenu();
void sesiBelanjaInteraktif(TreeNode* rootSupermarket);
void menuPelanggan(TreeNode* rootSupermarket);
void saveCustomerReceipt(Pelanggan p);

#endif