//
//  otsu.c
//  TestOCR
//
//  Created by Pierre Pelletier on 17/11/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//

#include "otsu.h"


Uint32 *histo;
float *Pk;

int otsu(SDL_Surface *surface){
    init_otsu();
    createHisto(*surface);
    calculateproba_otsu(*surface);
    if(equalize == 1){
        SDL_Surface imghisto = drawHisto();
        IMG_SavePNG(&imghisto, "histo1.png");
        equalization(surface);
        init_otsu();
        createHisto(*surface);
        calculateproba_otsu(*surface);
        SDL_Surface imghisto2 = drawHisto();
        IMG_SavePNG(&imghisto2, "histo2.png");
    }
    int T = getT();
    free_otsu();
    return T;
}

void init_otsu(){
    histo = calloc(256, sizeof(Uint32));
    Pk = calloc(256,sizeof(float));
}

void equalization(SDL_Surface *surface){
    for(int i = 0; i < surface->w; i++){
        for(int j = 0; j < surface->h; j++){
            Uint32 pixel = getpixel(surface, i, j);
            Uint8 *black = malloc(sizeof(Uint8));
            SDL_GetRGB(pixel, surface->format, black, black, black);
            *black = (255*cumulatedHisto(*black));
            pixel = SDL_MapRGB(surface->format, *black, *black, *black);
            putpixel(surface, i, j, pixel);
            free(black);
        }
    }
}

float cumulatedHisto(Uint8 n){
    float cumulated = 0.0f;
    for(Uint8 i = 0; i < n; i++){
        cumulated += *(Pk + i);
    }
    return cumulated;
}

int getT(){
    float max = 0.0f;
    int bestT = 0;
    for(int i = 0; i < 256; i++){
        float sigma = calculateintraCvar(i);
        if(sigma > max){
            max = sigma;
            bestT = i;
        }
    }
    return bestT;
}

float calculateintraCvar(int T){
    float sigma = 0;
    float omega1 = getprobaclass1(T);
    float omega2 = getprobaclass2(T);
    float mu1 = calculateaverage1(T);
    float mu2 = calculateaverage2(T);
    sigma = omega1*omega2*(mu1 - mu2)*(mu1-mu2);
    return sigma;
}

float calculateaverage1(int T){
    float average = 0;
    for(int i = 0; i < T; i++){
        average += i*(*(Pk + i));
    }
    return average/getprobaclass1(T);
}

float calculateaverage2(int T){
    float average = 0;
    for(int i = T; i < 256; i++){
        average += i*(*(Pk + i));
    }
    return average/getprobaclass2(T);
}

float getprobaclass1(int T){
    float proba = 0.0f;
    for(int i = 0; i < T; i++){
        proba += *(Pk + i);
    }
    return proba;
}

float getprobaclass2(int T){
    float proba = 0.0f;
    for(int i = T; i < 256; i++){
        proba += *(Pk + i);
    }
    return proba;
}

void calculateproba_otsu(SDL_Surface surface){
    for(int i = 0; i < 256; i++){
        *(Pk + i) = ((float)*(histo + i)) / ((float)(surface.h * surface.w));
    }
}

void createHisto(SDL_Surface surface){
    for(int i = 0; i < surface.w; i++){
        for(int j = 0; j < surface.h; j++){
            Uint32 pixel = getpixel(&surface, i, j);
            Uint8 *black = malloc(sizeof(Uint8));
            SDL_GetRGB(pixel, surface.format,black,black,black);
            *(histo + *black) = *(histo + (Uint32)(*black)) + 1;
            free(black);
        }
    }
}

SDL_Surface drawHisto(){
    float max = maxinHisto();
    SDL_Surface surfacehisto = *SDL_CreateRGBSurface(0, 256, 256, 32, 0, 0, 0, 0);
    for(int i = 0; i < 256; i++){
        for(int j = 255; j >= 0;j--){
            Uint32 pixel = SDL_MapRGB(surfacehisto.format, 255, 0, 255);
            if(histo[i]/max*256 < 256 - j){
                pixel = SDL_MapRGB(surfacehisto.format, 255, 255, 255);
            }
            putpixel(&surfacehisto, i, j, pixel);
        }
    }
    return surfacehisto;
}

float maxinHisto(){
    float max = 0;
    for(int i = 0; i < 256; i++){
        if(histo[i] > max){
            max = histo[i];
        }
    }
    return max;
}

void free_otsu(){
    free(histo);
    free(Pk);
}
