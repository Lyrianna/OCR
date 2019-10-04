CC=gcc

CPPFLAGS= `sdl2-config --cflags` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `sdl2-config --libs` -lSDL2_image

all: main

main: main.c

clean:
	${RM} *.o
	${RM} *.d

# END
