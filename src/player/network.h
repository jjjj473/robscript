#ifndef NETWORK_H
#define NETWORK_H

void network_init(void);
void network_shutdown(void);
int network_open_stream(const char *url);

#endif /* NETWORK_H */
