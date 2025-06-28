#include <stdio.h>
#include "decoder.h"

void decoder_init(void) {
    printf("Decoder system initialized\n");
}

void decoder_shutdown(void) {
    printf("Decoder system shutdown\n");
}

int decoder_open(const char *file) {
    printf("Pretending to open decoder for %s\n", file);
    return 0;
}
