#include <stdio.h>
#include "network.h"

void network_init(void) {
    printf("Network system initialized\n");
}

void network_shutdown(void) {
    printf("Network system shutdown\n");
}

int network_open_stream(const char *url) {
    printf("Pretending to open network stream: %s\n", url);
    return 0;
}
