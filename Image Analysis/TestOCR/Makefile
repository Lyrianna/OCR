CC=gcc -g

CPPFLAGS= `sdl2-config --cflags` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99
LDFLAGS= `sdl2-config --libs`
LDLIBS= `sdl2-config --libs` -lSDL2_image
DEPS= renegade.h letter.h segmentation.h otsu.h loadandprocess.h main.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all: letter.o renegade.o otsu.o segmentation.o loadandprocess.o main.o
	$(CC) -o OCR *.o $(LDLIBS)

clean:
	${RM} *.o
	${RM} *.d
	${RM} OCR
	${RM} *.png
