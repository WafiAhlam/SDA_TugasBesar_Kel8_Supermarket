#include <stdio.h>
#include <stdlib.h>
#include "Keranjang.h"
#define MAX_ID_PELANGGAN 40
#ifndef Pelanggan_H

typedef struct Pelanggan {
    char idpelanggan [MAX_ID_PELANGGAN];
    Keranjang* KPelanggan;
} Pelanggan;

Pelanggan* CreatePelanggan (const char* id);
void FreePelanggan (Pelanggan* pelanggan);






#endif