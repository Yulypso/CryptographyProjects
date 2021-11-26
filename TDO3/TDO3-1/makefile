CC=gcc
LDFLAGS=-Wall


all : COMPILE CLEAN LANCEMENT


COMPILE : STEGANALYSE.c
	$(CC) -o STEGANO STEGANALYSE.c `sdl-config --cflags --libs` $(LDFLAGS)

CLEAN :
	rm -rf *.o

LANCEMENT :
	./STEGANO
