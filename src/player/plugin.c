#include <stdio.h>
#include "plugin.h"

void plugin_init(void) {
    printf("Plugin system initialized\n");
}

void plugin_shutdown(void) {
    printf("Plugin system shutdown\n");
}

int plugin_load(const char *path) {
    printf("Loading plugin: %s\n", path);
    return 0;
}
