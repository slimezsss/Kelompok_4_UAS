#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sigap.h"

// Inisialisasi variabel global
struct Pesanan* front = NULL;
struct Pesanan* rear = NULL;

void tambahAntrian(int idProduk, int jumlah) {
    struct Produk* ptr = head;
    while (ptr && ptr->id != idProduk) {
        ptr = ptr->next;
    }

    if (!ptr) {
        printf("Produk tidak ditemukan.\n");
        return;
    }

    struct Pesanan* baru = (struct Pesanan*)malloc(sizeof(struct Pesanan));
    if (baru == NULL) {
        printf("Gagal mengalokasikan memori untuk pesanan.\n");
        return;
    }
    baru->id = idProduk;
    strcpy(baru->namaProduk, ptr->nama);
    baru->jumlah = jumlah;
    baru->next = NULL;

    printf("Pesanan ditambahkan: %s x%d\n", baru->namaProduk, jumlah);

    if (rear == NULL) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }

    // Debugging
    printf("Front ID: %d, Rear ID: %d\n", front->id, rear->id);
    simpanAntrianKeFile();
}

void prosesPesanan() {
    printf("Front ID sebelum proses: %d\n", front ? front->id : -1);
    if (front == NULL) {
        printf("Tidak ada pesanan dalam antrian.\n");
        return;
    }

    struct Pesanan* temp = front;
    printf("Memproses: %s x%d\n", temp->namaProduk, temp->jumlah);
    kurangiStokProduk(temp->id, temp->jumlah);
    simpanRiwayat(temp->id, temp->jumlah);
    front = front->next;
    free(temp);
    if (front == NULL) {
        rear = NULL; // Reset rear jika antrian kosong
    }

    printf("Pesanan telah diproses.\n");
}


void simpanAntrianKeFile() {
    FILE* f = fopen("data_pesanan.txt", "w");
    if (!f) {
        printf("Gagal menyimpan antrian.\n");
        return;
    }

    struct Pesanan* temp = front;
    while (temp) {
        fprintf(f, "%d;%s;%d\n", temp->id, temp->namaProduk, temp->jumlah);
        temp = temp->next;
    }

    fclose(f);
}



void muatAntrianDariFile() {
    FILE* f = fopen("data_pesanan.txt", "r");
    if (!f) {
        printf("File pesanan tidak ditemukan.\n");
        return;
    }

    int id, jumlah;
    char nama[100];

    while (fscanf(f, "%d;%[^;];%d\n", &id, nama, &jumlah) == 3) {
        struct Pesanan* baru = (struct Pesanan*)malloc(sizeof(struct Pesanan));
        baru->id = id;
        strcpy(baru->namaProduk, nama);
        baru->jumlah = jumlah;
        baru->next = NULL;

        if (!rear) {
            front = rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
    }

    fclose(f);
}
