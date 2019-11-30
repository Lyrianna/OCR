#ifndef XOR_NETWORK_H
#define XOR_NETWORK_H

#include "matrix/matrix.h"



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
void train_neural(Matrix *in , Matrix *wanted_out, bool istherearg, unsigned long int epochuser);

//character finder
void character_translator(Matrix* in, char* filename);

//Displays the results
void displayepoch();

//Save datas
void save_datas();

//loadmatric
void load_datas(Matrix* matrixarray[], FILE* fichier);

//free the memory
void freeAll();

#endif
