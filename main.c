//
// Created by Néphélie Lambrinidis on 21/11/2019.
//


#include "./ImageAnalysis/TestOCR/letter.h"

#include <stdio.h>
#include "nn2/networkV2.h"
#include "nn2/matrix/matrix.h"
#include <string.h>
#include <SDL2/SDL.h>

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
            FILE* fichier = fopen("text.txt", "w");
            
	    int size = 0;

	    if (fichier!=NULL)
	    {
	    	Letter* letters = seg_segmentation(arg,&size);
            	for (int i = 0; i < size; ++i) {
                	printf("letter");
			if(letters[i].newline==0)
			{		Matrix* input = initwithvaluesM(1, 784, letters[i].matrix);
                		ocr(input, fichier);
			}
            	}

            	fclose(fichier);
	    }
        }

    }
	freeAll();
    return 0;
}
