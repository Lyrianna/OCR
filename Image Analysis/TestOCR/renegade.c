#include "renegade.h"

SDL_Surface* renegade(SDL_Surface *letters,int *size, int averagesize){
    return letters;
    SDL_Surface *newletters = malloc(sizeof(SDL_Surface));
    int newindex = 0;
    int index = 0;
    for(int i = 0; i < *size; i++){
        if((letters + i)->w >= averagesize*2){
            SDL_Surface *renegades = (letters+i);
            int fixedsize = 0;
            SDL_Surface *fixed = crusade(renegades,&fixedsize,averagesize);
            newletters = realloc(newletters, (newindex + fixedsize + 5)*sizeof(SDL_Surface));
            for(int k = 0; k < fixedsize; k++){
                newletters[newindex] = fixed[k];
                newindex++;
            }
        }
        else{
            newletters = realloc(newletters,(newindex + 1)*sizeof(SDL_Surface));
            newletters[newindex] = letters[index];
            newindex++;
        }
    }
    *size = newindex + 1;
    return newletters;
}

SDL_Surface* crusade(SDL_Surface *renegades, int *size, int averagesize){
    if(averagesize != 0){
        int currentpos = averagesize;
        int lastpos = 0;
        SDL_Surface *fixed = malloc((renegades->w)/averagesize*sizeof(SDL_Surface));
        int index = 0;
        while(renegades->w > currentpos){
            fixed[index] = CropImage(*renegades,lastpos,currentpos,0,renegades->h);
            lastpos = currentpos;
            currentpos = (index + 1)*averagesize;
            index++;
        }
        *size = index +1;
        return fixed;
    }
    else{
        return renegades;
    }
}