//
// Created by Lyrianna on 21/11/2019.
//
#include <stdio.h>
#include "nn2/networkV2.h"
#include "nn2/matrix/matrix.h"
#include <string.h>
#include <SDL2/SDL.h>
#include "Image Analysis/TestOCR/segmentation.h"

int main(int argc, char** argv)
{
    if (argc == 1 || argc>3)
        errx(1,"MAIN : No matrice is specified.");
    else
    {
        char* arg = argv[1];
        bool istherearg = (argc==3) ? true : false ;

        if (strcmp(arg, "train") == 0)
        {
            train_neural(istherearg,(int) atoi(argv[2]));
        }

        else
        {
            Letter* letters = seg_segmentation(argv[2],size);
            //TODO: space
            for (int i = 0; i < size; ++i) {
                Matrix* input = initwithvaluesM(28, 28, (double *) letters[i].matrix);
                ocr(input);
            }
        }

    }

    Matrix* test = loadM("../BDI/Training/arialalphabet/10");

    return 0;
}

