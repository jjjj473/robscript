CC?=gcc
CFLAGS?=-Wall -Wextra -std=c99

all: robbuilder

robbuilder: robbuilder.o
	$(CC) $(CFLAGS) -o $@ robbuilder.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o robbuilder
