#include <stdio.h>
#include <stdarg.h>
#include "logging.h"

static log_level_t current_level = LOG_INFO;

void logging_init(void) {
    printf("Logging system initialized\n");
}

void logging_shutdown(void) {
    printf("Logging system shutdown\n");
}

void logging_set_level(log_level_t level) {
    current_level = level;
}

void log_info(const char *fmt, ...) {
    if (current_level < LOG_INFO) return;
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void log_debug(const char *fmt, ...) {
    if (current_level < LOG_DEBUG) return;
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
