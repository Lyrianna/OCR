//
// Created by Néphélie Lambrinidis on 21/11/2019.
//


#include "./ImageAnalysis/TestOCR/letter.h"

#include <stdio.h>
#include "nn2/networkV2.h"
#include "nn2/matrix/matrix.h"
#include <string.h>
//#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
    if (argc == 1 || argc>3)
        errx(1,"MAIN : No matrice is specified.");
    else
    {
        char* arg = argv[1];
        bool istherearg = (argc==3) ? true : false ;
	printf("miaou");
        if (strcmp(arg, "train") == 0)
        {
            train_neural(istherearg,(int) atoi(argv[2]));
        }
        else
        {
		    printf("1main");
		        int size = 0;
                Letter* letters = seg_segmentation(arg,&size);
            
	        for (int i = 0; i < size; ++i) {
                float *tableau = (float*) letters[i].matrix;
                    Matrix* input = initwithvaluesM(1, 784, tableau);
                    printM(input,"input");
		    //ocr(input);
	        }
        }

    }

    //Matrix* test = loadM("../BDI/Training/arialalphabet/10");
	freeAll();
    return 0;
}

