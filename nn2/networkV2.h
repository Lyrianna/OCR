#ifndef XOR_NETWORK_H
#define XOR_NETWORK_H

#include "matrix/matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "networkV2.h"
#include <string.h>
#include <stdbool.h>


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
void train_neural(bool istherearg, unsigned long int epochuser);
Matrix* createouttrain(int i);

//character finder
void ocr(Matrix* in, FILE* fichier);
char whichchar(Matrix* output);
void writeinfile(char character, FILE* fichier);

//Displays the results
void displayepoch();

//Save datas
void save_datas();

//loadmatric
void load_datas(Matrix matrixarray[], FILE* fichier);

//free the memory
void freeAll();

#endif
