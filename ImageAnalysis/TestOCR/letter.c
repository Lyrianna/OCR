//
//  letter.c
//  TestOCR
//
//  Created by Pierre Pelletier on 17/11/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#include "letter.h"

int max(int a, int b){
    if(a > b)
        return a;
    return b;
}

SDL_Surface makesquarehelper(SDL_Surface surface){
    int side = max(surface.h, surface.w);
    SDL_Surface *square = SDL_CreateRGBSurface(0, side, side, 32, 0, 0, 0, 0);
    Uint32 white = SDL_MapRGB(square->format, 255, 255, 255);
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            putpixel(square, i, j, white);
        }
    }
    for(int j = 0; j < surface.h;j++){
        for(int i = 0; i < surface.w;i++){
            Uint32 pixel = getpixel(&surface, i, j);
            putpixel(square, side/2 - surface.w/2 + i, j, pixel);
        }
    }
    return *square;
}

double* makesquare(SDL_Surface letter){
    letter = makesquarehelper(letter);
    double *matrix = malloc(28*28*sizeof(double));
    float xratio = letter.w/(float)28;
    float yratio = letter.h/(float)28;
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28;j++){
            Uint32 pixel = getpixel(&letter,i*xratio, j*yratio);
            Uint8 black;
            SDL_GetRGB(pixel,letter.format,&black,&black,&black);
            if(black == 0)
                matrix[j*28 + i] = 1.0;
        }
    }
    return matrix;
}
