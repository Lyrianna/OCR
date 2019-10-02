//
//  main.c
//  TestOCR
//
//  Created by Pierre Pelletier on 02/10/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

void print_init_flags(int flags);

int main(int argc, const char * argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    IMG_Init(0);
    IMG_Init(~0);
    SDL_Surface *surface =  IMG_Load("lena.bmp");
    if(surface != NULL){
        printf("Success\n");
    }
    else{
        printf("Failed ! %s\n", IMG_GetError());
    }
    return 0;
}

