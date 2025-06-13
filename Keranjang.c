#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Keranjang.h"

// Fungsi internal untuk mencari produk berdasarkan ID di keranjang.
// Mengembalikan pointer ke KeranjangNode jika ditemukan, NULL jika tidak.
static KeranjangNode* cariProdukDiKeranjang(KeranjangBelanja* keranjang, const char* idProduk) {
    KeranjangNode* current = keranjang->head;
    while (current != NULL) {
        if (strcmp(current->infoProduk.idProduk, idProduk) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Membuat dan mengembalikan pointer ke keranjang belanja baru yang kosong.
KeranjangBelanja* createKeranjang() {
    KeranjangBelanja* keranjang = (KeranjangBelanja*) malloc(sizeof(KeranjangBelanja));
    if (keranjang == NULL) {
        perror("Gagal alokasi memori untuk KeranjangBelanja");
        return NULL;
    }
    keranjang->head = NULL;
    keranjang->jumlahItemUnik = 0;
    keranjang->totalHarga = 0.0;
    return keranjang;
}

// Memeriksa apakah keranjang belanja kosong.
boolean isKeranjangEmpty(KeranjangBelanja* keranjang) {
    return keranjang->head == NULL;
}

// Menambahkan produk ke keranjang.
void tambahProdukKeKeranjang(KeranjangBelanja* keranjang, Produk produk, int kuantitas) {
    if (keranjang == NULL || kuantitas <= 0) return;

    KeranjangNode* itemAda = cariProdukDiKeranjang(keranjang, produk.idProduk);

    if (itemAda != NULL) {
        // Jika produk sudah ada, cukup tambah kuantitasnya
        itemAda->kuantitas += kuantitas;
        printf("-> Kuantitas '%s' di keranjang ditambah %d.\n", produk.nama, kuantitas);
    } else {
        // Jika produk belum ada, buat node baru dan tambahkan di awal list
        KeranjangNode* newNode = (KeranjangNode*) malloc(sizeof(KeranjangNode));
        if (newNode == NULL) {
            perror("Gagal alokasi memori untuk KeranjangNode");
            return;
        }
        newNode->infoProduk = produk;
        newNode->kuantitas = kuantitas;
        
        newNode->next = keranjang->head;
        keranjang->head = newNode;
        keranjang->jumlahItemUnik++;
        printf("-> Produk '%s' ditambahkan ke keranjang.\n", produk.nama);
    }

    // Perbarui total harga
    keranjang->totalHarga += (produk.harga * kuantitas);
}

// Helper function untuk menghapus node sepenuhnya dari linked list
static void hapusNodeSepenuhnya(KeranjangBelanja* keranjang, const char* idProduk) {
    KeranjangNode* current = keranjang->head;
    KeranjangNode* prev = NULL;

    while (current != NULL && strcmp(current->infoProduk.idProduk, idProduk) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return; // Seharusnya tidak terjadi jika dipanggil dari kurangiProduk

    // Update total harga sebelum menghapus
    keranjang->totalHarga -= (current->infoProduk.harga * current->kuantitas);
    
    if (prev == NULL) { // Menghapus head
        keranjang->head = current->next;
    } else { // Menghapus di tengah atau akhir
        prev->next = current->next;
    }

    free(current);
    keranjang->jumlahItemUnik--;
    printf("-> Produk dengan ID '%s' dihapus sepenuhnya dari keranjang.\n", idProduk);
}


// Mengurangi kuantitas produk dari keranjang.
void kurangiProdukDariKeranjang(KeranjangBelanja* keranjang, const char* idProduk, int kuantitas) {
    if (keranjang == NULL || kuantitas <= 0) return;

    KeranjangNode* itemAda = cariProdukDiKeranjang(keranjang, idProduk);

    if (itemAda == NULL) {
        printf("-> Produk dengan ID '%s' tidak ada di keranjang.\n", idProduk);
        return;
    }

    if (kuantitas >= itemAda->kuantitas) {
        // Jika jumlah yang dikurangi lebih besar atau sama dengan yang ada, hapus sepenuhnya
        hapusNodeSepenuhnya(keranjang, idProduk);
    } else {
        // Jika tidak, cukup kurangi kuantitas dan total harga
        itemAda->kuantitas -= kuantitas;
        keranjang->totalHarga -= (itemAda->infoProduk.harga * kuantitas);
        printf("-> Kuantitas '%s' dikurangi %d. Sisa: %d\n", itemAda->infoProduk.nama, kuantitas, itemAda->kuantitas);
    }
}

// Menampilkan isi keranjang belanja secara rapi.
void displayKeranjang(KeranjangBelanja* keranjang) {
    printf("\n================ ISI KERANJANG BELANJA ================\n");
    if (isKeranjangEmpty(keranjang)) {
        printf("                      Keranjang kosong.\n");
    } else {
        printf("No. | Nama Produk              | Harga      | Kuantitas | Subtotal\n");
        printf("----------------------------------------------------------\n");
        KeranjangNode* current = keranjang->head;
        int i = 1;
        while (current != NULL) {
            double subtotal = current->infoProduk.harga * current->kuantitas;
            printf("%-3d | %-24s | %-10.0f | %-9d | %.0f\n",
                   i,
                   current->infoProduk.nama,
                   current->infoProduk.harga,
                   current->kuantitas,
                   subtotal);
            current = current->next;
            i++;
        }
        printf("----------------------------------------------------------\n");
        printf("Total Belanja: %.0f\n", keranjang->totalHarga);
    }
    printf("=======================================================\n");
}

// Menghancurkan keranjang dan membebaskan semua memori yang digunakan.
void destroyKeranjang(KeranjangBelanja** keranjang) {
    if (keranjang == NULL || *keranjang == NULL) return;

    KeranjangNode* current = (*keranjang)->head;
    KeranjangNode* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(*keranjang);
    *keranjang = NULL;
}