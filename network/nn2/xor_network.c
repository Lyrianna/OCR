#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "xor_network.h"
#include "matrix/matrix.h"

//NEURAL NETWORK - XOR - Sarah and Nephelie//
//ADAPTATION TO MATRIX STARTED ON 17/11/2019 BY SARAH AND NEPHELIE

double lr = 2; //learning rate

unsigned long int epoch = 10000;//number of epoch for the training

size_t inputNb;//number/size of the input
Matrix *input;
Matrix *wanted_output;

size_t hiddenNb = 30;//number of hidden neurons
Matrix *hidden, *hidden_weight, *hidden_bias;

size_t outputNb;//output neurons
Matrix *output, *output_weight, *output_bias;


Matrix *derivative_output, *derivative_hidden;

Matrix *error_values;

//initialization
void initAll(){

    //Hidden layers
    initM2(hidden, inputNb, hiddenNb);
	initM2(hidden_weight, hiddenNb, hiddenNb);
	initM2(hidden_bias, inputNb, hiddenNb);

	//Output Layer
    initM2(output, hiddenNb, outputNb);
    initM2(output_weight, hiddenNb, outputNb);
    initM2(output_bias, hiddenNb, outputNb);

    //Update weights
    initM2(error_values, outputNb, outputNb);
    initM2(derivative_output, hiddenNb, outputNb);
    initM2(derivative_hidden, inputNb, hiddenNb);
    initM2(weight_gradient,inputNb*inputNb,inputNb*inputNb);
}

void generate_wgt()
{
    srand(time(NULL));
    for (int i = 0; i < (hidden_weight->sizevector) ; i++)
	    hidden_weight->matrix[i] = (double) (rand()/ (double)RAND_MAX*(2)-1);
    for (int j = 0 ; j < (output_weight->sizevector) ;j++)
	    output_weight->matrix[j] =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (int k = 0 ; k < (hidden_bias->sizevector); k++)
	    hidden_bias->matrix[k] =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (int g = 0; g < (output_bias->sizevector); g++)
	    output_bias->matrix[g] = (double) (rand()/ (double)RAND_MAX*(2)-1);

}

//Feed forward

void hidden_layers()
{
	hidden = hadaM(input, hidden_weight);
	hidden = sigM(addM(hidden, hidden_bias),false);
}

void output_neurons()
{
	output = hadaM( hidden, output_weight);
	output = sigM( addM(output, output_bias),false);
}

//Backpropagation
void error()
{
	error_values = subM(wanted_output,output);
}

void derivatives()
{
    derivative_output = hadaM(error_values,sigM(output,true));
    derivative_hidden = hadaM(hadaM(sigM(derivative_hidden,true),weight),derivative_output);
}

//update of weights and bias
/*void weight_gradient_update()
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
}*/

void update_weights()
{
	//update of the weight btw input and hidden layer
	hidden_weight =sum(hidden_weight, scalM(hadaM(input, derivative_hidden), lr));

	//update of the bias of the hidden layer
	hidden_bias = sumM(hidden_bias, scalM(hadaM(derivative_hidden, hadaM(sigM(hidden_bias, derivative_hidden)), lr));
   	//update of the weight btw hidden and output layer
        output_weight = sumM(output_weight, scalM(hadaM(hidden_activ, derivative_output), lr));
	//update of the bias of the output layer
	output_bias = sumM(output_bias, scalM(hadaM(derivative_output, mulM(sigM(output_bias),derivative_output)), lr));
}

//training
void train_neural(Matrix *in , Matrix *wanted_out)
{
	*input = *in;
	*wanted_output = *wanted_out;
	inputNb = input->n;
	outputNb = wanted_output->n;
	initAll();
	unsigned long int k = 0;
    while ( k < epoch)
    {
	    hidden_layers();
            output_neurons();
            error();
            derivatives();
            //weight_gradient_update();
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
