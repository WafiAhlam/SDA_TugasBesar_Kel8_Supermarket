#include <stdio.h>
#include <stdlib.h>
#define BOOLEAN
#ifndef items_H
#define MAX_ID_BARANG 20
#define MAX_NAMA_BARANG 50

typedef struct ItemNode {
    int stock;
    int harga;
    ItemNode* next;
    item dataBarang;
} ItemNode;

typedef ItemNode *AddressItemNode;
typedef struct Listitem *address;
typedef struct Listitem {
    char type[50];
    ItemNode* head;
    ItemNode* tail;
} Listitem;
 
typedef struct item {
    char idbarang [MAX_ID_BARANG];
    char namabarang [MAX_NAMA_BARANG];
    double harga;
} item;

AddressItemNode CreateNode (item barang);
void insertNode (AddressItemNode *head, item barang);
void displayItem (const item* barang );


#endif