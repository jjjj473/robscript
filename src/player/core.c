#include <stdio.h>
#include "core.h"
#include "logging.h"
#include "config.h"
#include "network.h"
#include "formatter.h"
#include "plugin.h"
#include "playlist.h"
#include "controller.h"
#include "decoder.h"
#include "audio_output.h"
#include "renderer.h"
#include "input.h"
#include "mp4_demuxer.h"
#include "mp4_muxer.h"
#include "mp4_parser.h"
#include "mp4_metadata.h"
#include "mp4_stream.h"
#include "mp4_index.h"
#include "mp4_cache.h"
#include "mp4_thumbnail.h"
#include "mp4_chapter.h"
#include "mp4_subtitle.h"
#include "mp4_encryption.h"
#include "mp4_quality.h"

int core_init(const char *file) {
    logging_init();
    config_init();
    network_init();
    plugin_init();
    playlist_init();
    formatter_init();
    decoder_init();
    mp4_demuxer_init();
    mp4_muxer_init();
    mp4_parser_init();
    mp4_metadata_init();
    mp4_stream_init();
    mp4_index_init();
    mp4_cache_init();
    mp4_thumbnail_init();
    mp4_chapter_init();
    mp4_subtitle_init();
    mp4_encryption_init();
    mp4_quality_init();

    const config_t *cfg = config_get();
    audio_output_init(cfg->volume);
    renderer_init(640, 480);
    controller_init();
    input_init();

    if (file) {
        const char *play_file = formatter_autoconvert(file);
        playlist_add(play_file);
        decoder_open(play_file);
    }

    controller_play();
    printf("Core initialized with all systems\n");
    return 0;
}

void core_shutdown(void) {
    input_shutdown();
    controller_shutdown();
    renderer_shutdown();
    audio_output_shutdown();
    decoder_shutdown();
    mp4_quality_shutdown();
    mp4_encryption_shutdown();
    mp4_subtitle_shutdown();
    mp4_chapter_shutdown();
    mp4_thumbnail_shutdown();
    mp4_cache_shutdown();
    mp4_index_shutdown();
    mp4_stream_shutdown();
    mp4_metadata_shutdown();
    mp4_parser_shutdown();
    mp4_muxer_shutdown();
    mp4_demuxer_shutdown();
    formatter_shutdown();
    playlist_shutdown();
    plugin_shutdown();
    network_shutdown();
    config_shutdown();
    logging_shutdown();
    printf("Core shutdown complete\n");
}
