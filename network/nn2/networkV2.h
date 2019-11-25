#ifndef XOR_NETWORK_H
#define XOR_NETWORK_H

#include "matrix/matrix.h"

#define ALPHABET = [abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ,.];

//initialization
void generate_wgt();
void initAll();

//Feed forward
void hidden_layers();
void output_neurons();

//Backpropagation
void error();
void derivatives();

//Update of weights and bias
void update_weights();

//training
void train_neural();

//character finder
void character_translator(Matrix *in, Matrix *outp);

//Displays the results
void displayepoch();

//Save datas
void save_datas();

//loadmatric
void load_datas(Matrix* matrixarray[]);

//free the memory
void freeAll();

#endif
