#include <stdio.h>
#include <stdarg.h>
#include "logging.h"

void logging_init(void) {
    printf("Logging system initialized\n");
}

void logging_shutdown(void) {
    printf("Logging system shutdown\n");
}

void log_info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
