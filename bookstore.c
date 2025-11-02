#include "bookstore.h"

// Function untuk menghapus enter pada string
void removeEnter(char *s)
{
    char *newline_pos = strchr(s, '\n');

    if (newline_pos != NULL)
    {
        *newline_pos = '\0';
    }
}

// Function untuk mengambil kode buku terakhir
char *getBookCode(char *buffer)
{
    if (!buffer || buffer[0] == '\0')
    {
        return NULL;
    }

    char *tab = strchr(buffer, '|');   // Mendapatkan index paling awal karakter |
    size_t code_length = tab - buffer; // Digunakan untuk mendapatkan panjang kode buku dari buffer

    char *code = (char *)malloc(code_length + 1); // Mengalokasikan memori berdasarkan panjang kode buku
    strncpy(code, buffer, code_length);           // Copy kode buku dari buffer ke variable code
    code[code_length] = '\0';

    return code;
}

char *generateBookCode(char *kodeterakhir)
{
    if (!kodeterakhir) // Jika kode terakhir tidak ditemukan
    {
        char *new_code = (char *)malloc(strlen("BK") + 3 + 1); // Alokasi memori untuk kode baru
        if (new_code)
        {
            sprintf(new_code, "%s%0*d", "BK", 3, 1); // Membuat kode buku BK001
        }
        return new_code;
    }
    char *num_str = kodeterakhir + strlen("BK"); // Menyimpan digit dari kode buku
    int last_number = atoi(num_str);             // Konversi digit dari kode buku yang awalnya string menjadi int

    int next_number = last_number + 1;

    size_t new_code_len = strlen("BK") + 3;
    char *new_code = (char *)malloc(new_code_len + 1); // Alokasi memori untuk kode baru

    sprintf(new_code, "%s%0*d", "BK", 3, next_number); // Menyimpan kode baru ke variable new_code

    return new_code;
}

void addBook()
{
    FILE *file;       // Deklarasi variable yang nantinya untuk R file databuku.txt
    struct Book buku; // Deklarasi structur buku
    char buffer[150];
    char *kodeterakhir = NULL; // inisialisasi biar gak ada pointer sampah
    char *kodeterbaru = NULL;
    file = fopen(DATABUKU, "a"); // buka databuku.txt dengan mode a untuk get error system dan membuat file jika file tidak ada
    if (file == NULL)
    {
        printf("File %s tidak bisa diakses", DATABUKU);
    }
    else
    {
        fclose(file); // close file mode a
        file = fopen("databuku.txt", "r"); // open file ke mode read untuk get kode buku terakhir
        while (fgets(buffer, sizeof(buffer), file) != NULL) // looping untuk membaca data buku per line
        {
            buffer[strcspn(buffer, "\n")] = 0; // merubah enter pada buffer menjadi \0
            if (buffer[0] == '\0')             // jika buffer kosong, maka langsung skip
            {
                continue;
            }
            kodeterbaru = getBookCode(buffer); // Panggil getBookCode untuk mendapatkan kode buku terakhir
            if (kodeterbaru)
            {
                if (kodeterakhir != NULL) // hindari free pointer kosong
                    free(kodeterakhir);
                kodeterakhir = kodeterbaru;
            }
        }
        fclose(file);                                      // menutup file data buku dengan mode read
        strcpy(buku.kode, generateBookCode(kodeterakhir)); // generate kode buku baru
        if (kodeterakhir != NULL)
            free(kodeterakhir); // bebasin memori terakhir kalau ada
        file = fopen(DATABUKU, "a");                       // membuka file databuku dengan mode append
        if (file == NULL)
        {
            printf("File %s tidak bisa diakses", DATABUKU);
        }
        else
        {
            // Start input judul buku, jenis buku dan harga
            puts("Masukkan Data Buku");
            puts("--------------------");
            printf("Masukkan judul buku: ");
            fgets(buku.judul, 100, stdin);

            printf("Masukkan jenis buku: ");
            fgets(buku.jenis, 100, stdin);

            printf("Masukkan harga buku: ");
            scanf("%f", &buku.harga);
            getchar(); // buang newline biar gak ganggu input berikutnya
            // End input judul buku, jenis buku dan harga
            removeEnter(buku.judul);                                                         // Hapus enter pada judul buku
            removeEnter(buku.jenis);                                                         // Hapus enter pada jenis buku
            fprintf(file, "%s|%s|%s|%.2f\n", buku.kode, buku.judul, buku.jenis, buku.harga); // Simpan data buku ke file databuku
            puts("Data buku berhasil tersimpan!");
            fclose(file); // tutup file databuku
        }
    }
}

void addSales()
{
    FILE *file;         // Deklarasi variable yang nantinya untuk R file databuku.txt
    struct Sales sales; // Deklarasi structur sales
    char buffer[150];
    char *kodeterbaru = NULL;
    char *kodeterakhir = NULL; // inisialisasi supaya gak langsung di-free
    float hargabuku = 0;
    file = fopen(DATABUKU, "r"); // Membuka file databuku.txt

    if (file == NULL)
    {
        printf("File %s tidak bisa diakses", DATABUKU);
    }
    else
    {
        // Start input penjualan
        puts("Masukkan Data Penjualan");
        puts("--------------------");
        printf("Masukkan kode buku: ");
        scanf("%s", sales.kodebuku);

        printf("Masukkan Qty Penjualan: ");
        scanf("%d", &sales.qty);
        // End input penjualan

        while (fgets(buffer, sizeof(buffer), file) != NULL) // looping untuk membaca data buku per line
        {
            buffer[strcspn(buffer, "\n")] = 0; // merubah enter pada buffer menjadi \0
            if (buffer[0] == '\0')             // jika buffer kosong, maka langsung skip
            {
                continue;
            }
            kodeterbaru = getBookCode(buffer); // Panggil getBookCode untuk mendapatkan kode buku terakhir
            if (kodeterbaru)
            {
                if (kodeterakhir != NULL)
                    free(kodeterakhir); // pastiin gak free pointer kosong
                kodeterakhir = kodeterbaru;
            }
            if (kodeterakhir && strcmp(kodeterakhir, sales.kodebuku) == 0)
            {
                // Jika kodeterakhir sama dengan kode yang diinput, maka harga pada databuku.txt akan disimpan pada hargabuku dan looping akan break atau berhenti
                char *last_delimiter = strrchr(buffer, '|');
                char *price_start = last_delimiter + 1;
                hargabuku = atof(price_start);
                break;
            }
        }
        fclose(file);       
        if (kodeterakhir != NULL)
            free(kodeterakhir); // bebasin memori terakhir
        if (hargabuku > 0)
        {
            // Jika harga buku lebih dari 0 maka data penjualan akan langsung diinput ke datasales.txt
            sales.harga = hargabuku;
            file = fopen(DATASALES, "a");
            if (file == NULL)
            {
                printf("File %s tidak bisa diakses", DATASALES);
            }
            else
            {
                fprintf(file, "%s|%d|%.2f\n", sales.kodebuku, sales.qty, (sales.harga * sales.qty));
                puts("Transaksi berhasil dicatat");
                fclose(file);
            }
        }
        else
        {
            puts("Kode buku tidak ditemukan");
        }
    }
}

void viewBooks()
{
    FILE *file = fopen(DATABUKU, "r");
    if (!file)
    {
        printf("File %s tidak bisa diakses atau belum ada data.\n", DATABUKU);
        return;
    }

    struct Book buku;
    char buffer[200];

    printf("\n=== DAFTAR BUKU ===\n");
    printf("%-10s | %-30s | %-20s | %-15s\n", "Kode", "Judul", "Jenis", "Harga");
    printf("----------------------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        if (buffer[0] == '\0')
            continue;

        char *token = strtok(buffer, "|");
        if (token)
            strcpy(buku.kode, token);

        token = strtok(NULL, "|");
        if (token)
            strcpy(buku.judul, token);

        token = strtok(NULL, "|");
        if (token)
            strcpy(buku.jenis, token);

        token = strtok(NULL, "|");
        if (token)
            buku.harga = atof(token);

        printf("%-10s | %-30s | %-20s | Rp. %.2f\n",
               buku.kode, buku.judul, buku.jenis, buku.harga);
    }

    fclose(file);
    printf("----------------------------------------------------------------------------\n");
}