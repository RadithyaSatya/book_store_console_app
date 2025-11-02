#include "bookstore.h"

// deklarasi fungsi-fungsi
void sortMenu();
void sortByName(Buku *buku, int count);
void sortByPrice(Buku *buku, int count);

// fungsi mengurutkan data buku berdasarkan nama secara ascending
void sortByName(Buku *buku, int count)
{
  Buku temp;
  int i, j;
  for (i = 0; i < count - 1; i++) // perulangan buat proses tukar-tukar data (bubble sort)
  {
    for (j = 0; j < count - i - 1; j++)
    {
      if (strcmp(buku[j].judul, buku[j + 1].judul) > 0) // bandingin judul sekarang dengan yang setelahnya
      {
        temp = buku[j];
        buku[j] = buku[j + 1];
        buku[j + 1] = temp;
      }
    }
  }
  printf("\nData berhasil diurutkan berdasarkan *nama (ascending)*:\n"); // tampilkan hasil sorting
  for (i = 0; i < count; i++)
  {
    printf("%d. %s | %s | %s | %.2f\n",
           i + 1,
           buku[i].kode,
           buku[i].judul,
           buku[i].kategori,
           buku[i].harga);
  }
}

// fungsi mengurutkan data buku berdasarkan harga secara descending
void sortByPrice(Buku *buku, int count)
{
  int i, j, maxIndex;
  Buku temp;

  for (i = 0; i < count - 1; i++)
  {
    maxIndex = i;
    for (j = i + 1; j < count; j++)
    {
      if (buku[j].harga > buku[maxIndex].harga) // cari buku dengan harga paling tinggi
      {
        maxIndex = j;
      }
    }
    if (maxIndex != i) // kalau ketemu yang lebih mahal, tukar
    {
      temp = buku[i];
      buku[i] = buku[maxIndex];
      buku[maxIndex] = temp;
    }
  }

  printf("\nData berhasil diurutkan berdasarkan *harga (descending)*:\n"); // tampilkan hasil sorting
  for (i = 0; i < count; i++)
  {
    printf("%d. %s | %s | %s | %.2f\n",
           i + 1,
           buku[i].kode,
           buku[i].judul,
           buku[i].kategori,
           buku[i].harga);
  }
}

// fungsi menu utama untuk fitur sorting
void sortMenu()
{
  Buku *buku = NULL;
  int count = 0;
  char pilihan;

  count = readBooksFromFile(&buku, "databuku.txt"); // buka file databuku.txt

  // validasi file kosong
  if (count == 0)
  {
    printf("Tidak ada data buku untuk diurutkan.\n");
    free(buku);
    return;
  }

  // tampilkan submenu sorting
  do
  {
    printf("\n===== SORT MENU =====\n");
    printf("a. Urutkan berdasarkan Nama (Ascending)\n");
    printf("b. Urutkan berdasarkan Harga (Descending)\n");
    printf("x. Kembali ke menu utama\n");
    printf("Pilih opsi: ");
    scanf(" %c", &pilihan);

    switch (pilihan)
    {
    case 'a':
      sortByName(buku, count);
      break;
    case 'b':
      sortByPrice(buku, count);
      break;
    case 'x':
      printf("Kembali ke menu utama...\n");
      break;
    default:
      printf("Pilihan tidak valid!\n");
    }
  } while (pilihan != 'x');

  // bersihkan memori
  free(buku);
}
