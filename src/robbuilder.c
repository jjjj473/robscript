#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source files> [-o output]\n", argv[0]);
        return 1;
    }

    const char *out = "a.out";
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            out = argv[i + 1];
            argv[i] = argv[i + 1] = NULL;
            break;
        }
    }

    char cmd[1024] = "gcc -I../blocks ../blocks/*.c";
    for (int i = 1; i < argc; ++i) {
        if (argv[i] && strcmp(argv[i], "-o") != 0) {
            strcat(cmd, " ");
            strcat(cmd, argv[i]);
        }
    }
    strcat(cmd, " -o ");
    strcat(cmd, out);

    printf("Running: %s\n", cmd);
    return system(cmd);
}
