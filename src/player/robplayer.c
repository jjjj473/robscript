#include "core.h"
#include "logging.h"

int main(int argc, char **argv) {
    if (core_init(argc, argv) != 0) {
        return 1;
    }

    // Placeholder for main loop
    log_info("Running robplayer...\n");

    core_shutdown();
    return 0;
}
