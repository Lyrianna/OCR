//
//  otsu.h
//  TestOCR
//
//  Created by Pierre Pelletier on 17/11/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#ifndef otsu_h
#define otsu_h

#include "loadandprocess.h"
#include "main.h"

int otsu(SDL_Surface *surface);
void init_otsu(void);
void free_otsu(void);
void createHisto(SDL_Surface surface);
void calculateproba_otsu(SDL_Surface surface);
float getprobaclass1(int T);
float getprobaclass2(int T);
float calculateintraCvar(int T);
float calculateaverage1(int T);
float calculateaverage2(int T);
int getT(void);
void equalization(SDL_Surface *surface);
float cumulatedHisto(Uint8 n);
SDL_Surface drawHisto(void);
float maxinHisto(void);

#endif /* otsu_h */
