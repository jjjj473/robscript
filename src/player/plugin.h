#ifndef PLUGIN_H
#define PLUGIN_H

void plugin_init(void);
void plugin_shutdown(void);
int plugin_load(const char *path);

#endif /* PLUGIN_H */
