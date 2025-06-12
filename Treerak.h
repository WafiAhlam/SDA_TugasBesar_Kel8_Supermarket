#ifndef TREERAK_H
#define TREERAK_H

#include "items.h"
#include "NonBinaryTree.h"
#define MAXPATH 100
typedef struct {
    char* namaLokasi;
    int jarakDariParent;
    Listitem daftarItem;
} RakData;

// DEKLARASI FUNGSI-FITUR SUPERMARKET
TreeNode* buatLayoutSupermarket();
void tampilkanPetaSupermarket(TreeNode* root);
void cariRuteDanJarak(TreeNode* root, const char* namaAwal, const char* namaTujuan);
void tambahItemKeRak(TreeNode* rakTujuan, item barang, int stock);
TreeNode* cariRakDenganNama(TreeNode* root, const char* namaRak);
boolean ambilItemDariRak(TreeNode* root, const char* idBarang, int jumlah);
void bebaskanLayoutSupermarket(TreeNode* root);
void tampilkanJarakDariEntry(TreeNode* root, const char* namaTujuan);
AddressItemNode findItemDataOnTree(TreeNode* root, const char* idBarang);
TreeNode* cariRakDenganIdBarang(TreeNode* root, const char* idBarang);
void setParentPointersRecursive(TreeNode* node);

#endif 
