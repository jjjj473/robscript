#ifndef PLAYLIST_H
#define PLAYLIST_H

void playlist_init(void);
void playlist_shutdown(void);
void playlist_add(const char *file);
const char *playlist_current(void);

#endif /* PLAYLIST_H */
