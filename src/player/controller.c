#include <stdio.h>
#include "controller.h"

static controller_state_t state = STATE_STOPPED;

void controller_init(void) {
    state = STATE_STOPPED;
    printf("Playback controller initialized\n");
}

void controller_shutdown(void) {
    printf("Playback controller shutdown\n");
}

void controller_play(void) {
    state = STATE_PLAYING;
    printf("Playback started\n");
}

void controller_pause(void) {
    state = STATE_PAUSED;
    printf("Playback paused\n");
}

controller_state_t controller_state(void) {
    return state;
}
