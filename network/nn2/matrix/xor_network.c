#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "xor_network.h"
#include "matrix.h"

//NEURAL NETWORK - XOR - Sarah and Nephelie//
//ADAPTATION TO MATRIX STARTED ON 17/11/2019 BY SARAH
double lr = 2;//learning rate

unsigned long int epoch = 10000;//number of epoch for the training

size_t inputNb;//number/size of the input
Matrix *input;
Matrix *wanted_output

size_t hiddenNb = 30;//number of hidden neurons
Matrix *hidden, *hidden_weight, *hidden_bias;

size_t outputNb;//output neurons
Matrix *output, *output_weight, *output_bias;


Matrix *derivative_output, *derivative_hidden;

Matrix *error_values;
double weight_gradient[9];//jsp

//initialization
void initAll(){
	*hidden = initm(inputNb, hiddenNb);
	*hidden_weight = initM(hiddenNb, hiddenNb);
	*hidden_bias = initM(inputNb, hiddenNb);

	*output = initM(hiddenNb, outputNb)
	*output_weight = initM(hiddenNb, outputNb);
	*output_bias = initM(hiddenNb, outputNb);

	*error_values = initM(outputNb,outputNb);
	*derivative_output = initM(hiddenNb, outputNb);
	*derivative_hidden = initM(inputNb, hiddenNb);
}

void generate_wgt()
{
    srand(time(NULL));
    for (int i = 0; i < (*(hidden_weight)->sizevector) ; i++)
	    *(hidden_weight+i) =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (int j = 0 ; j < (*(output_weight)->sizevector) ;j++)
	    *(output_weight+j) =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (int k = 0 ; k < (*(hidden_bias)->sizevector); k++)
	    *(hidden_bias+k) =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (int g = 0; g < (*(output_bias)->sizevector); g++)
	    *(output_bias+g) =(double) (rand()/ (double)RAND_MAX*(2)-1);

}

//Feed forward

void hidden_layers()
{
	*hidden = mulM(inputs, hidden_weight);
	*hidden = sigM(addM(hidden, hidden_bias));
}

void output_neurons()
{
	*output = mulM( hidden, output_weight);
	*output = sigM( addM(output, output_bias));
}

//backpropagation
void error()
{
	*error_values = subM(wanted,output);
}

void derivatives()
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
	*wanted_output = *wanted_out;
	inputNb = *inputs->n;
	outputNb = *wanted_output->n;
	initAll();
	unsigned long int k = 0;
    while ( k < epoch)
    {
	    hidden_layers();
            output_neurons();
            error();
            derivatives();
            weight_gradient_update();
            update_weights();
            displayepoch();
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
