
// Bai tap 1 
void main() {
    // In n?i dung c?a 150 � FAT d?u ti�n
    printf("\n\n");
    printf("N?i dung c?a 150 � FAT d?u ti�n tr�n ? D:\n");
    for (int i = 0; i < 150; i++) {
        printf("%u ", fat[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    // In b?ng bit c?a 150 kh?i nh? c?a ? D
    printf("\n\n");
    printf("B?ng bit c?a 150 kh?i nh? c?a ? D:\n");
    for (int i = 0; i < 150; i++) {
        printf("%d ", (fat[i] & 0x0001) != 0);
        fat[i] >>= 1;
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
// Bai tap 2
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

struct BOOT {
    // ... (c�c tru?ng d� du?c d?nh nghia trong struct BOOT)
};

struct ROOT {
    // ... (c�c tru?ng d� du?c d?nh nghia trong struct ROOT)
};

void main() {
    // ... (Ph?n code tru?c d� du?c d?nh nghia)

    // �?c b?ng FAT16 v�o b? nh?
    unsigned int *fat = (unsigned int *)malloc(boot.FAT_size * boot.bytes_per_sector);
    if (fat == NULL) {
        printf("Not enough memory\n");
        return;
    }
    printf("\n\nReading FAT16 parameters\n");
    printf("__________________________\n");
    printf("FAT size: %d \n", boot.FAT_size);
    printf("Reserved: %d \n", boot.reserved);

    int res = absread(drive, boot.FAT_size, boot.reserved, fat);
    if (res != 0) {
        printf("Cannot read FAT\n");
        free(fat);
        return;
    }

    // ... (Ph?n code ti?p theo d� du?c d?nh nghia)

    // �?c t�n c?a file d?a tr�n cluster d?u ti�n n
    unsigned int n;
    printf("Nh?p cluster d?u ti�n (n): ");
    scanf("%u", &n);

    char filename[12];
    memset(filename, 0, 12); // Kh?i t?o filename th�nh chu?i tr?ng

    for (int i = 0; i < boot.ROOT_size; i++) {
        if (root[i].name[0] == 0x00 || root[i].name[0] == 0xE5) {
            continue; // D�ng n�y d�nh d?u m?c kh�ng du?c s? d?ng ho?c d� b? x�a
        }

        if (root[i].first_cluster == n) {
            // T�m th?y t?p d?a tr�n cluster d?u ti�n
            for (int j = 0; j < 8; j++) {
                if (root[i].name[j] == ' ') {
                    break; // �� d?n cu?i t�n t?p
                }
                filename[j] = root[i].name[j];
            }

            for (int j = 0; j < 3; j++) {
                if (root[i].ext[j] == ' ') {
                    break; // �� d?n cu?i ph?n m? r?ng
                }
                if (j == 0) {
                    strcat(filename, ".");
                }
                char ext_char[2];
                ext_char[0] = root[i].ext[j];
                ext_char[1] = '\0';
                strcat(filename, ext_char);
            }
        }
    }

    if (filename[0] != '\0') {
        printf("T�n t?p d?a tr�n cluster d?u ti�n %u: %s\n", n, filename);
    } else {
        printf("Kh�ng t�m th?y t?p d?a tr�n cluster d?u ti�n %u\n", n);
    }

    // ... (Ph?n code ti?p theo d� du?c d?nh nghia)

    // �?m b?o gi?i ph�ng b? nh? khi b?n d� s? d?ng malloc trong m� c?a b?n.
    free(fat);
    free(root);
}
// Bai 3 
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

struct BOOT {
    // ... (c�c tru?ng d� du?c d?nh nghia trong struct BOOT)
};

struct ROOT {
    // ... (c�c tru?ng d� du?c d?nh nghia trong struct ROOT)
};

void main() {
    // ... (Ph?n code tru?c d� du?c d?nh nghia)

    // �?c thu m?c g?c v�o b? nh?
    int num_byte = boot.ROOT_size * 32; // K�ch thu?c c?a thu m?c g?c
    ROOT *root = (ROOT *)malloc(num_byte);
    if (root == NULL) {
        printf("Not enough memory\n");
        return;
    }

    int num_sector = num_byte / boot.bytes_per_sector;
    int root_begin = boot.reserved + boot.FAT_size * boot.FAT_cnt;
    int res = absread(drive, num_sector, root_begin, (void *)root);
    if (res != 0) {
        printf("\nCannot read ROOT\n");
        free(root);
        return;
    }

    // In t�n v� d? d�i c?a c�c file trong thu m?c g?c
    printf("\nDanh s�ch c�c t?p trong thu m?c g?c:\n");
    for (int i = 0; i < boot.ROOT_size; i++) {
        if (root[i].name[0] == 0x00 || root[i].name[0] == 0xE5) {
            continue; // D�ng n�y d�nh d?u m?c kh�ng du?c s? d?ng ho?c d� b? x�a
        }

        char filename[13];
        memset(filename, 0, 13); // Kh?i t?o filename th�nh chu?i tr?ng

        for (int j = 0; j < 8; j++) {
            if (root[i].name[j] == ' ') {
                break; // �� d?n cu?i t�n t?p
            }
            filename[j] = root[i].name[j];
        }

        if (root[i].ext[0] != ' ') {
            strcat(filename, ".");
            for (int j = 0; j < 3; j++) {
                if (root[i].ext[j] == ' ') {
                    break; // �� d?n cu?i ph?n m? r?ng
                }
                char ext_char[2];
                ext_char[0] = root[i].ext[j];
                ext_char[1] = '\0';
                strcat(filename, ext_char);
            }
        }

        printf("T�n t?p: %s, �? d�i: %ld byte\n", filename, root[i].size);
    }

    // T�m t�n file du?c ch? d?nh v� t�nh k�ch thu?c c?a n�
    char search_filename[13]; // T�n t?p c?n t�m
    printf("\nNh?p t�n t?p c?n t�m: ");
    scanf("%s", search_filename);

    long file_size = -1; // K�ch thu?c t?p, -1 n?u kh�ng t�m th?y
    for (int i = 0; i < boot.ROOT_size; i++) {
        if (root[i].name[0] == 0x00 || root[i].name[0] == 0xE5) {
            continue; // D�ng n�y d�nh d?u m?c kh�ng du?c s? d?ng ho?c d� b? x�a
        }

        char filename[13];
        memset(filename, 0, 13); // Kh?i t?o filename th�nh chu?i tr?ng

        for (int j = 0; j < 8; j++) {
            if (root[i].name[j] == ' ') {
                break; // �� d?n cu?i t�n t?p
            }
            filename[j] = root[i].name[j];
        }

        if (root[i].ext[0] != ' ') {
            strcat(filename, ".");
            for (int j = 0; j < 3; j++) {
                if (root[i].ext[j] == ' ') {
                    break; // �� d?n cu?i ph?n m? r?ng
                }
                char ext_char[2];
                ext_char[0] = root[i].ext[j];
                ext_char[1] = '\0';
                strcat(filename, ext_char);
            }
        }

        if (strcmp(filename, search_filename) == 0) {
            file_size = root[i].size;
            break;
        }
    }

    if (file_size != -1) {
        printf("T?p %s c� k�ch thu?c %ld byte\n", search_filename, file_size);
    } else {
        printf("Kh�ng t�m th?y t?p %s trong thu m?c g?c\n", search_filename);
    }

    // ... (Ph?n code ti?p theo d� du?c d?nh nghia)

    // �?m b?o gi?i ph�ng b? nh? khi b?n d� s? d?ng malloc trong m� c?a b?n.
    free(root);
}
