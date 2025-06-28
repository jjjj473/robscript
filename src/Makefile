CC?=gcc
CFLAGS := $(shell pkg-config --cflags libavformat libavcodec libavutil libswscale sdl2)
LDFLAGS := $(shell pkg-config --libs libavformat libavcodec libavutil libswscale sdl2)

all: robformat robplay robplayer

robformat: robformat.o
	$(CC) -o $@ $^ $(LDFLAGS)

robplay: robplay.o
	$(CC) -o $@ $^ $(LDFLAGS)

PLAYER_OBJS := player/core.o player/logging.o player/config.o player/network.o player/plugin.o \
player/playlist.o player/controller.o player/decoder.o player/audio_output.o \
player/renderer.o player/input.o player/robplayer.o

robplayer: $(PLAYER_OBJS)
	$(CC) -o $@ $(PLAYER_OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o robformat robplay robplayer player/*.o
