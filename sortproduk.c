// sortProduk.c
#include <stdio.h>
#include <string.h>
#include "sigap.h"

extern struct Produk* head;

struct Produk* getLast(struct Produk* node) {
    while (node && node->next) node = node->next;
    return node;
}

// Sorting berdasarkan harga
struct Produk* partition(struct Produk* low, struct Produk* high) {
    int pivot = high->harga;
    struct Produk* i = low->prev;
    for (struct Produk* j = low; j != high; j = j->next) {
        if (j->harga < pivot) {
            i = (i == NULL) ? low : i->next;
            int tmp = i->harga; i->harga = j->harga; j->harga = tmp;
            char nama[50]; strcpy(nama, i->nama); strcpy(i->nama, j->nama); strcpy(j->nama, nama);
        }
    }
    i = (i == NULL) ? low : i->next;
    int tmp = i->harga; i->harga = high->harga; high->harga = tmp;
    char nama[50]; strcpy(nama, i->nama); strcpy(i->nama, high->nama); strcpy(high->nama, nama);
    return i;
}

void quickSortProdukByHarga(struct Produk* low, struct Produk* high) {
    if (high && low != high && low != high->next) {
        struct Produk* p = partition(low, high);
        quickSortProdukByHarga(low, p->prev);
        quickSortProdukByHarga(p->next, high);
    }
}

// Sorting berdasarkan nama
struct Produk* partitionByNama(struct Produk* low, struct Produk* high) {
    char pivot[50];
    strcpy(pivot, high->nama);
    struct Produk* i = low->prev;
    for (struct Produk* j = low; j != high; j = j->next) {
        if (strcmp(j->nama, pivot) < 0) {
            i = (i == NULL) ? low : i->next;
            int tmp = i->harga; i->harga = j->harga; j->harga = tmp;
            char nama[50]; strcpy(nama, i->nama); strcpy(i->nama, j->nama); strcpy(j->nama, nama);
        }
    }
    i = (i == NULL) ? low : i->next;
    int tmp = i->harga; i->harga = high->harga; high->harga = tmp;
    char nama[50]; strcpy(nama, i->nama); strcpy(i->nama, high->nama); strcpy(high->nama, nama);
    return i;
}

void quickSortProdukByNama(struct Produk* low, struct Produk* high) {
    if (high && low != high && low != high->next) {
        struct Produk* p = partitionByNama(low, high);
        quickSortProdukByNama(low, p->prev);
        quickSortProdukByNama(p->next, high);
    }
}

void urutkanProdukById() {
    struct Produk* ptr1, *ptr2;
    int tempId, tempStok, tempHarga;
    char tempNama[MAX_NAME];

    // Bubble Sort untuk mengurutkan berdasarkan ID (dari terkecil ke terbesar)
    for (ptr1 = head; ptr1 != NULL; ptr1 = ptr1->next) {
        for (ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next) {
            if (ptr1->id > ptr2->id) {  // Kondisi untuk urutan ID dari terkecil ke terbesar
                // Tukar ID
                tempId = ptr1->id;
                ptr1->id = ptr2->id;
                ptr2->id = tempId;

                // Tukar Nama
                strcpy(tempNama, ptr1->nama);
                strcpy(ptr1->nama, ptr2->nama);
                strcpy(ptr2->nama, tempNama);

                // Tukar Stok
                tempStok = ptr1->stok;
                ptr1->stok = ptr2->stok;
                ptr2->stok = tempStok;

                // Tukar Harga
                tempHarga = ptr1->harga;
                ptr1->harga = ptr2->harga;
                ptr2->harga = tempHarga;
            }
        }
    }

    // Output untuk memberi tahu bahwa produk telah diurutkan
    printf("Produk telah diurutkan berdasarkan ID (dari terkecil ke terbesar).\n");
}


// Fungsi umum
void urutkanProduk(const char* mode) {
    printf("Masuk ke urutkanProduk dengan mode: %s\n", mode);
    if (strcmp(mode, "harga") == 0) {
        struct Produk* last = getLast(head);
        quickSortProdukByHarga(head, last);
        printf("Produk telah diurutkan berdasarkan harga.\n");
    } else if (strcmp(mode, "nama") == 0) {
        struct Produk* last = getLast(head);
        quickSortProdukByNama(head, last);
        printf("Produk telah diurutkan berdasarkan nama.\n");
    } else if (strcmp(mode, "id") == 0) {
        urutkanProdukById();
    } else {
        printf("Mode pengurutan tidak dikenali.\n");
    }
}
