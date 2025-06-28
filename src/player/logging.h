#ifndef LOGGING_H
#define LOGGING_H

void logging_init(void);
void logging_shutdown(void);
void log_info(const char *fmt, ...);

#endif /* LOGGING_H */
