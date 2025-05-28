#include <stdio.h>
#include <string.h>
#include "items.h"
#include <stdlib.h>

AddressItemNode* CreateNode (item barang) {
    AddressItemNode newNode = (AddressItemNode)malloc(sizeof(ItemNode));
    if (newNode == NULL) {
        perror ("Gagal alokasi node baru");
        return NULL;
    }
    newNode->dataBarang = barang;
    newNode->next = NULL;
    return newNode;
}
 
void insertNode (AddressItemNode *head, item barang) {


}

void displayItem (const item* barang) {


}