#ifndef LOGGING_H
#define LOGGING_H

typedef enum {
    LOG_ERROR = 0,
    LOG_INFO,
    LOG_DEBUG
} log_level_t;

void logging_init(void);
void logging_shutdown(void);
void logging_set_level(log_level_t level);
void log_info(const char *fmt, ...);
void log_debug(const char *fmt, ...);

#endif /* LOGGING_H */
