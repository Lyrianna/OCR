# Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O2
#CFLAGS= -g
LDFLAGS=
LDLIBS= -lm

SRC = ./nn2/networkV2.c main.c ./nn2/matrix/matrix.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

-include ${DEP}

#$(info WARNING, WARNING ARE IGNORED REMOVE -w OPTION)

clean:
	rm -f ${OBJ} ${DEP}
	rm -f main

 # END
