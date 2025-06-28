#include <stdio.h>
#include "audio_output.h"

void audio_output_init(int volume) {
    printf("Audio output system initialized (volume=%d)\n", volume);
}

void audio_output_shutdown(void) {
    printf("Audio output system shutdown\n");
}
