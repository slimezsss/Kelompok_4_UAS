// auth.h
#ifndef SIGAP_H
#define SIGAP_H

void registrasi();
int login(char* username, char* role);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define AKUN_FILE "akun.txt"

void registrasi() {
    char username[MAX], password[MAX], role[MAX];
    FILE *file = fopen(AKUN_FILE, "a");
    if (!file) {
        printf("Gagal membuka file akun.\n");
        return;
    }

    
    printf("\n--- Registrasi ---\n");
    printf("Silahkan registrasi dan pilih peran anda!!!\n");
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    printf("Pilih peran (admin/user): ");
    scanf("%s", role);
    while (strcmp(role, "admin") != 0 && strcmp(role, "user") != 0) {
        printf("Peran tidak valid. Masukkan 'admin' atau 'user': ");
        scanf("%s", role);
    }

    fprintf(file, "%s,%s,%s\n", username, password, role);
    fclose(file);
    printf("Registrasi berhasil!\n");
}

int login(char* username, char* role) {
    char inputUser[MAX], inputPass[MAX];
    char fileUser[MAX], filePass[MAX], fileRole[MAX];

    printf("\n--- Login ---\n");
    printf("Silahkan Masukkan Username dan Password Anda!!!\n");
    printf("Username: ");
    scanf("%s", inputUser);
    printf("Password: ");
    scanf("%s", inputPass);

    FILE *file = fopen(AKUN_FILE, "r");
    if (!file) {
    file = fopen(AKUN_FILE, "w"); // buat file jika belum ada
    if (!file) {
        printf("Gagal membuat file akun.\n");
        return 0;
    }
    fclose(file);
    file = fopen(AKUN_FILE, "r"); // buka ulang untuk baca
    }


    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", fileUser, filePass, fileRole) == 3) {
        if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0) {
            strcpy(username, fileUser);
            strcpy(role, fileRole);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    printf("Login gagal. Username atau password salah.\n");
    return 0;
}
