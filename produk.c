// produk.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "sigap.h"

struct Produk* head = NULL;

void tambahProdukManual(int id, char* nama, int stok, int harga) {
    struct Produk* ptr = head;
    while (ptr) {
        if (ptr->id == id) {
            printf("Produk dengan ID %d sudah ada.\n", id);
            return;
        }
        ptr = ptr->next;
    }

    struct Produk* baru = (struct Produk*)malloc(sizeof(struct Produk));
    baru->id = id;
    strcpy(baru->nama, nama);
    baru->stok = stok;
    baru->harga = harga;
    baru->next = head;
    baru->prev = NULL;

    if (head != NULL) head->prev = baru;
    head = baru;

    printf("Produk dengan ID %d berhasil ditambahkan.\n", id);
}

void tambahProduk() {
    int id, stok, harga;
    char nama[MAX_NAME];
    printf("Masukkan ID Produk: ");
    scanf("%d", &id);
    getchar();
    printf("Masukkan Nama Produk: ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';
    printf("Masukkan Stok: ");
    scanf("%d", &stok);
    printf("Masukkan Harga: ");
    scanf("%d", &harga);
    tambahProdukManual(id, nama, stok, harga);
}

void hapusProduk(int id) {
    struct Produk* ptr = head;
    struct Produk* prev = NULL;
    while (ptr) {
        if (ptr->id == id) {
            if (prev == NULL) {
                head = ptr->next;
                if (head) head->prev = NULL;
            } else {
                prev->next = ptr->next;
                if (ptr->next) ptr->next->prev = prev;
            }
            free(ptr);
            printf("Produk dengan ID %d telah dihapus.\n", id);
            return;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    printf("Produk dengan ID %d tidak ditemukan.\n", id);
}

void updateProduk() {
    int pilihanUpdate;
    printf("Pilih tindakan:\n");
    printf("1. Tambah Produk\n");
    printf("2. Hapus Produk\n");
    pilihanUpdate = inputInteger("Pilihan: ", 1, 2);
    if (pilihanUpdate == 1) {
        tambahProduk();
    } else if (pilihanUpdate == 2) {
        int id = inputInteger("Masukkan ID Produk yang ingin dihapus: ", 1, INT_MAX);
        hapusProduk(id);
    } else {
        printf("Pilihan tidak valid.\n");
    }
}

void bacaProdukDariFile(const char* namaFile) {
    FILE* file = fopen(namaFile, "r");
    if (!file) {
        printf("Gagal membuka file %s\n", namaFile);
        perror("Detail error");
        return;
    }

    int id, stok, harga;
    char nama[MAX_NAME];
    int jumlahProduk = 0;

    // Nonaktifkan output di tambahProdukManual
    while (fscanf(file, "%d,%49[^,],%d,%d\n", &id, nama, &stok, &harga) == 4) {
        struct Produk* ptr = head;
        int sudahAda = 0;
        while (ptr) {
            if (ptr->id == id) {
                sudahAda = 1;
                break;
            }
            ptr = ptr->next;
        }
        if (!sudahAda) {
            struct Produk* baru = (struct Produk*)malloc(sizeof(struct Produk));
            baru->id = id;
            strcpy(baru->nama, nama);
            baru->stok = stok;
            baru->harga = harga;
            baru->next = head;
            baru->prev = NULL;
            if (head != NULL) head->prev = baru;
            head = baru;
            jumlahProduk++;
        }
    }

    fclose(file);
    printf("Berhasil memuat %d produk dari file.\n", jumlahProduk);
}


void simpanProdukKeFile(const char* namaFile) {
    FILE* file = fopen(namaFile, "w");
    struct Produk* sekarang = head;
    while (sekarang) {
        fprintf(file, "%d,%s,%d,%d\n", sekarang->id, sekarang->nama, sekarang->stok, sekarang->harga);
        sekarang = sekarang->next;
    }
    fclose(file);
}

void tampilkanProduk() {
    struct Produk* sekarang = head;
    printf("\n=== Daftar Produk ===\n");
    printf("+-------+------------------------------------------+--------+-------------+\n");
    printf("|  ID   | Nama Produk                              | Stok   | Harga       |\n");
    printf("+-------+------------------------------------------+--------+-------------+\n");
    while (sekarang) {
        printf("| %03d   | %-40s | %6d | Rp %8d |\n",
               sekarang->id, sekarang->nama, sekarang->stok, sekarang->harga);
        sekarang = sekarang->next;
    }
    printf("+-------+------------------------------------------+--------+-------------+\n");
}

void kurangiStokProduk(int id, int jumlah) {
    struct Produk* ptr = head;
    while (ptr) {
        if (ptr->id == id) {
            if (ptr->stok >= jumlah) {
                ptr->stok -= jumlah;
                printf("Stok berhasil dikurangi.\n");
            } else {
                printf("Stok tidak mencukupi.\n");
            }
            return;
        }
        ptr = ptr->next;
    }
    printf("Produk dengan ID %d tidak ditemukan.\n", id);
}

void tambahStokProduk(int id, int jumlah) {
    struct Produk* ptr = head;
    while (ptr) {
        if (ptr->id == id) {
            ptr->stok += jumlah;
            printf("Stok produk dengan ID %d berhasil ditambah sebanyak %d.\n", id, jumlah);
            return;
        }
        ptr = ptr->next;
    }
    printf("Produk dengan ID %d tidak ditemukan.\n", id);
}

