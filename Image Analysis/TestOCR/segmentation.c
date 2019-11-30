#include "segmentation.h"


//Oubliez pas de free les lettres après vous en être servi

void debug_matrix(Letter l){
	for(int i = 0; i < 28; i++){
		for(int j = 0; j < 28; j++){
			printf("%d",l.matrix[i][j]);
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
	int value = loadimage(filename,seg_letters,nbletters);
	if(value != 0){
		printf("Error while loading your image !\n");
		return NULL;
	}
	Letter *letters = getLetters(seg_letters,*nbletters);
	for(int i = 0; i < *nbletters;i++){
		debug_matrix(*(letters + i));
		printf("\n\n\n\n");
	}
	IMG_Quit();
	SDL_Quit();	
	free(seg_letters);
	*size = *nbletters;
	free(nbletters);
	return letters;
}


Letter* getLetters(SDL_Surface *seg_letters, int size){
	Letter* letters = malloc(size*sizeof(Letter) + 1);
	for(int i = 0; i < size; i++){
		if(seg_letters + i != NULL){
			int** matrix = malloc(28*28*sizeof(int));
			matrix = makesquare(*(seg_letters + i));
			Letter l;
			l.matrix = matrix;
			letters[i] = l;	
		}
	}
	return letters;
}