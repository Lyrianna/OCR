//
//  letter.h
//  TestOCR
//
//  Created by Pierre Pelletier on 17/11/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#ifndef letter_h
#define letter_h

#include <SDL2/SDL.h>

typedef struct Letter{
    int posx;
    int posy;
    SDL_Surface image;
    int **matrix;
} Letter;


int** makesquare(SDL_Surface letter);
SDL_Surface makesquarehelper(SDL_Surface surface);
int max(int a, int b);

#include "loadandprocess.h"

#endif /* letter_h */
