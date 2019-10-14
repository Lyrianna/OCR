#ifndef XOR_NETWORK_H
#define XOR_NETWORK_H

//sigmoid
double sigmoid( double x);
double sigmoid_prime(double x);

//init
void generate_wgt();
void start_input();

//forward prop

void calc_hiddenlayers(int x);
void calc_outputneurons(int x);
void calc_error(int x);
void calc_derivatives(int x);
void calc_gradient(int x);
void calc_update(int x);

//backprop

void update_weights();

//training
void train_neural();


#endif