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

int loadimage(char *filename);
void BlackAndWhite(SDL_Surface* surface);
void MonoColor(SDL_Surface* surface);
void ExtractBlock(SDL_Surface* surface);
void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Please use the correct argument\n");
        return(-1);
    }
    int value = loadimage(argv[1]);
    IMG_Quit();
    SDL_Quit();
    return value;
}

int loadimage(char *filename){
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        printf("SDL failed to inilialize");
        return 1;
    }
    IMG_Init(~0);
    SDL_Surface *surface =  IMG_Load(filename);
    if(surface != NULL){
        printf("Success\n");
        BlackAndWhite(surface);
        MonoColor(surface);
        ExtractBlock(surface);
    }
    else{
        printf("Failed ! %s\n", IMG_GetError());
    }
    return 0;
}

void BlackAndWhite(SDL_Surface* surface){
    int i = 0;
    int j = 0;
    for(i = 0; i < surface->h; i++){
        for(j = 0; j < surface->w;j++){
            Uint8 red = 0;
            Uint8 green = 0;
            Uint8 blue = 0;
            Uint32 pixel = getpixel(surface,j,i);
            SDL_GetRGB(pixel, surface->format, &red, &green, &blue);
            Uint8 black = (red + green + blue)/3;
            pixel = SDL_MapRGB(surface->format, black, black, black);
            putpixel(surface,j,i,pixel);
        }
    }
    IMG_SavePNG(surface, "bw.png");
}

void MonoColor(SDL_Surface* surface){
    for(int i = 0; i < surface->h; i++){
        for(int j = 0; j < surface->w;j++){
            Uint8 red = 0;
            Uint8 green = 0;
            Uint8 blue = 0;
            Uint32 pixel = getpixel(surface,j,i);
            SDL_GetRGB(pixel, surface->format, &red, &green, &blue);
            Uint8 black = 0;
            if((red + green + blue)/3 >= 128){
                black = 255;
            }
            else{
                black = 0;
            }
            pixel = SDL_MapRGB(surface->format, black, black, black);
            putpixel(surface,j,i,pixel);
        }
    }
    IMG_SavePNG(surface, "mono.png");
}

void ExtractBlock(SDL_Surface* surface){
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
            Uint32 pixel = getpixel(surface,x,y);
            SDL_GetRGB(pixel, surface->format, &red, &green, &blue);
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
    IMG_SavePNG(surface, "selected.png");
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}
void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height)
{
    SDL_Rect pos = {x,  y, width, height};
    SDL_FillRect(surface, &pos, SDL_MapRGB(surface->format, 0, 255, 0));
}

