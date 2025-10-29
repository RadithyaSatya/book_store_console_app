#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char kode[15];
  char judul[100];
  char kategori[100];
  float harga;
} Buku;

// deklarasi fungsi-fungsi
int readBooksFromFile(Buku **buku, const char *filename);
void sortMenu();
void sortByName(Buku *buku, int count);
void sortByPrice(Buku *buku, int count);

// fungsi untuk membuka dan membaca dataBook.txt
int readBooksFromFile(Buku **buku, const char *filename)
{
  FILE *file;
  int count = 0;
  int kapasitas = 10;

  // alokasi awal
  *buku = malloc(kapasitas * sizeof(Buku));
  if (!*buku)
  {
    printf("Gagal alokasi memori!\n");
    return 0;
  }

  // buka file
  file = fopen(filename, "r");
  if (!file)
  {
    printf("File %s tidak ditemukan!\n", filename);
    free(*buku);
    *buku = NULL;
    return 0;
  }

  // baca baris demi baris
  while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f\n",
                (*buku)[count].kode,
                (*buku)[count].judul,
                (*buku)[count].kategori,
                &(*buku)[count].harga) == 4)
  {
    count++;

    // kalau penuh, gandakan kapasitas
    if (count >= kapasitas)
    {
      kapasitas *= 2;
      Buku *temp = realloc(*buku, kapasitas * sizeof(Buku));
      if (!temp)
      {
        printf("Gagal menambah kapasitas memori!\n");
        free(*buku);
        fclose(file);
        *buku = NULL;
        return 0;
      }
      *buku = temp;
    }
  }
  fclose(file);
  return count;
}

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
  FILE *file;
  Buku *buku = NULL;
  int count = 0, kapasitas = 10, i;
  char pilihan;

  buku = malloc(kapasitas * sizeof(Buku)); // alokasi awal memori buat nampung data buku
  if (!buku)
  {
    printf("Gagal alokasi memori!\n");
    return;
  }

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

int main()
{
  sortMenu();
  return 0;
}
