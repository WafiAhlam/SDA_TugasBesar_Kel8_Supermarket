#include "items.h" // Pastikan ini meng-include header yang baru

// Fungsi untuk membuat Listitem kosong
void CreateListItem(Listitem *L) {
    L->head = Nil;
    L->tail = Nil;
}

// Fungsi untuk memeriksa apakah Listitem kosong
boolean ListItemEmpty(Listitem L) {
    return (L.head == Nil);
}

// Fungsi untuk membuat node item baru
AddressItemNode CreateItemNode(Produk produk, int stock) { // Menerima Produk
    AddressItemNode newNode = (AddressItemNode)malloc(sizeof(ItemNode));
    if (newNode != Nil) {
        newNode->dataProduk = produk; // Salin seluruh struktur Produk
        newNode->stock = stock;
        newNode->next = Nil;
    }
    return newNode;
}

// Fungsi untuk menambahkan item ke akhir list
void InsertLastItem(Listitem *L, Produk produk, int stock) { // Menerima Produk
    AddressItemNode P = CreateItemNode(produk, stock);
    if (P != Nil) {
        if (ListItemEmpty(*L)) {
            L->head = P;
            L->tail = P;
        } else {
            L->tail->next = P;
            L->tail = P;
        }
    }
}

// Fungsi untuk mencari item berdasarkan ID produk
AddressItemNode SearchItem(Listitem L, const char* idProdukCari) { // Menerima idProduk (string)
    AddressItemNode P = L.head;
    while (P != Nil) {
        if (strcmp(P->dataProduk.idProduk, idProdukCari) == 0) { // Bandingkan idProduk
            return P; // Item ditemukan
        }
        P = P->next;
    }
    return Nil; // Item tidak ditemukan
}

void DeallocateListItem(Listitem *L) {
    AddressItemNode P = L->head;
    while (P != Nil) {
        AddressItemNode temp = P;
        P = P->next;
        free(temp);
    }
    L->head = Nil;
    L->tail = Nil;
}

// Fungsi untuk menampilkan semua item dalam sebuah list (rak)
void PrintListItem(Listitem L) {
    AddressItemNode P = L.head;
    if (ListItemEmpty(L)) {
        printf("Rak ini kosong.\n");
    } else {
        int i = 1;
        printf("----------------------------------\n");
        printf("Daftar Barang di Lokasi ini:\n");
        while (P != Nil) {
            printf("%d. %s (ID: %s, Stok: %d, Harga: %.0f)\n",
                     i, P->dataProduk.nama, P->dataProduk.idProduk, P->stock, P->dataProduk.harga); // Akses dataProduk
            i++;
            P = P->next;
        }
        printf("----------------------------------\n");
    }
}

// Fungsi untuk menampilkan detail satu item (tidak banyak berubah)
void displayItem(const Produk* produk) { // Menerima pointer ke Produk
    printf("ID: %s, Nama: %s, Harga: %.2f",
           produk->idProduk, produk->nama, produk->harga);
}

boolean kurangiStokItem(Listitem* L, const char* idProduk, int jumlah) {
    if (L == NULL) return FALSE;

    AddressItemNode itemNode = SearchItem(*L, idProduk);
    if (itemNode == NULL) {
        printf("Error: Produk dengan ID '%s' tidak ditemukan di rak ini.\n", idProduk);
        return FALSE;
    }

    if (itemNode->stock < jumlah) {
        printf("Error: Stok '%s' di rak tidak mencukupi. Tersedia: %d, Diminta: %d.\n",
               itemNode->dataProduk.nama, itemNode->stock, jumlah);
        return FALSE;
    }

    // Kurangi stok jika semua kondisi terpenuhi
    itemNode->stock -= jumlah;
    return TRUE;
}