//
//  main.c
//  TestOCR
//
//  Created by Pierre Pelletier on 02/10/2019.
//  Copyright © 2019 Pierre Pelletier. All rights reserved.
//
#include "main.h"


int equalize = 0;

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Please use the correct argument\n");
        return(-1);
    }
    for(int i = 2; i < argc; i++){
        if(strcmp("-h", argv[i]) == 0)
            equalize = 1;
        else if(strcmp("-t",argv[i]) == 0){
            trainingmode(argv[1]);
            return 0;
        }
    }
    int size;
    Letter *l = seg_segmentation(argv[1], &size);
    return (uint64_t)l;
}

void trainingmode(char *filename){
    int size = 0;
    Letter *l = seg_segmentation(filename,&size);
    for(int i = 0; i < size; i++){
        char *name = malloc(50*sizeof(char));
        sprintf(name, "training/matrix%d",i);
        FILE *f = fopen(name,"w");
        char *content = str_matrix(l[i]);
        if(content != NULL){
			fputs(content,f);	
	}
      fclose(f);
      free(name);
      free(content);
    }
}

char* str_matrix(Letter l){
    char *s = malloc(28*29*sizeof(char));
    int strindex = 0;
    if(l.newline == 1){
	return NULL;
    }
	for(int i = 0; i < 28; i++){
		for(int j = 0; j < 28; j++){
			s[strindex] = l.matrix[i*28 + j] + '0';
            strindex++;
		}
		s[strindex] = '\n';
        strindex++;
	}
    return s;
}
