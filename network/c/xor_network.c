#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//training data 2bits for XOR

int bias = 1;

float weights[9] = {};

double inputs[4][2] = {
        {0, 1},
        {1, 0},
        {0, 0},
        {1, 1}
}

int wanted_outputs[4]={1,1,0,0};

//other datas
float hidden1;
float hidden2;
float sum_hidden1;
float sum_hidden2;
float output;
float sum_ouput;
float error[4];

//SIGMOID
double sigmoid( double x)
{
    return (double)(1/(1+exp(-x)));
}

double sigmoid_prime(double x)
{

    return x*(1-x); //return sigmoid(x)*(1-sigmoid(x));
}

//init
void generate_wgt()
{
    //srand(time(NULL));
    for (int i = 0; i < 9; ++i)
    {
        int randomNum = rand()%2;
        if (randomNum==1)
            weights[i] = -1* (double (rand())/ (double(RAND_MAX)+1.0));
        else
            weights[i] = (double(rand())/(double(RAND_MAX)+1.0);

    }
}
void start_input()
{
//TODO
}

//forward prop

void calc_hiddenlayers(int x)
{
    sum_hidden1 = (inputs[x][0]*weights[0]) + (inputs[x][1]*weights[2]) + (bias *weights[4]);
    sum_hidden2 = (inputs[x][0]*weights[1]) + (inputs[x][1]*weights[3]) + (bias *weights[5]);
    hidden1 = sigmoid(sum_hidden1);
    hidden2 = sigmoid(sum_hidden2);
}
void calc_outputneurons(int x)
{
    sum_output = (hidden1 * weights[6]) + (hidden2 * weights[7]) + (bias * weights[8]);
    output = sigmoid(sum_output);
}
void calc_error(int x)
{
    error[x] = output - wanted_outputs[x];
}
void calc_derivatives(int x);
void calc_gradient(int x);
void calc_update(int x);

//backprop

void update_weights();

//training
unsigned long int epoch = 0;
void train_neural()
{
    while (epoch<10000)
    {
        for (int i = 0; i < 4; ++i)
        {
            calc_hiddenlayers(i);
            calc_outputneurons();
            calc_error(i);
            calc_derivatives(i);
            calc_gradient(i);
            calc_update();
            update_weights();
        }
        epoch+=1;
        if (epoch>400)
        {
            //TODO
        }
    }
}