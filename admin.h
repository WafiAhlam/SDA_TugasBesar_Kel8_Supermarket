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
#endif // ADMIN_H