CC?=gcc
CFLAGS := $(shell pkg-config --cflags libavformat libavcodec libavutil libswscale sdl2)
LDFLAGS := $(shell pkg-config --libs libavformat libavcodec libavutil libswscale sdl2)

all: robplayer

# standalone converter and simple player removed

MP4_OBJS := player/mp4_demuxer.o player/mp4_muxer.o player/mp4_parser.o \
player/mp4_metadata.o player/mp4_stream.o player/mp4_index.o \
player/mp4_cache.o player/mp4_thumbnail.o player/mp4_chapter.o \
player/mp4_subtitle.o player/mp4_encryption.o player/mp4_quality.o

PLAYER_OBJS := player/core.o player/logging.o player/config.o player/network.o player/plugin.o \
player/playlist.o player/formatter.o player/controller.o player/decoder.o \
player/audio_output.o player/renderer.o player/input.o $(MP4_OBJS) player/robplayer.o

robplayer: $(PLAYER_OBJS)
	$(CC) -o $@ $(PLAYER_OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o robplayer player/*.o
