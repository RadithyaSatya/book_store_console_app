#include "bookstore.h"

void displayMenu() {
    printf("\n=== BOOK STORE MANAGEMENT SYSTEM ===\n");
    printf("1. Input Data Buku Baru\n");
    printf("2. View History Transaksi Penjualan\n");
    printf("3. View Buku (Seluruh Data Buku yang Tersedia)\n");
    printf("4. Delete History (Hapus Histori Penjualan Tertentu)\n");
    printf("5. Delete Buku (Hapus Data Buku Tertentu)\n");
    printf("6. Exit (Simpan data terbaru & keluar)\n");
    printf("7. Input Transaksi Penjualan\n");
    printf("8. Sort Buku (Sorting Algorithm Menu)\n");
    printf("Pilih menu (1-8): ");
}

void saveAndExit() {
    printf("Data telah tersimpan otomatis.\n");
    printf("Terima kasih telah menggunakan Book Store Management System!\n");
}

int main() {
    int choice;
    
    printf("=== SELAMAT DATANG DI BOOK STORE MANAGEMENT SYSTEM ===\n");
    printf("Loading data...\n");
    
    while (1) {
        displayMenu();
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Input tidak valid! Masukkan angka 1-8.\n");
            continue;
        }
        
        // Clear input buffer
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                printf("\n=== INPUT DATA BUKU BARU ===\n");
                addBook();
                break;
            case 2:
                viewHistory();
                break;
            case 3:
                viewBooks();
                break;
            case 4:
                printf("\n=== DELETE HISTORY TRANSAKSI ===\n");
                deleteHistory();
                break;
            case 5:
                printf("\n=== DELETE DATA BUKU ===\n");
                deleteBook();
                break;
            case 6:
                saveAndExit();
                return 0;
            case 7:
                printf("\n=== INPUT TRANSAKSI PENJUALAN ===\n");
                addSales();
                break;
            case 8:
                printf("\n=== SORTING MENU ===\n");
                sortMenu();
                break;
            default:
                printf("Pilihan tidak valid! Masukkan angka 1-8.\n");
                break;
        }
        
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
    }
    
    return 0;
}
