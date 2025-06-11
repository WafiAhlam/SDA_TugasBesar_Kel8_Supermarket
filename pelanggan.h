#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <stdio.h>
#include <stdlib.h>
#include "Keranjang.h"

typedef struct Pelanggan {
    char nama[50];
    Keranjang* KPelanggan;
} Pelanggan;

#endif