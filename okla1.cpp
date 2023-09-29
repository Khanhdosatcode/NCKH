
// Bai tap 1 
void main() {
    // In n?i dung c?a 150 ô FAT d?u tiên
    printf("\n\n");
    printf("N?i dung c?a 150 ô FAT d?u tiên trên ? D:\n");
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
    // ... (các tru?ng dã du?c d?nh nghia trong struct BOOT)
};

struct ROOT {
    // ... (các tru?ng dã du?c d?nh nghia trong struct ROOT)
};

void main() {
    // ... (Ph?n code tru?c dã du?c d?nh nghia)

    // Ð?c b?ng FAT16 vào b? nh?
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

    // ... (Ph?n code ti?p theo dã du?c d?nh nghia)

    // Ð?c tên c?a file d?a trên cluster d?u tiên n
    unsigned int n;
    printf("Nh?p cluster d?u tiên (n): ");
    scanf("%u", &n);

    char filename[12];
    memset(filename, 0, 12); // Kh?i t?o filename thành chu?i tr?ng

    for (int i = 0; i < boot.ROOT_size; i++) {
        if (root[i].name[0] == 0x00 || root[i].name[0] == 0xE5) {
            continue; // Dòng này dánh d?u m?c không du?c s? d?ng ho?c dã b? xóa
        }

        if (root[i].first_cluster == n) {
            // Tìm th?y t?p d?a trên cluster d?u tiên
            for (int j = 0; j < 8; j++) {
                if (root[i].name[j] == ' ') {
                    break; // Ðã d?n cu?i tên t?p
                }
                filename[j] = root[i].name[j];
            }

            for (int j = 0; j < 3; j++) {
                if (root[i].ext[j] == ' ') {
                    break; // Ðã d?n cu?i ph?n m? r?ng
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
        printf("Tên t?p d?a trên cluster d?u tiên %u: %s\n", n, filename);
    } else {
        printf("Không tìm th?y t?p d?a trên cluster d?u tiên %u\n", n);
    }

    // ... (Ph?n code ti?p theo dã du?c d?nh nghia)

    // Ð?m b?o gi?i phóng b? nh? khi b?n dã s? d?ng malloc trong mã c?a b?n.
    free(fat);
    free(root);
}
// Bai 3 
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>

struct BOOT {
    // ... (các tru?ng dã du?c d?nh nghia trong struct BOOT)
};

struct ROOT {
    // ... (các tru?ng dã du?c d?nh nghia trong struct ROOT)
};

void main() {
    // ... (Ph?n code tru?c dã du?c d?nh nghia)

    // Ð?c thu m?c g?c vào b? nh?
    int num_byte = boot.ROOT_size * 32; // Kích thu?c c?a thu m?c g?c
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

    // In tên và d? dài c?a các file trong thu m?c g?c
    printf("\nDanh sách các t?p trong thu m?c g?c:\n");
    for (int i = 0; i < boot.ROOT_size; i++) {
        if (root[i].name[0] == 0x00 || root[i].name[0] == 0xE5) {
            continue; // Dòng này dánh d?u m?c không du?c s? d?ng ho?c dã b? xóa
        }

        char filename[13];
        memset(filename, 0, 13); // Kh?i t?o filename thành chu?i tr?ng

        for (int j = 0; j < 8; j++) {
            if (root[i].name[j] == ' ') {
                break; // Ðã d?n cu?i tên t?p
            }
            filename[j] = root[i].name[j];
        }

        if (root[i].ext[0] != ' ') {
            strcat(filename, ".");
            for (int j = 0; j < 3; j++) {
                if (root[i].ext[j] == ' ') {
                    break; // Ðã d?n cu?i ph?n m? r?ng
                }
                char ext_char[2];
                ext_char[0] = root[i].ext[j];
                ext_char[1] = '\0';
                strcat(filename, ext_char);
            }
        }

        printf("Tên t?p: %s, Ð? dài: %ld byte\n", filename, root[i].size);
    }

    // Tìm tên file du?c ch? d?nh và tính kích thu?c c?a nó
    char search_filename[13]; // Tên t?p c?n tìm
    printf("\nNh?p tên t?p c?n tìm: ");
    scanf("%s", search_filename);

    long file_size = -1; // Kích thu?c t?p, -1 n?u không tìm th?y
    for (int i = 0; i < boot.ROOT_size; i++) {
        if (root[i].name[0] == 0x00 || root[i].name[0] == 0xE5) {
            continue; // Dòng này dánh d?u m?c không du?c s? d?ng ho?c dã b? xóa
        }

        char filename[13];
        memset(filename, 0, 13); // Kh?i t?o filename thành chu?i tr?ng

        for (int j = 0; j < 8; j++) {
            if (root[i].name[j] == ' ') {
                break; // Ðã d?n cu?i tên t?p
            }
            filename[j] = root[i].name[j];
        }

        if (root[i].ext[0] != ' ') {
            strcat(filename, ".");
            for (int j = 0; j < 3; j++) {
                if (root[i].ext[j] == ' ') {
                    break; // Ðã d?n cu?i ph?n m? r?ng
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
        printf("T?p %s có kích thu?c %ld byte\n", search_filename, file_size);
    } else {
        printf("Không tìm th?y t?p %s trong thu m?c g?c\n", search_filename);
    }

    // ... (Ph?n code ti?p theo dã du?c d?nh nghia)

    // Ð?m b?o gi?i phóng b? nh? khi b?n dã s? d?ng malloc trong mã c?a b?n.
    free(root);
}
