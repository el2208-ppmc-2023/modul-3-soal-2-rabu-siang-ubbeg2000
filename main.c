#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 500

#define ID 0
#define NAMA 1
#define PESAN 2
#define TANGGAL 3
#define WAKTU 4

int hex_to_int(char hex)
{
    if (hex >= 48 && hex <= 57)
    {
        return hex - '0';
    }
    else
    {
        return hex - 'A' + 10;
    }
}

void decipher(char *str, int length_text, char arr2[][MAXLEN])
{
    int holder = 0;
    int cases = 0;
    int code;
    int length;
    // int index = 0;

    while (holder < length_text)
    {
        if (cases == 0)
        {
            length = hex_to_int(str[holder]) * 16 + hex_to_int(str[holder + 1]);
            holder += 2;
            cases = 1;
        }
        else if (cases == 1)
        {
            code = hex_to_int(str[holder]) * 16 + hex_to_int(str[holder + 1]);
            holder += 2;
            length -= 1;
            cases = 2;
        }
        else
        {
            int i = 0;

            while (i < length)
            {
                arr2[code][i] = hex_to_int(str[holder]) * 16 + hex_to_int(str[holder + 1]);

                i++;
                holder += 2;
            }
            cases = 0;
        }
    }
}

int main()
{
    FILE *fp;
    char filename[20];
    char buffer[MAXLEN];
    int lib1[MAXLEN];
    char content[MAXLEN][MAXLEN];
    int option;

    printf("Masukkan nama file: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File tidak ditemukan.\n");
        return 0;
    }

    fgets(buffer, MAXLEN, fp);

    fclose(fp);

    decipher(buffer, strlen(buffer), content);

    printf("\nTerjemahan Pesan:\n");
    printf("ID: %s\n", content[ID]);
    printf("Nama: %s\n", content[NAMA]);
    printf("Pesan: %s\n", content[PESAN]);
    printf("Tanggal: %s\n", content[TANGGAL]);
    printf("Waktu: %s\n", content[WAKTU]);

    return 0;
}
