#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "formatter.h"

static char converted[1024];

void formatter_init(void) {
    converted[0] = '\0';
    printf("Formatter system initialized\n");
}

void formatter_shutdown(void) {
    if (converted[0]) {
        printf("Removing temporary file %s\n", converted);
        unlink(converted);
    }
    printf("Formatter system shutdown\n");
}

static int has_rob_extension(const char *file) {
    const char *dot = strrchr(file, '.');
    return dot && strcmp(dot, ".rob") == 0;
}

const char *formatter_autoconvert(const char *file) {
    if (has_rob_extension(file)) {
        return file;
    }

    snprintf(converted, sizeof(converted), "%s.rob", file);

    char cmd[2048];
    snprintf(cmd, sizeof(cmd), "./robformat \"%s\" \"%s\"", file, converted);
    int ret = system(cmd);
    if (ret != 0) {
        fprintf(stderr, "robformat failed, attempting to play original file\n");
        converted[0] = '\0';
        return file;
    }
    return converted;
}
