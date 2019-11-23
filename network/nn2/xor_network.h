#ifndef XOR_NETWORK_H
#define XOR_NETWORK_H

#include "matrix/matrix.h"
#define Matrix *matrixarray[8];
#define ALPHABET = [abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ,.];

//initialization
void generate_wgt();

//Feed forward
void hidden_layers();
void output_neurons();

//Backpropagation
void error();
void derivatives();

//Update of weights and bias
void weight_gradient_update();
void update_weights();

//XOR training
void train_neural();

//Displays the results
void displayepoch();

//Save datas
void save_datas();

//loadmatric
void load_datas();

#endif
