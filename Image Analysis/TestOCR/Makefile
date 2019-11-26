CC=gcc -g

CPPFLAGS= `sdl2-config --cflags` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99
LDFLAGS= `sdl2-config --libs`
LDLIBS= `sdl2-config --libs` -lSDL2_image
DEPS= letter.h segmentation.h otsu.h loadandprocess.h main.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDLIBS)


all: letter.o otsu.o segmentation.o loadandprocess.o main.o
	$(CC) -o OCR main.o segmentation.o letter.o otsu.o loadandprocess.o $(LDLIBS)

clean:
	${RM} *.o
	${RM} *.d
	${RM} OCR
	${RM} *.png
