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

void deleteBook()
{
  FILE *file;
  Buku *buku = NULL; // pointer ke array Buku
  int count = 0, i, index;
  int kapasitas = 10; // kapasitas awal

  // alokasikan memori awal
  buku = malloc(kapasitas * sizeof(Buku));
  if (buku == NULL)
  {
    printf("Gagal alokasi memori!\n");
    return;
  }

  // buka file databuku.txt
  file = fopen("databuku.txt", "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    free(buku);
    return;
  }

  // baca data buku dari file
  while (fscanf(file, "%[^|]|%[^|]|%[^|]|%f\n",
                buku[count].kode,
                buku[count].judul,
                buku[count].kategori,
                &buku[count].harga) == 4)
  {
    count++;

    // kitika array penuh, tambahkan kapasitas
    if (count >= kapasitas)
    {
      kapasitas *= 2;
      Buku *temp = realloc(buku, kapasitas * sizeof(Buku));

      if (temp == NULL)
      {
        printf("Gagal menambah kapasitas memori!\n");
        free(buku);
        fclose(file);
        return;
      }

      buku = temp; // gunakan pointer baru hasil realloc
    }
  }
  fclose(file);

  // validasi jika data buku kosong
  if (count == 0)
  {
    printf("Daftar buku kosong!\n");
    free(buku);
    return;
  }

  // tampilkan daftar buku
  printf("Daftar Buku:\n");
  for (i = 0; i < count; i++)
  {
    printf("%d. %s | %s | %s | %.2f\n",
           i + 1,
           buku[i].kode,
           buku[i].judul,
           buku[i].kategori,
           buku[i].harga);
  }

  // minta input index buku yang ingin dihapus
  printf("\nMasukkan index buku yang ingin dihapus (1 - %d): ", count);
  scanf("%d", &index);

  // validasi index input
  if (index < 1 || index > count)
  {
    printf("Index tidak valid!\n");
    free(buku);
    return;
  }

  // geser data untuk menghapus buku
  for (i = index - 1; i < count - 1; i++)
  {
    buku[i] = buku[i + 1];
  }
  count--;

  // write ulang ke file databuku.txt
  file = fopen("databuku.txt", "w");
  if (!file)
  {
    printf("Gagal membuka file untuk menulis!\n");
    free(buku);
    return;
  }

  for (i = 0; i < count; i++)
  {
    fprintf(file, "%s|%s|%s|%.2f\n",
            buku[i].kode,
            buku[i].judul,
            buku[i].kategori,
            buku[i].harga);
  }
  fclose(file);

  printf("\nData Successfully delete..\n");

  // hapus alokasi memori dinamis setelah selesai
  free(buku);
}

int main()
{
  deleteBook();
  return 0;
}
