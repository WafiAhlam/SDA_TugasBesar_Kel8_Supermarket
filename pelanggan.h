#include <stdio.h>
#include <stdlib.h>
#include "Keranjang.h"
#define MAX_ID_PELANGGAN 40
#ifndef PELANGGAN_H
#define PELANGGAN_H

typedef struct Pelanggan {
    char nama[50];
    Keranjang* KPelanggan;
} Pelanggan;

Pelanggan* CreatePelanggan (const char* id);
void FreePelanggan (Pelanggan* pelanggan);






#endif