#ifndef Kasir_H
#include "Pelanggan.h"
typedef struct NodeAntrian {
    NodeAntrian* next;
    Pelanggan* dataP;
} NodeAntrian;

typedef struct AntrianKasir {
    NodeAntrian* front;
    NodeAntrian* rear;
    int count;
} AntrianKasir;

AntrianKasir* CreateKasir();
int isKasirEmpty (const AntrianKasir* antrian);
void clearKasir (AntrianKasir* antrian);











#endif