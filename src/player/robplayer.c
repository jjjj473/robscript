#include "core.h"
#include "logging.h"
#include "input.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        log_info("Usage: %s <video file>\n", argv[0]);
        return 1;
    }

    if (core_init(argv[1]) != 0) {
        return 1;
    }

    log_info("Running robplayer...\n");
    for (int i = 0; i < 3; ++i) {
        input_process();
    }

    core_shutdown();
    return 0;
}
