//
//  main.c
//  TestOCR
//
//  Created by Pierre Pelletier on 02/10/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

int loadimage(void);
void BlackAndWhite(SDL_Surface* surface);

int main() {
    return loadimage();
}

int loadimage(void){
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
        BlackAndWhite(surface);
    }
    else{
        printf("Failed ! %s\n", IMG_GetError());
    }
    SDL_Quit();
    return 0;
}

void BlackAndWhite(SDL_Surface* surface){
    Uint32 *pixels = (Uint32 *)surface->pixels;
    printf("%lu\n",sizeof(pixels));
    for(int i = 0; i < surface->h; i++){
        for(int j = 0; j < surface->w;j++){
            Uint8 red = 0;
            Uint8 green = 0;
            Uint8 blue = 0;
            SDL_GetRGB(pixels[i*surface->w + j], surface->format, &red, &green, &blue);
            Uint8 black = (red + green + blue)/3;
            pixels[i*surface->w + j] = SDL_MapRGB(surface->format, black, black, black);
        }
    }
    IMG_SavePNG(surface, "lenabw.png");
    IMG_Quit();
}

