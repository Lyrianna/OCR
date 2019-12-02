//
//  loadandprocess.h
//  TestOCR
//
//  Created by Pierre Pelletier on 17/11/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#ifndef loadandprocess_h
#define loadandprocess_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "otsu.h"
#include "letter.h"
#include "segmentation.h"
#include "renegade.h"

int loadimage(char *filename,SDL_Surface *seg_letters, int *nbletters);
void BlackAndWhite(SDL_Surface* surface);
void MonoColor(SDL_Surface* surface);
void ExtractBlock(SDL_Surface* surface);
void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface CropImage(SDL_Surface surface, int x1,int x2, int y1,int y2);
SDL_Surface* GetLines(SDL_Surface surface,size_t *arraysize);
SDL_Surface ImproveLine(SDL_Surface surface);
SDL_Surface* GetLetters(SDL_Surface surface,size_t *arraysize);
int endswithspace(SDL_Surface surface, int average);
SDL_Surface ImproveLetter(SDL_Surface surface);
void ExtractLetters(SDL_Surface *surface, SDL_Surface *seg_letters, int *totalsize);

#endif /* loadandprocess_h */
