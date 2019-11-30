CC=gcc -g

CPPFLAGS= `sdl2-config --cflags` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99
LDFLAGS= `sdl2-config --libs`
LDLIBS= `sdl2-config --libs` -lSDL2_image
DEPS= nn2/networkV2.h nn2/matrix/matrix.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDLIBS)


all: main.o nn2/networkV2.o nn2/matrix/matrix.h
	$(CC) -o OCR main.o $(LDLIBS)

clean:
	${RM} *.o
	${RM} *.d
	${RM} OCR
	${RM} *.png