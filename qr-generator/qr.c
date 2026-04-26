#include "qrcodegen.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printQr(const uint8_t qrcode[]) {
    printf("QR Code:\n");
    int size = qrcodegen_getSize(qrcode);
    int border = 4;
    for (int y = -border; y < size + border; y++) {
        for (int x = -border; x < size + border; x++) {
            bool val = qrcodegen_getModule(qrcode, x, y);
            fputs(qrcodegen_getModule(qrcode, x, y) ? "██" : "  ", stdout);
        }
        fputs("\n", stdout);
    }
    fputs("\n", stdout);
}

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     printf("Usage: %s <link>", argv[0]);
    // }
    char link[qrcodegen_BUFFER_LEN_MAX];
    // char *link = argv[1];
    // scanf("%[^\n]", link); -> include space
    printf("Please enter a link: ");
    while (1) {
        if (fgets(link, sizeof(link), stdin) == NULL) {
            printf("Please enter a link: ");
            continue;
        }
        link[strcspn(link, "\n")] = '\0'; // remove \n in the end
        if (strlen(link) == 0) {
            printf("Please enter a link: ");
            continue;
        }
        if (strncmp(link, "http", 4) == 0) {
            break;
        } else {
            printf("Link must start with \"http://\"or \"https://\": ");
            continue;
        }
    }
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;

    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(link, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX,
                                   qrcodegen_Mask_AUTO, true);
    if (ok)
        printQr(qrcode);
    return 0;
}
