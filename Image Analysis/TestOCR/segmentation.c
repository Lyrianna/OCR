#include "segmentation.h"


//Oubliez pas de free les lettres après vous en être servi

Letter* seg_segmentation(char *filename,int *size){
	SDL_Surface *seg_letters = malloc(10000*sizeof(SDL_Surface));
	int *nbletters = malloc(sizeof(int));
	int value = loadimage(filename,seg_letters,nbletters);
	if(value != 0){
		printf("Error while loading your image !");
		return NULL;
	}
	Letter *letters = getLetters(seg_letters,*nbletters);
	IMG_Quit();
	SDL_Quit();	
	free(seg_letters);
	*size = *nbletters;
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