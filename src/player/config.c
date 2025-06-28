#include <stdio.h>
#include <stdlib.h>
#include "config.h"

static config_t cfg;

const config_t *config_get(void) {
    return &cfg;
}

void config_init(void) {
    const char *env = getenv("ROBPLAYER_VOLUME");
    cfg.volume = env ? atoi(env) : 100;
    printf("Config system initialized (volume=%d)\n", cfg.volume);
}

void config_shutdown(void) {
    printf("Config system shutdown\n");
}
