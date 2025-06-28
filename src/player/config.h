#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int volume;
} config_t;

const config_t *config_get(void);
void config_init(void);
void config_shutdown(void);

#endif /* CONFIG_H */
