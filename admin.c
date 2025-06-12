#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

typedef struct {
    char username[50];
    char password[50];
} Admin;

void menuAdmin(TreeNode* rootSupermarket) {
    int pilihan;
    do {
        printf("\n=== MENU MASUK ADMIN ===\n");
        printf("1. Login Admin\n");
        printf("2. Registrasi Admin\n");
        printf("0. Kembali ke menu utama\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                if (loginAdmin()) {
                    adminMenu(rootSupermarket);  // masuk ke menu admin
                } else {
                    printf("Login gagal. Username atau password salah.\n");
                }
                break;
            case 2:
                registerAdmin();  // daftar admin baru
                break;
            case 0:
                printf("Kembali ke menu utama...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}

int isUsernameExist(const char* username) {
    FILE* file = fopen("admin_data.txt", "r");
    if (!file) return 0;

    Admin temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) != EOF) {
        if (strcmp(temp.username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void registerAdmin() {
    Admin newAdmin;
    printf("=== REGISTRASI ADMIN ===\n");
    printf("Masukkan username: ");
    scanf("%s", newAdmin.username);

    if (isUsernameExist(newAdmin.username)) {
        printf("Username sudah terdaftar!\n");
        return;
    }

    printf("Masukkan password: ");
    scanf("%s", newAdmin.password);

    FILE* file = fopen("admin_data.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(file, "%s %s\n", newAdmin.username, newAdmin.password);
    fclose(file);
    printf("Registrasi berhasil!\n");
}

int loginAdmin() {
    Admin login;
    printf("=== LOGIN ADMIN ===\n");
    printf("Masukkan username: ");
    scanf("%s", login.username);
    printf("Masukkan password: ");
    scanf("%s", login.password);

    FILE* file = fopen("admin_data.txt", "r");
    if (file == NULL) {
        printf("Belum ada admin terdaftar!\n");
        return 0;
    }

    Admin temp;
    while (fscanf(file, "%s %s", temp.username, temp.password) != EOF) {
        if (strcmp(login.username, temp.username) == 0 && strcmp(login.password, temp.password) == 0) {
            fclose(file);
            printf("Login berhasil. Selamat datang, %s!\n", login.username);
            return 1;
        }
    }

    fclose(file);
    printf("Login gagal. Username atau password salah.\n");
    return 0;
}

void adminMenu(TreeNode* rootSupermarket) {
    int pilihan;
    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("1. Tambah Produk\n");
        printf("2. Hapus Produk\n");
        printf("3. Lihat Daftar Produk\n");
        printf("0. Logout\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                printf("-> Tambah produk (belum diimplementasi).\n");
                break;
            case 2:
                printf("-> Hapus produk (belum diimplementasi).\n");
                break;
            case 3:
                printf("-> Lihat produk (belum diimplementasi).\n");
                break;
            case 0:
                printf("-> Logout.\n");
                break;
            default:
                printf("-> Pilihan tidak valid!\n");
        }
    } while (pilihan != 0);
}
