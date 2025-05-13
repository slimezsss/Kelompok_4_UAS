#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sigap.h"
#define FILE_RIWAYAT "riwayat_pesanan.txt"

void simpanRiwayat(int idProduk, int jumlah) {
    FILE* file = fopen(FILE_RIWAYAT, "a");
    time_t now = time(NULL);
    fprintf(file, "%d,%d,%ld\n", idProduk, jumlah, now);
    fclose(file);
}

void tampilkanRiwayat() {
    FILE* file = fopen(FILE_RIWAYAT, "r");
    if (!file) {
        printf("Belum ada riwayat pesanan.\n");
        return;
    }
    int id, jumlah;
    long waktu;
    printf("\n=== Riwayat Pesanan ===\n");
    printf("+------------+--------+---------------------+\n");
    printf("| ID Produk  | Jumlah | Waktu               |\n");
    printf("+------------+--------+---------------------+\n");

while (fscanf(file, "%d,%d,%ld\n", &id, &jumlah, &waktu) == 3) {
    char waktuStr[30];
    strftime(waktuStr, sizeof(waktuStr), "%Y-%m-%d %H:%M:%S", localtime(&waktu));
    printf("| %03d        | %-6d | %-19s |\n", id, jumlah, waktuStr);
}
    printf("+------------+--------+---------------------+\n");
    fclose(file);
}
