#include <stdio.h>
#include <stdlib.h>
#include "linked.h"
#include "Queue.h"
#include "stack2.h"
#include "Treerak.h"
#include "Keranjang.h"
#include "pelanggan.h"

//Queue antrianPelanggan;       // pelanggan yang lagi ngantri
//Queue pelangganSelesai;       // pelanggan yang udah selesai belanja

//keranjang kasih 
 Keranjang* keranjang = createKeranjang();

  
    char inputID[MAX_ID_BARANG];
    printf("Masukkan ID barang yang ingin dibeli: ");
    scanf("%s", inputID);

    AddressItemNode found = SearchItem(listMakanan, inputID);
    if (found != NULL) {
        pushKeranjang(keranjang, &found->dataBarang);
        printf("Barang berhasil dimasukkan ke keranjang.\n");
    } else {
        printf("Barang tidak ditemukan.\n");
    }


    displayKeranjang(keranjang);


    printf("\nMengeluarkan barang terakhir dari keranjang...\n");
    item* dikeluarkan = popKeranjang(keranjang);
    if (dikeluarkan != NULL) {
        printf("Barang '%s' dikeluarkan dari keranjang.\n", dikeluarkan->namabarang);
    }

    displayKeranjang(keranjang);


    double total = getTotalHargaKeranjang(keranjang);
    printf("Total belanja sekarang: %.2f\n", total);

    clearKeranjang(keranjang);
    free(keranjang);

    return 0;


