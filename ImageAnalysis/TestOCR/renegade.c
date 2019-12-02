#include "renegade.h"

SDL_Surface* renegade(SDL_Surface *letters,int *size, int averagesize){
    return letters;
    SDL_Surface *solved = malloc(sizeof(SDL_Surface));
    int solvedindex = 0;
    for(int i = 0; i < *size; i++){
        if((letters + i)->w < averagesize*2.3f){
            solved = realloc(solved,(solvedindex+1)*sizeof(SDL_Surface));
            solved[solvedindex] = *(letters + i);
            solvedindex++;
            IMG_SavePNG((solved + solvedindex - 1), "current.png");
        }
        else{
            int nbletters = 0;
            SDL_Surface *fixed = crusade(*letters,averagesize, &nbletters);
            for(int j = 0; j < nbletters;j++){
            	for(int k = 0; k < nbletters;k++){
                    IMG_SavePNG(fixed+k,"currentfixed.png");
	            }
                solved = realloc(solved, (solvedindex + 1)*sizeof(SDL_Surface));
                solved[solvedindex] = fixed[j];
                solvedindex++;
            }
        }
    }
    return solved;
}

SDL_Surface* crusade(SDL_Surface renegades, int averagesize,int *nbletters){
    SDL_Surface *solved = malloc(sizeof(SDL_Surface));
    int index = 0;
    while(index*averagesize <= renegades.w){
        solved = realloc(solved, (index+1)*sizeof(SDL_Surface));
        solved[index] = CropImage(renegades,index*averagesize, (index+1)*averagesize, 0,renegades.h);
        index++;
    }
    *nbletters = index;
    return solved;
}
