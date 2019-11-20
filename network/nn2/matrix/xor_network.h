#ifndef XOR_NETWORK_H
#define XOR_NETWORK_H

//Sigmoid functions
double sigmoid(double x);
double sigmoid_derivate(double x);

//initialization
void generate_wgt();

//Feed forward
void hidden_layers(int x);
void output_neurons();

//Backpropagation
void error(int x);
void derivatives(int x);

//Update of weights and bias
void weight_gradient_update(int x);
void update_weights();

//XOR training
void train_neural();

//Displays the results
void displayepoch(int x);

//Save datas
void save_datas();

#endif
