#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABUKU "databuku.txt"
#define DATASALES "history.txt"

// Structure definitions
struct Book {
    char kode[15];
    char judul[100];
    char jenis[100];
    float harga;
};

struct Sales {
    char kodebuku[15];
    int qty;
    float harga;
};

typedef struct {
    char kode[15];
    char judul[100];
    char kategori[100];
    float harga;
} Buku;

// Function declarations from bookstore.c
void addBook();
void addSales();
void viewBooks();

// Function declarations from deleteBook.c
void deleteBook();

// Function declarations from deleteHistory.c
void deleteHistory();

// Function declarations from viewHistory.c
void viewHistory();

// Function declarations from sorting_Algo.c
void sortMenu();

// Utility functions
int readBooksFromFile(Buku **buku, const char *filename);

#endif