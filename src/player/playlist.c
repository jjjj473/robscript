#include <stdio.h>
#include <string.h>
#include "playlist.h"

static char current_file[1024];

void playlist_init(void) {
    current_file[0] = '\0';
    printf("Playlist system initialized\n");
}

void playlist_shutdown(void) {
    printf("Playlist system shutdown\n");
}

void playlist_add(const char *file) {
    strncpy(current_file, file, sizeof(current_file)-1);
    current_file[sizeof(current_file)-1] = '\0';
    printf("Added %s to playlist\n", current_file);
}

const char *playlist_current(void) {
    return current_file;
}
