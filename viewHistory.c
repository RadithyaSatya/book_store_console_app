#include "bookstore.h"

void viewHistory() {
    FILE *file = fopen(DATASALES, "r");
    if (!file) {
        printf("File %s tidak bisa diakses atau belum ada data transaksi.\n", DATASALES);
        return;
    }

    char buffer[200];
    struct Sales sales;

    printf("\n=== HISTORY TRANSAKSI PENJUALAN ===\n");
    printf("%-10s | %-15s | %-15s\n", "Kode Buku", "Jumlah Terjual", "Total Harga");
    printf("-----------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0; 
        if (buffer[0] == '\0') continue;

        char *token = strtok(buffer, "|");
        if (token) strcpy(sales.kodebuku, token);

        token = strtok(NULL, "|");
        if (token) sales.qty = atoi(token);

        token = strtok(NULL, "|");
        if (token) sales.harga = atof(token);

        printf("%-10s | %-15d | Rp. %.2f\n",
               sales.kodebuku, sales.qty, sales.harga);
    }

    fclose(file);
    printf("-----------------------------------------------\n");
}