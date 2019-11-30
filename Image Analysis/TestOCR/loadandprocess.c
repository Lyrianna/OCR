//
//  loadandprocess.c
//  TestOCR
//
//  Created by Pierre Pelletier on 17/11/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#include "loadandprocess.h"

/* 1: BlackAndWhite
   2: Otsu
   3: ExtractBlock
   4: ExtraLetters
 */
int loadimage(char *filename, SDL_Surface *seg_letters,int *nbletters){
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        printf("SDL failed to inilialize");
        return 1;
    }
    IMG_Init(~0);
    SDL_Surface *surface =  IMG_Load(filename);
    if(surface != NULL){
        printf("SDL Initialized\n");
        BlackAndWhite(surface);
        MonoColor(surface);
        ExtractBlock(surface);
        ExtractLetters(surface,seg_letters,nbletters);
        printf("Letters have been extracted\n");
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
    int threesold = otsu(surface);
    for(int i = 0; i < surface->h; i++){
        for(int j = 0; j < surface->w;j++){
            Uint8 red = 0;
            Uint8 green = 0;
            Uint8 blue = 0;
            Uint32 pixel = getpixel(surface,j,i);
            SDL_GetRGB(pixel, surface->format, &red, &green, &blue);
            Uint8 black = 0;
            if((red + green + blue)/3 >= threesold){
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
    for(int y = 0; y < surface->h; y++){
        for(int x = 0; x < surface->w;x++){
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
    /*draw_rectangle(surface, xstart, ystart, xend - xstart, 1);
    draw_rectangle(surface, xstart, ystart, 1, yend - ystart);
    draw_rectangle(surface, xend, ystart, 1, yend - ystart);
    draw_rectangle(surface, xstart, yend, xend - xstart, 1);
    IMG_SavePNG(surface, "selected.png");*/
    SDL_Surface cropped = CropImage(*surface, xstart, xend, ystart, yend);
    IMG_SavePNG(&cropped, "cropped.png");
}

void ExtractLetters(SDL_Surface *surface,SDL_Surface *seg_letters,int *totalsize){
    size_t *arraysize = malloc(sizeof(size_t));
    SDL_Surface *lines = GetLines(*surface,arraysize);
    int letterindex = 0;
    for(size_t i = 0; i < (*arraysize); i++){
        *(lines + i) = ImproveLine(*(lines + i));
        size_t *nbletters = malloc(sizeof(size_t));
        SDL_Surface *letters = GetLetters(*(lines + i), nbletters);
        seg_letters = realloc(seg_letters,(*nbletters + (size_t)letterindex + 1)*sizeof(SDL_Surface));
        for(size_t j = 0; j < *nbletters; j++){
            *(letters + j) = ImproveLetter(*(letters + j));
            if((*(letters + j)).w != 0 && (*(letters + j)).h != 0){
                *(seg_letters + letterindex) = *(letters + j);
                letterindex++;
            }
        }
    }
    *totalsize = letterindex;
}

SDL_Surface CropImage(SDL_Surface surface, int x1,int x2, int y1,int y2){
    SDL_Rect rect;
    rect.x = x1;
    rect.y = y1;
    rect.h = y2 - y1;
    rect.w = x2 - x1;
    SDL_Surface *cropped = SDL_CreateRGBSurface((&surface)->flags, rect.w, rect.h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(&surface,&rect,cropped,NULL);
    return *cropped;
}

SDL_Surface ImproveLine(SDL_Surface surface){
    for(int y = 0; y < surface.h; y++){
        int blackinline = 0;
        for(int x = 0; x < surface.w;x++){
            Uint8 black;
            Uint32 pixel = getpixel(&surface, x, y);
            SDL_GetRGB(pixel, surface.format, &black, &black, &black);
            if(black == 0){
                blackinline = 1;
            }
        }
        if(blackinline == 0){
            surface = CropImage(surface, 0, surface.w, 0, y);
            break;
        }
    }
    return surface;
}

SDL_Surface ImproveLetter(SDL_Surface surface){
    int asbeenblack = 0;
    for(int x = 0; x < surface.w; x++){
        int blackinline = 0;
        for(int y = 0; y < surface.h;y++){
            Uint8 black;
            Uint32 pixel = getpixel(&surface, x, y);
            SDL_GetRGB(pixel, surface.format, &black, &black, &black);
            if(black == 0){
                blackinline = 1;
                asbeenblack = 1;
            }
        }
        if(blackinline == 0 && asbeenblack == 0){
            surface = CropImage(surface,0 , x, 0, surface.h);
        }
        else if(blackinline == 0){
            surface = CropImage(surface, 0,x,0, surface.h);
            break;
        }
    }
    return surface;
}

SDL_Surface* GetLetters(SDL_Surface surface, size_t *arraysize){
    SDL_Surface *letters = malloc(sizeof(SDL_Surface));
    int blackinline = 1;
    int lastwaswhite = 0;
    int index = 0;
    *arraysize = 1;
    int previous_x = 0;
    int average = 0;
    for(int x = 0; x < surface.w; x++){
        if(blackinline == 0){
            lastwaswhite = 1;
        }
        else{
            lastwaswhite = 0;
        }
        blackinline = 0;
        for(int y = 0; y < surface.h;y++){
            Uint32 pixel = getpixel(&surface, x, y);
            Uint8 black = 0;
            SDL_GetRGB(pixel, surface.format, &black, &black, &black);
            if(black == 0){
                blackinline = 1;
                break;
            }
        }
        if(blackinline == 1 && lastwaswhite == 1){
            average = (average**arraysize + (x - previous_x))/(*arraysize+1);
            letters = realloc(letters, (*arraysize)*sizeof(SDL_Surface));
            *(letters + index) = CropImage(surface, previous_x, x, 0, surface.h);
            if(endswithspace(*(letters + index),average)){
                (*arraysize)+=1;
                index += 1;
                letters = realloc(letters, (*arraysize)*sizeof(SDL_Surface));
                *(letters + index) = *SDL_CreateRGBSurface(0,1,1,32,0,0,0,0);
            }
            (*arraysize)+=1;
            index += 1;
            previous_x = x;
        }
    }
    letters = realloc(letters, *arraysize*(sizeof(SDL_Surface)));
    *(letters + index) = CropImage(surface, previous_x, surface.w, 0, surface.h);
    if(index != 0){
        int newsize = *arraysize;
        SDL_Surface *norenegade = renegade(letters,&newsize,average);
        *arraysize = newsize;
        return norenegade;
    }
    else{
        return letters;
    }
}

int endswithspace(SDL_Surface surface, int average){
    int asbeenblack = 0;
    for(int i = (surface.w)*0.7f - 1; i < surface.w && !asbeenblack; i++){
        for(int j = 0; j < surface.h; j++){
            Uint8 black;
            Uint32 pixel = getpixel(&surface,i,j);
            SDL_GetRGB(pixel,surface.format,&black,&black,&black);
            if(black == 0)
                asbeenblack = 1;
        }
    }
    return !asbeenblack && (surface.w > average*1.3f);
}

SDL_Surface* GetLines(SDL_Surface surface,size_t *arraysize){
    int lineblack = 1;
    int previouswhite = 0;
    SDL_Surface *lines = malloc(sizeof(SDL_Surface));
    *arraysize = 1;
    int index = 0;
    int previous_y = 0;
    for(int y = 0; y < surface.h;y++){
        if(lineblack == 0){
            previouswhite = 1;
        }
        else{
            previouswhite = 0;
        }
        lineblack = 0;
        for(int x = 0; x < surface.w;x++){
            if(lineblack != 0){
                break;
            }
            Uint32 pixel = getpixel(&surface, x, y);
            Uint8 red;
            Uint8 green;
            Uint8 blue;
            SDL_GetRGB(pixel, surface.format, &red, &green, &blue);
            if(blue == 0){
                lineblack = 1;
            }
        }
        if(lineblack == 1 && previouswhite == 1){
            lines = realloc(lines,(*arraysize) * (sizeof(SDL_Surface)));
            *(lines + index) = CropImage(surface, 0, surface.w, previous_y, y);
            *arraysize = (*arraysize) + 1;
            index++;
            previous_y = y;
        }
    }
    lines = realloc(lines, (*arraysize)*sizeof(SDL_Surface));
    *(lines + index) = CropImage(surface, 0, surface.w, previous_y, surface.h);
    return lines;
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
