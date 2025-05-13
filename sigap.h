#ifndef SIGAP_H
#define SIGAP_H

#define MAX_NAME 50
#define INT_MAX 2147483647  // Definisikan nilai maksimum integer

// Struktur Produk
struct Produk {
    int id;
    char nama[MAX_NAME];
    int stok;
    int harga;
    struct Produk* next;  // Pointer ke produk berikutnya
    struct Produk* prev;  // Pointer ke produk sebelumnya (untuk doubly linked list)
};

// Struktur Pesanan
struct Pesanan {
    int id;
    char namaProduk[100];
    int jumlah;
    struct Pesanan* next;
};

// Deklarasi eksternal untuk produk dan antrian pesanan
extern struct Produk* head;   // Head untuk daftar produk
extern struct Pesanan* front; // Front untuk antrian pesanan
extern struct Pesanan* rear;  // Rear untuk antrian pesanan

// produk.c
void tambahProdukManual(int id, char* nama, int stok, int harga);
void tambahProduk();
void hapusProduk(int id);
void updateProduk();
void bacaProdukDariFile(const char* namaFile);
void simpanProdukKeFile(const char* namaFile);
void tampilkanProduk();
void kurangiStokProduk(int id, int jumlah);
void tambahStokProduk(int id, int jumlah);

// sortProduk.c
struct Produk* getLast(struct Produk* node);
void quickSortProdukByHarga(struct Produk* low, struct Produk* high);
void quickSortProdukByNama(struct Produk* low, struct Produk* high);
void urutkanProdukById();
void urutkanProduk(const char* mode);


// Fungsi pesanan
void tambahAntrian(int idProduk, int jumlah);
void prosesPesanan();
void simpanAntrianKeFile();
void muatAntrianDariFile();

// Fungsi riwayat
void simpanRiwayat(int idProduk, int jumlah);  // Menyimpan riwayat pesanan
void tampilkanRiwayat(void);

// Deklarasi Fungsi Input
int inputInteger(const char* prompt, int min, int max);
int produkTersedia(int id);

//login
void registrasi();
int login(char* username, char* role);

#endif // SIGAP_H
