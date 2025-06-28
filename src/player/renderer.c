#include <stdio.h>
#include "renderer.h"

void renderer_init(int width, int height) {
    printf("Renderer system initialized (%dx%d)\n", width, height);
}

void renderer_shutdown(void) {
    printf("Renderer system shutdown\n");
}
