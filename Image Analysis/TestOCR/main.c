//
//  main.c
//  TestOCR
//
//  Created by Pierre Pelletier on 02/10/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//
#include "loadandprocess.h"
#include "main.h"

int equalize = 0;

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Please use the correct argument\n");
        return(-1);
    }
    if(argc > 2 && strcmp(argv[2], "-h") == 0){
        equalize = 1;
    }   
    int size;
    Letter *l = seg_segmentation(argv[1], &size);
    return l->matrix[0][0];
}
