//
// Created by Lyrianna on 21/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "networkV2.h"
#include <stdio.h>
#include "matrix/matrix.h"
#include <math.h>
#include <stdbool.h>
#include <err.h>

int main(int argc, char** argv)
{

    if (argc == 1 || argc>2)
        errx(1,"MAIN : No matrice is specified.");
    else
    {
        int arg = (int) atoi(argv[1]);
        switch (arg) {
            case 'train':
                train_neural();
            default:
                character_translator((char)arg);
        }
    }

    return 0;
}

