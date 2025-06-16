#ifndef ADMIN_H
#define ADMIN_H

/**
 * REVISI: Tambahkan include ini agar tipe data RakBTree dikenali.
 */
#include "avl.h"
#include "TreeRak.h"
#include "tumpukan.h"
#include "Kasir.h"
#include "tipedata.h"
/**
 * REVISI: Hapus semua deklarasi 'menuAdmin' yang lama.
 * Sisakan hanya deklarasi fungsi yang relevan dengan struktur baru.
 */

/*
IS: Sistem berada di menu utama. Semua struktur data global (rootAVL, rootLayout, dll.) telah diinisialisasi.
FS: Sesi admin telah berakhir dan program kembali ke menu utama. State dari struktur data global mungkin telah berubah.

Creator: Marelly Salsa Kasih Risky
*/
void jalankanModeAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir);

/*
IS: Admin telah berhasil login. Semua struktur data global tersedia untuk dimanipulasi.
FS: Admin telah memilih opsi logout. Kontrol program kembali ke fungsi pemanggil (jalankanModeAdmin).

Creator: Marelly Salsa Kasih Risky
*/
void prosesMenuAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan, AntrianKasir* antriankasir);

/*
IS: rootAVL adalah pointer ke root pointer dari AVL tree. Pengguna siap memasukkan data produk baru.
FS: Sebuah produk baru berdasarkan input pengguna telah ditambahkan ke dalam database (AVL Tree). Tree tetap dalam keadaan seimbang.

Creator: Wafi Ahlam Rizqulloh
*/
void menuTambahProduk(RakBTree** rootAVL);

/*
IS: AVL Tree berisi data produk. Pengguna siap memasukkan ID produk yang akan dihapus.
FS: Jika produk ditemukan, node yang berisi produk tersebut telah dihapus dari AVL Tree. Tree tetap seimbang.

Creator: Wafi Ahlam Rizqulloh
*/
void menuHapusProduk(RakBTree** rootAVL, TreeNode* rootLayout);

/*
IS: rootAVL adalah pointer ke root dari AVL Tree.
FS: Seluruh produk yang ada di database telah ditampilkan ke layar secara terurut. State tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void menuLihatProduk(RakBTree* rootAVL);

/*
IS: Produk ada di database AVL dan rak fisik di layout tree terdefinisi.
FS: Stok master produk di AVL Tree telah berkurang, dan stok produk di rak fisik yang dituju telah bertambah.

Creator: Wafi Ahlam Rizqulloh
*/
void menuTambahStokKeRak(RakBTree* rootAVL, TreeNode* rootLayout);

/*
IS: rootLayout adalah pointer ke root dari peta supermarket.
FS: Peta supermarket telah ditampilkan ke layar. State tree tidak berubah.

Creator: Wafi Ahlam Rizqulloh
*/
void menuLihatPeta(TreeNode* rootLayout);

/*
IS: Produk ada di database AVL dan rakTumpukan terdefinisi.
FS: Stok master produk di AVL Tree telah berkurang, dan satu atau lebih item produk telah ditambahkan (push) ke atas rakTumpukan.

Creator: Wafi Ahlam Rizqulloh
*/
void menuPushProdukKeTumpukan(RakBTree* rootAVL, RakTumpukan* rakTumpukan);

/*
IS: Pengguna siap memasukkan username dan password baru. File admin_data.txt berada dalam state tertentu.
FS: Jika username belum ada, satu baris data admin baru telah ditambahkan ke akhir file admin_data.txt.

Creator: Marelly Salsa Kasih Risky
*/
void registerAdmin();

/*
IS: Pengguna siap memasukkan username dan password untuk login.
FS: Mengembalikan nilai 1 (TRUE) jika kombinasi username dan password ditemukan di admin_data.txt. Jika tidak, mengembalikan 0 (FALSE). File admin_data.txt tidak berubah.

Creator: Marelly Salsa Kasih Risky
*/
int loginAdmin();

/*
IS: antrian terdefinisi dan mungkin berisi pelanggan.
FS: Jika antrian tidak kosong, pelanggan pertama telah dihapus (dequeued), keranjang belanjanya diproses, dan memorinya dibebaskan. Jika kosong, pesan eror ditampilkan.

Creator: Wafi Ahlam Rizqulloh
*/
void menuLayaniPelanggan(AntrianKasir* antrian);


/*
// Fungsi utama yang dipanggil dari main.c untuk memulai mode admin
void jalankanModeAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan, AntrianKasir* antrianKasir);

// Fungsi internal yang menangani menu setelah admin login
void prosesMenuAdmin(RakBTree** rootAVL, TreeNode* rootLayout, RakTumpukan* rakTumpukan);

// Deklarasi untuk setiap opsi di menu admin
void menuTambahProduk(RakBTree** rootAVL);
void menuHapusProduk(RakBTree** rootAVL, TreeNode* rootLayout);
void menuLihatProduk(RakBTree* rootAVL);
void menuTambahStokKeRak(RakBTree* rootAVL, TreeNode* rootLayout);
void menuLihatPeta(TreeNode* rootLayout);
void menuPushProdukKeTumpukan(RakBTree* rootAVL, RakTumpukan* rakTumpukan);
// Anda mungkin masih memerlukan ini untuk login/registrasi di luar menu utama
void registerAdmin();
int loginAdmin();
void menuLayaniPelanggan(AntrianKasir* antrian);
*/
#endif // ADMIN_H