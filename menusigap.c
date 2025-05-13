#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "sigap.h"
#define FILE_PRODUK "data_produk.txt"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int inputInteger(const char* prompt, int min, int max) {
    char line[100];
    int value;
    char* endptr;

    while (1) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) {
            printf("Terjadi kesalahan input.\n");
            continue;
        }

        value = (int)strtol(line, &endptr, 10);

        if (*endptr != '\n' && *endptr != '\0') {
            printf("Input tidak valid. Harus berupa angka.\n");
            continue;
        }

        // Memastikan angka dalam rentang yang diperbolehkan
        if (value < min || value > max) {
            printf("Input di luar rentang yang diperbolehkan (%d - %d).\n", min, max);
            continue;
        }

        return value;
    }
}

int produkTersedia(int id) {
    struct Produk* ptr = head;
    while (ptr) {
        if (ptr->id == id) return 1;
        ptr = ptr->next;
    }
    return 0;
}

void menuAdmin() {
    int pilihan;
        printf("\n--- ANDA LOGIN SEBAGAI ADMIN ---");
    do {
        printf("\n--- Menu Admin ---\n");
        printf("1. Proses Pesanan\n");
        printf("2. Lihat Riwayat Pesanan\n");
        printf("3. Update Stok Produk\n");
        printf("4. Tampilkan Stok Produk\n");
        printf("5. Urutkan Produk\n");
        printf("6. Update Produk\n");
        printf("7. Keluar\n");
        printf("Pilihan: ");
        
        scanf("%d", &pilihan);
        getchar();  // Membersihkan karakter newline yang tertinggal setelah scanf

        int id, jumlah;

        switch (pilihan) {
            case 1:
                printf("Memproses pesanan...\n");
                prosesPesanan();
                break;
            case 2:
                printf("Menampilkan riwayat pesanan...\n");
                tampilkanRiwayat();
                break;
            case 3:
                printf("Mengupdate produk...\n");
                id = inputInteger("Masukkan ID Produk: ", 1, INT_MAX);
                if (!produkTersedia(id)) {
                    printf("ID produk tidak ditemukan.\n");
                    break;
                }
                printf("Pilih tindakan:\n");
                printf("1. Kurangi Stok\n");
                printf("2. Tambah Stok\n");
                int tindakanStok = inputInteger("Pilihan: ", 1, 2);
    
                jumlah = inputInteger("Masukkan jumlah: ", 1, INT_MAX);
    
                if (tindakanStok == 1) {
                    kurangiStokProduk(id, jumlah);
                } else if (tindakanStok == 2) {
                    tambahStokProduk(id, jumlah);
                } else {
                    printf("Mohon Maaf Saat Ini Fitur Belum Tersedia....\n");
                    printf("Silahkan pilih fitur yang tersedia....\n");
                }
                break;
            case 4:
                printf("Menampilkan produk\n");
                tampilkanProduk();
                break;
            case 5:
                printf("\nPilih cara mengurutkan produk:\n");
                printf("1. Urutkan berdasarkan Harga\n");
                printf("2. Urutkan berdasarkan Nama\n");
                printf("3. Urutkan berdasarkan ID\n");
                int urutPilihan = inputInteger("Pilihan: ", 1, 3);
                if (urutPilihan == 1) {
                    urutkanProduk("harga");
                } else if (urutPilihan == 2) {
                    urutkanProduk("nama");
                } else if (urutPilihan == 3) {
                    urutkanProduk("id");
                } else {
                    printf("Mohon Maaf Saat Ini Fitur Belum Tersedia....\n");
                    printf("Silahkan pilih fitur yang tersedia....\n");
                }
                break;
            case 6:
                updateProduk();
                getchar();  // Membersihkan karakter newline yang tersisa di buffer input
                break;
            case 7:
                simpanProdukKeFile(FILE_PRODUK);
                simpanAntrianKeFile("data_pesanan.txt");
                clearScreen();
                printf("------TERIMA KASIH TELAH MENGGUNAKAN APLIKASI SIGAP-----\n");
                break;
            default:
                printf("Mohon Maaf Saat Ini Fitur Belum Tersedia....\n");
                printf("Silahkan pilih fitur yang tersedia....\n");
        }
    } while (pilihan != 7);
}

void menuUser() {
    int pilihan;
        printf("\n--- ANDA LOGIN SEBAGAI ADMIN ---");
    do {
        printf("\n--- Menu User ---\n");
        printf("1. Pesan produk\n");
        printf("2. Lihat produk\n");
        printf("3. Riwayat pesanan\n");
        printf("4. Urutkan produk\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        
        scanf("%d", &pilihan);
        getchar();  // Membersihkan karakter newline yang tertinggal setelah scanf

        int id, jumlah;

        switch (pilihan) {
            case 1:
                printf("Memesan produk...\n");
                id = inputInteger("Masukkan ID Produk: ", 1, INT_MAX);
                if (!produkTersedia(id)) {
                    printf("ID produk tidak ditemukan.\n");
                    break;
                }
                jumlah = inputInteger("Masukkan jumlah: ", 1, INT_MAX);
                tambahAntrian(id, jumlah);
                simpanAntrianKeFile("data_pesanan.txt");
                break;
            case 2:
                printf("Melihat produk...\n");
                tampilkanProduk();
                break;
            case 3:
                printf("Menampilkan riwayat pesanan...\n");
                tampilkanRiwayat();
                break;
            case 4:
                printf("\nPilih cara mengurutkan produk:\n");
                printf("1. Urutkan berdasarkan Harga\n");
                printf("2. Urutkan berdasarkan Nama\n");
                printf("3. Urutkan berdasarkan ID\n");
                int urutPilihan = inputInteger("Pilihan: ", 1, 3);
                if (urutPilihan == 1) {
                    urutkanProduk("harga");
                } else if (urutPilihan == 2) {
                    urutkanProduk("nama");
                } else if (urutPilihan == 3) {
                    urutkanProduk("id");
                } else {
                    printf("Mohon Maaf Saat Ini Fitur Belum Tersedia....\n");
                    printf("Silahkan pilih fitur yang tersedia....\n");
                }
                break;
            case 5:
                simpanProdukKeFile(FILE_PRODUK);
                simpanAntrianKeFile("data_pesanan.txt");
                clearScreen();
                printf("------TERIMA KASIH TELAH MENGGUNAKAN APLIKASI SIGAP-----\n");
                break;
            default:
                printf("Mohon Maaf Saat Ini Fitur Belum Tersedia....\n");
                printf("Silahkan pilih fitur yang tersedia....\n");
        }
    } while (pilihan != 5);
}

int main() {
    bacaProdukDariFile(FILE_PRODUK);
    muatAntrianDariFile(); 

    char username[100], role[100];
    int pilihan;

    clearScreen(); 
    printf("\n-------------SELAMAT DATANG DI APLIKASI SIGAP-----------\n");
    printf("-------------SILAHKAN REGISTRASI ATAU LOGIN!!!-----------\n");
    printf("1. Login\n2. Registrasi\nPilihan: ");
    scanf("%d", &pilihan);
    getchar();  // Membersihkan karakter newline setelah scanf

    clearScreen();
    if (pilihan == 1) {
    if (login(username, role)) {
        clearScreen();
        if (strcmp(role, "admin") == 0) {
            menuAdmin();
        } else {
            menuUser();
        }
    }
        } else if (pilihan == 2) {
            registrasi();
            getchar();  // Pause agar user bisa membaca
    clearScreen();
    if (login(username, role)) {
        clearScreen();
        if (strcmp(role, "admin") == 0) {
            menuAdmin();
        } else {
            menuUser();
        }
    }
} else {
    printf("Pilihan tidak valid. Silakan jalankan ulang program dan pilih 1 atau 2.\n");
}

    return 0;
}
