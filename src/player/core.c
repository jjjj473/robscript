#include <stdio.h>
#include "core.h"
#include "logging.h"
#include "config.h"
#include "network.h"
#include "plugin.h"
#include "playlist.h"
#include "controller.h"
#include "decoder.h"
#include "audio_output.h"
#include "renderer.h"
#include "input.h"

int core_init(int argc, char **argv) {
    (void)argc; (void)argv;
    logging_init();
    config_init();
    network_init();
    plugin_init();
    playlist_init();
    decoder_init();
    audio_output_init();
    renderer_init();
    controller_init();
    input_init();
    printf("Core initialized with all systems\n");
    return 0;
}

void core_shutdown(void) {
    input_shutdown();
    controller_shutdown();
    renderer_shutdown();
    audio_output_shutdown();
    decoder_shutdown();
    playlist_shutdown();
    plugin_shutdown();
    network_shutdown();
    config_shutdown();
    logging_shutdown();
    printf("Core shutdown complete\n");
}
