//
// Created by Lyrianna on 21/11/2019.
//
#include <stdio.h>
//#include <stdlib.h>
#include "networkV2.h"
#include "matrix/matrix.h"
//#include <math.h>

int main(int argc, char** argv)
{
    double xorx[] = {
            0,0,1,0,0,1,1,1,1,0,1,0
    };

    double wanted_ouput[] = {
            0,
	    1,
	    0,
	    0,
            1,
            1,
            1
    };

    Matrix* xor = initwithvaluesM(4,3, xorx);
    Matrix* wanted_output = initwithvaluesM(1,7,wanted_ouput);
    /*if (argc == 1 || argc>2)
        errx(1,"MAIN : No matrice is specified.");
    else
    {
        int arg = (int) atoi(argv[1]);
        switch (arg) {
            case 'train':
                train_neural(xor,wanted_output);
            default:
                character_translator((char)arg);
        }
    }*/
    train_neural(xor,wanted_output);
    //character_translator(xor,"miaou.txt");

    //freeM(xor);
    //freeM(wanted_output);

    return 0;
}
