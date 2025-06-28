CC?=gcc
CFLAGS := $(shell pkg-config --cflags libavformat libavcodec libavutil libswscale sdl2)
LDFLAGS := $(shell pkg-config --libs libavformat libavcodec libavutil libswscale sdl2)

all: robformat robplay

robformat: robformat.o
	$(CC) -o $@ $^ $(LDFLAGS)

robplay: robplay.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o robformat robplay
