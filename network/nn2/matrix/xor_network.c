#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "xor_network.h"
#include "matrix.h"

//NEURAL NETWORK - XOR - Sarah and Nephelie//


double bias=1;//general bias

double lr = 2;//learning rate
unsigned long int epoch = 10000;//number of epoch for the training

size_t inputNb;//number/size of the input
Matrix *input;
Matrix *wanted_output

Matrix *wanted_output;

size_t hiddenNb = 30;//number of hidden neurons
Matrix *hidden = initM(inputNb, hiddenNb);
Matrix *hidden_weight = initM(1, hiddenNb);

size_t outputNb;
Matrix *output = initM(hiddenNb, outputNb);//output neurons
Matrix *output_weight =initM(1, outputNb);

double error_values[4];//jsp
Matrix *derivative_output = initM(hiddenNb, outputNb);
Matrix *derivative_hidden = initM(inputNb, hiddenNb);

double weight_gradient[9];//jsp

//Sigmoid functions
double sigmoid( double x)
{
    return (double)(1/(1+exp(-x)));
}

double sigmoid_derivate(double x)
{

    return x*(1-x);
}

//initialization
void generate_wgt()
{
    srand(time(NULL));
    for (int i = 0; i < 9; i++)
            weights[i] =(double) (rand()/ (double)RAND_MAX*(2)-1);
}

//Feed forward

void hidden_layers(int x)
{
    sum_hidden1 = (inputs[x][0]*weights[0]) + (inputs[x][1]*weights[2])
    + (bias *weights[4]);
    sum_hidden2 = (inputs[x][0]*weights[1]) + (inputs[x][1]*weights[3])
    + (bias *weights[5]);
    hidden1 = sigmoid(sum_hidden1);
    hidden2 = sigmoid(sum_hidden2);
}

void output_neurons()
{
    sum_output = (hidden1 * weights[6]) + (hidden2 * weights[7])
    + (bias * weights[8]);
    output = sigmoid(sum_output);
}

//backpropagation
void error(int x)
{
    error_values[x] = wanted_outputs[x]- output;
}

void derivatives(int x)
{
    derivative_output = error_values[x] * sigmoid_derivate(output);

    derivative_hidden1 = sigmoid_derivate(hidden1) * weights[6]
    * derivative_output;

    derivative_hidden2 = sigmoid_derivate(hidden2) * weights[7]
    * derivative_output;
}

//update of weights and bias
void weight_gradient_update(int x)
{
    weight_gradient[0] = sigmoid(inputs[x][0]) * derivative_hidden1;
    weight_gradient[1] = sigmoid(inputs[x][0]) * derivative_hidden2;
    weight_gradient[2] = sigmoid(inputs[x][1]) * derivative_hidden1;
    weight_gradient[3] = sigmoid(inputs[x][1]) * derivative_hidden2;
    weight_gradient[4] = sigmoid(bias) * derivative_hidden1;//bias gradient
    weight_gradient[5] = sigmoid(bias) * derivative_hidden2;//bias gradient
    weight_gradient[6] = hidden1 * derivative_output;
    weight_gradient[7] = hidden2 * derivative_output;
    weight_gradient[8] = sigmoid(bias) * derivative_output;//bias gradient
    //for the case 4,5 and 8 it is about changing the fixed bias
}

void update_weights()
{
    for (int i = 0; i < 9;i++)
        weights[i] += lr * weight_gradient[i];
    //weight are updated with the weight
}

//training
void train_neural(Matrix *in , Matrix *wanted_out)
{
	*input = *in;
	*wanted_output = wanted_out;
	inputNb = *inputs->n;
	outputNb = *wanted_output->n;
	unsigned long int k = 0;
    while ( k < epoch)
    {
        for (int i = 0; i < 4; i++)
        {
            hidden_layers(i);
            output_neurons();
            error(i);
            derivatives(i);
            weight_gradient_update(i);
            update_weights();
            displayepoch(i);
        }
        k+=1;
    }
}

void displayepoch(int x)//displays the results of the start and the last epoch
{
    if (epoch==0){
	    if (x == 0)
		    printf("\nThis is the start of our untrained XOR:\n");
	printf("	%lf xor %lf = %lf\n", inputs[x][0],inputs[x][1],output);
    }
     if (epoch==9999){
	     if (x ==0)
		printf("\nThis is the final results of our trained XOR:\n");
	printf("	%lf xor %lf = %lf\n", inputs[x][0],inputs[x][1],output);
     }
}

void save_datas()
{
    FILE* fichier = NULL;
    fichier = fopen("datasaved.txt", "w");

    if (fichier != NULL)
    {
        for (int i = 0; i < 9; i++)
        {
            fprintf(fichier,"%lf\n",weights[i]);
            fprintf(fichier,"%lf\n",weight_gradient[i]);
        }
        fprintf(fichier,"%lf\n",hidden1);
        fprintf(fichier,"%lf\n",hidden2);

        fclose(fichier);
    }
}
