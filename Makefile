CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2

OBJS = main.o encode.o decode.o

all: rle

rle: $(OBJS)
	$(CC) $(CFLAGS) -o rle $(OBJS)

main.o: main.c rle.h
encode.o: encode.c rle.h
decode.o: decode.c rle.h

clean:
	rm -f *.o rle
