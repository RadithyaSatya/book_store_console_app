#include "bookstore.h"

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