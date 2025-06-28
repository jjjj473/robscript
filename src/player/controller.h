#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef enum {
    STATE_STOPPED,
    STATE_PLAYING,
    STATE_PAUSED
} controller_state_t;

void controller_init(void);
void controller_shutdown(void);
void controller_play(void);
void controller_pause(void);
controller_state_t controller_state(void);

#endif /* CONTROLLER_H */
