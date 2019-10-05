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
void MonoColor(SDL_Surface* surface);
void ExtractBlock(SDL_Surface* surface);
SDL_Surface CropImg(SDL_Surface* surface,int x1,int x2,int y1, int y2);
void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height);

int main() {
    int value = loadimage();
    IMG_Quit();
    SDL_Quit();
    return value;
}

int loadimage(void){
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    IMG_Init(0);
    IMG_Init(~0);
    SDL_Surface *surface =  IMG_Load("lena.png");
    if(surface != NULL){
        printf("Success\n");
        //BlackAndWhite(surface);
        MonoColor(surface);
        ExtractBlock(surface);
    }
    else{
        printf("Failed ! %s\n", IMG_GetError());
    }
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
    IMG_SavePNG(surface, "textbw.png");
}

void MonoColor(SDL_Surface* surface){
    Uint32 *pixels = (Uint32 *)surface->pixels;
    printf("%lu\n",sizeof(pixels));
    for(int i = 0; i < surface->h; i++){
        for(int j = 0; j < surface->w;j++){
            Uint8 red = 0;
            Uint8 green = 0;
            Uint8 blue = 0;
            SDL_GetRGB(pixels[i*surface->w + j], surface->format, &red, &green, &blue);
            Uint8 black = 0;
            if((red + green + blue)/3 >= 128){
                black = 255;
            }
            else{
                black = 0;
            }
            pixels[i*surface->w + j] = SDL_MapRGB(surface->format, black, black, black);
        }
    }
    IMG_SavePNG(surface, "textmono.png");
}

void ExtractBlock(SDL_Surface* surface){
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int xstart = 0;
    int xend = 0;
    int ystart = 0;
    int yend = 0;
    int firstmatch = 1;
    int lastwasblack = 0;
    for(int y = 0; y < surface->h; y++){ //y
        for(int x = 0; x < surface->w;x++){ //x
            Uint8 red = 0;
            Uint8 green = 0;
            Uint8 blue = 0;
            SDL_GetRGB(pixels[y*surface->w + x], surface->format, &red, &green, &blue);
            if(red == 0){
                if(firstmatch == 1|| xstart > x){
                    xstart = x;
                    if(firstmatch == 1){
                        ystart = y;
                        firstmatch = 0;
                    }
                }
                lastwasblack = 1;
                yend = y;
            }
            else{
                if(lastwasblack == 1){
                    if(x > xend){
                        xend = x;
                    }
                }
                lastwasblack = 0;
            }
        }
    }
    draw_rectangle(surface, xstart, ystart, xend - xstart, 1);
    draw_rectangle(surface, xstart, ystart, 1, yend - ystart);
    draw_rectangle(surface, xend, ystart, 1, yend - ystart);
    draw_rectangle(surface, xstart, yend, xend - xstart, 1);
}

SDL_Surface CropImg(SDL_Surface* surface,int x1,int x2,int y1, int y2){
    SDL_Rect crop;
    crop.x = x1;
    crop.y = y1;
    crop.h = y2 - y1;
    crop.w = x2 - x1;
    SDL_BlitSurface(surface,NULL,NULL,&crop);
    return *surface;
}

void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height)
{
    SDL_Rect pos = {x,  y, width, height};
    SDL_FillRect(surface, &pos, SDL_MapRGB(surface->format, 0, 255, 0));
    IMG_SavePNG(surface, "cropped.png");
}

