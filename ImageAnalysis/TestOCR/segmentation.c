#include "segmentation.h"


//Oubliez pas de free les lettres après vous en être servi

void debug_matrix(Letter l){
	if(l.newline == 1){
		printf("NEW LINE \n");
		return;
	}
	for(int i = 0; i < 28; i++){
		for(int j = 0; j < 28; j++){
			printf("%d",(int)l.matrix[i*28 + j]);
		}
		printf("\n");
	}
}

Letter* seg_segmentation(char *filename,int *size){
	SDL_Surface *seg_letters = malloc(10000*sizeof(SDL_Surface));
	if(seg_letters == NULL){
		printf("Memory full, aborting...\n");
		return NULL;
	}
	int *nbletters = malloc(sizeof(int));
	*nbletters = 0;
	int value = loadimage(filename,seg_letters,nbletters);
	seg_letters = realloc(seg_letters,*nbletters*sizeof(SDL_Surface));
	if(value != 0){
		printf("Error while loading your image !\n");
		return NULL;
	}
	Letter *letters = getLetters(seg_letters,*nbletters);
	IMG_Quit();
	SDL_Quit();	
	free(seg_letters);
	*size = *nbletters - 1;
		for(int i = 0; i < *nbletters; i++){
		debug_matrix(letters[i]);
		printf("\n\n");
	}
	free(nbletters);
	return letters + 1;
}


Letter* getLetters(SDL_Surface *seg_letters, int size){
	Letter* letters = calloc(size,sizeof(Letter));
	for(int i = 0; i < size; i++){
		if((seg_letters + i)->h == 2){
			Letter l;
			l.newline = 1;
			letters[i] = l;
		}
		else if(seg_letters + i != NULL){
			double* matrix = malloc(28*28*sizeof(double));
			matrix = makesquare(*(seg_letters + i));
			Letter l;
			l.matrix = matrix;
			l.newline = 0;
			letters[i] = l;	
		}
		
	}
	return letters;
}
