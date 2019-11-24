#ifndef segmentation_h
#define segmentation_h

#include "loadandprocess.h"

Letter* seg_segmentation(char *filename, int *size);
Letter* getLetters(SDL_Surface *seg_letters, int size);

#endif