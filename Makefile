# Compilers and options
CC=gcc -g -fsanitize=address
CPPFLAGS= `sdl-2config --cflags` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -pedantic -O2
#CFLAGS= -g
LDFLAGS= `sdl2-config --libs`
LDLIBS= `sdl2-config --libs` -lSDL2_image -lm 
DEPS= ImageAnalysis/TestOCR/renegade.h ImageAnalysis/TestOCR/letter.h ImageAnalysis/TestOCR/segmentation.h ImageAnalysis/TestOCR/otsu.h ImageAnalysis/TestOCR/loadandprocess.h ./nn2/networkV2.h ./nn2/matrix/matrix.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: main.o ./ImageAnalysis/TestOCR/letter.o ./ImageAnalysis/TestOCR/renegade.o ./ImageAnalysis/TestOCR/segmentation.o ./ImageAnalysis/TestOCR/otsu.o ./ImageAnalysis/TestOCR/loadandprocess.o ./nn2/networkV2.o ./nn2/matrix/matrix.o
	$(CC) -o OCR *.o $(LDLIBS)

#$(info WARNING, WARNING ARE IGNORED REMOVE -w OPTION)

clean:
	rm -f ${OBJ} ${DEP}
	rm -f main
	rm -f OCR
	rm -f *.o
	rm -f *.d

 # END
