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
            0,1,1,0,1,1,0,0
    };

    double wanted_ouput[] = {
            0,
            0,
            1,
            0
    };

    Matrix* xor = initwithvaluesM(4,2, xorx);
    Matrix* wanted_output = initwithvaluesM(1,4,wanted_ouput);

    if (argc == 1 || argc>3)
        errx(1,"MAIN : No matrice is specified.");
    else
    {
        int arg = (int) atoi(argv[1]);

        bool istherearg = (argc==3) ? true : false ;

        switch (arg) {
            case 'train':
                train_neural(xor,wanted_output,istherearg,(int) atoi(argv[2]));
            default:
                return 1;
                //character_translator(in,filename,istherearg,argv[2]);
        }
    }

    return 0;
}

