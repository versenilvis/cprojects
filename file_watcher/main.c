#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <dir>\n", argv[0]);
        return -1;
    }
    if (strcmp(argv[1], ".") == 0) {
        printf("Watching current directory\n");
    } else {
        printf("Watching directory %s\n", argv[1]);
    }
    return 0;
}
