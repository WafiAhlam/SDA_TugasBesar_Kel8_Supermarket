#ifndef ADMIN_H
#define ADMIN_H

/**
 * REVISI: Tambahkan include ini agar tipe data RakBTree dikenali.
 */
#include "avl.h"
#include "TreeRak.h"

/**
 * REVISI: Hapus semua deklarasi 'menuAdmin' yang lama.
 * Sisakan hanya deklarasi fungsi yang relevan dengan struktur baru.
 */

// Fungsi utama yang dipanggil dari main.c untuk memulai mode admin
void jalankanModeAdmin(RakBTree** rootAVL, TreeNode* rootLayout);

// Fungsi internal yang menangani menu setelah admin login
void prosesMenuAdmin(RakBTree** rootAVL, TreeNode* rootLayout);

// Deklarasi untuk setiap opsi di menu admin
void menuTambahProduk(RakBTree** rootAVL);
void menuHapusProduk(RakBTree** rootAVL, TreeNode* rootLayout);
void menuLihatProduk(RakBTree* rootAVL);
void menuTambahStokKeRak(RakBTree* rootAVL, TreeNode* rootLayout);
void menuLihatPeta(TreeNode* rootLayout);

// Anda mungkin masih memerlukan ini untuk login/registrasi di luar menu utama
void registerAdmin();
int loginAdmin();

#endif // ADMIN_H