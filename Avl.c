
#include "avl.h"
#include <string.h>

int height(RakBTree *N) {
    if (N == NULL) return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

RakBTree* newRakBTree(Produk produkBaru) {
    RakBTree* node = (RakBTree*) malloc(sizeof(RakBTree));
    node->info = produkBaru;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(RakBTree *N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

RakBTree *rightRotate(RakBTree *y) {
    RakBTree *x = y->left;
    RakBTree *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

RakBTree *leftRotate(RakBTree *x) {
    RakBTree *y = x->right;
    RakBTree *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}


RakBTree* insertProduk(RakBTree* node, Produk produk) {
    if (node == NULL) return newRakBTree(produk);

    int comparison = strcmp(produk.idProduk, node->info.idProduk);

    if (comparison < 0)
        node->left = insertProduk(node->left, produk);
    else if (comparison > 0)
        node->right = insertProduk(node->right, produk);
    else {
        printf("Info: Produk dengan ID %s sudah ada, stok diperbarui.\n", produk.idProduk);
        node->info.stok += produk.stok; // Contoh: jika ID sama, tambahkan stok
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && strcmp(produk.idProduk, node->left->info.idProduk) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(produk.idProduk, node->right->info.idProduk) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(produk.idProduk, node->left->info.idProduk) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(produk.idProduk, node->right->info.idProduk) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Fungsi searchProduk Anda sudah benar
RakBTree *searchProduk(RakBTree *root, const char* idProdukCari) {
    if (root == NULL || strcmp(idProdukCari, root->info.idProduk) == 0)
        return root;
    
    if (strcmp(idProdukCari, root->info.idProduk) < 0)
        return searchProduk(root->left, idProdukCari);
    
    return searchProduk(root->right, idProdukCari);
}


RakBTree* minValueNode(RakBTree* node) {
    RakBTree* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}


RakBTree* deleteProduk(RakBTree* root, const char* idProdukHapus) {
    // 1. Lakukan penghapusan BST standar
    if (root == NULL) return root;

    int cmp = strcmp(idProdukHapus, root->info.idProduk);

    if (cmp < 0)
        root->left = deleteProduk(root->left, idProdukHapus);
    else if (cmp > 0)
        root->right = deleteProduk(root->right, idProdukHapus);
    else { // Node yang akan dihapus ditemukan
        // Node dengan satu anak atau tanpa anak
        if ((root->left == NULL) || (root->right == NULL)) {
            RakBTree* temp = root->left ? root->left : root->right;
            
            // Kasus tanpa anak
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { // Kasus satu anak
                // Salin isi dari anak yang tidak null
                *root = *temp; 
            }
            free(temp);
        } else {
            // Node dengan dua anak: dapatkan inorder successor (terkecil di subtree kanan)
            RakBTree* temp = minValueNode(root->right);
            // Salin data inorder successor ke node ini
            root->info = temp->info;
            // Hapus inorder successor
            root->right = deleteProduk(root->right, temp->info.idProduk);
        }
    }

    // Jika tree hanya punya satu node lalu dihapus, root akan jadi NULL
    if (root == NULL) return root;

    // 2. Perbarui tinggi
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Dapatkan balance factor
    int balance = getBalance(root);

    /** REVISI KONDISI BALANCING SETELAH DELETE **/
    // Kondisi untuk balancing setelah delete sedikit berbeda dari insert.
    // Kita perlu memeriksa balance factor dari anak-anaknya juga.
    // getBalance(root->left) >= 0 mencakup kasus Left-Left dan kasus di mana subtree kiri seimbang.
    
    // Kasus Kiri-Kiri (Left Left Case)
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Kasus Kiri-Kanan (Left Right Case)
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Kasus Kanan-Kanan (Right Right Case)
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Kasus Kanan-Kiri (Right Left Case)
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inOrderProduk(RakBTree *root) {
    if (root != NULL) {
        inOrderProduk(root->left);
        printf("  - ID: %-10s | Nama: %-25s | Harga: %-10.0f | Stok Global: %d\n",
               root->info.idProduk, root->info.nama, root->info.harga, root->info.stok);
        inOrderProduk(root->right);
    }
}


void deleteTree(RakBTree **node) {
    if (*node == NULL) return;
    deleteTree(&((*node)->left));
    deleteTree(&((*node)->right));
    free(*node);
    *node = NULL; // Set pointer asli ke NULL
}

// Bentukan dari node sejenis yang dapat di rotasi 