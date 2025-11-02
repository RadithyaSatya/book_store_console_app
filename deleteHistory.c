#include "bookstore.h"

void deleteHistory()
{
    FILE *file;
    struct Sales *hist = NULL; // pointer ke array history
    int count = 0, i, index;
    int kapasitas = 10;
    char kode[20];
    int qty;
    float total;

    // alokasi awal
    hist = (struct Sales *)malloc(kapasitas * sizeof(struct Sales));
    if (hist == NULL)
    {
        printf("Gagal alokasi memori!\n");
        return;
    }

    // buka file history / datasales
    file = fopen(DATASALES, "r");
    if (file == NULL)
    {
        printf("Tidak ada data history / file %s belum ada.\n", DATASALES);
        free(hist);
        return;
    }

    // baca semua baris history
    while (fscanf(file, "%[^|]|%d|%f\n", kode, &qty, &total) == 3)
    {
        // pastikan masih muat di array
        if (count >= kapasitas)
        {
            kapasitas *= 2;
            struct Sales *tmp = (struct Sales *)realloc(hist, kapasitas * sizeof(struct Sales));
            if (tmp == NULL)
            {
                printf("Gagal menambah kapasitas memori!\n");
                fclose(file);
                free(hist);
                return;
            }
            hist = tmp;
        }

        strcpy(hist[count].kodebuku, kode);
        hist[count].qty = qty;
        hist[count].harga = total; // di file kita simpan total harga, bukan harga satuan
        count++;
    }
    fclose(file);

    // kalau kosong
    if (count == 0)
    {
        printf("Tidak ada data history untuk dihapus!\n");
        free(hist);
        return;
    }

    // tampilkan list history
    printf("\n===== HISTORY TRANSAKSI =====\n");
    for (i = 0; i < count; i++)
    {
        printf("%d. %s | Qty: %d | Total: %.2f\n",
               i + 1,
               hist[i].kodebuku,
               hist[i].qty,
               hist[i].harga);
    }

    // minta index
    printf("\nMasukkan index history yang ingin dihapus (1 - %d): ", count);
    scanf("%d", &index);

    // validasi
    if (index < 1 || index > count)
    {
        printf("Index tidak valid!\n");
        free(hist);
        return;
    }

    // geser ke kiri mulai dari index-1
    for (i = index - 1; i < count - 1; i++)
    {
        hist[i] = hist[i + 1];
    }
    count--;

    // tulis ulang ke file
    file = fopen(DATASALES, "w");
    if (file == NULL)
    {
        printf("Gagal membuka file %s untuk menulis ulang!\n", DATASALES);
        free(hist);
        return;
    }

    for (i = 0; i < count; i++)
    {
        // ingat: di addSales kamu tulis: kode|qty|total
        fprintf(file, "%s|%d|%.2f\n",
                hist[i].kodebuku,
                hist[i].qty,
                hist[i].harga);
    }
    fclose(file);

    printf("\nData Successfully delete..\n");

    free(hist);
}
