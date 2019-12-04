# Compilers and options
CC=gcc #-fsanitize=address -g
CPPFLAGS= `sdl-2config --cflags` -MMD
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O2
#CFLAGS= -g
LDFLAGS= `sdl2-config --libs`
LDLIBS= `sdl2-config --libs` -lSDL2_image -lm 
DEPS= ImageAnalysis/TestOCR/*.h ./nn2/networkV2.h ./nn2/matrix/matrix.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: main.o ./ImageAnalysis/TestOCR/letter.o ./ImageAnalysis/TestOCR/renegade.o ./ImageAnalysis/TestOCR/segmentation.o ./ImageAnalysis/TestOCR/otsu.o ./ImageAnalysis/TestOCR/loadandprocess.o ./nn2/networkV2.o ./nn2/matrix/matrix.o copy
	$(CC) -o OCR $(shell ls ./build/*.o) $(LDLIBS)

#$(info WARNING, WARNING ARE IGNORED REMOVE -w OPTION)

copy: 
	$(shell mkdir -p build)
	$(shell cp ./ImageAnalysis/TestOCR/*.o ./build/)
	$(shell cp ./nn2/*.o ./build/)
	$(shell cp ./nn2/matrix/*.o ./build/)
	$(shell cp main.o ./build/)

clean:
	rm -f ${OBJ} ${DEP}
	rm -f OCR
	rm -f *.o
	$(shell rm -f ./ImageAnalysis/TestOCR/*.o ./build/*.o ./nn2/*.o ./nn2/matrix/*.o)
	rm -rf build

 # END
