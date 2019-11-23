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
//TODO
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
}

void generate_wgt()
{
    srand(time(NULL));
    for (size_t i = 0; i < (hidden_weight->sizevector) ; i++)
	    hidden_weight->matrix[i] = (double) (rand()/ (double)RAND_MAX*(2)-1);
    for (size_t j = 0 ; j < (output_weight->sizevector) ;j++)
	    output_weight->matrix[j] =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (size_t k = 0 ; k < (hidden_bias->sizevector); k++)
	    hidden_bias->matrix[k] =(double) (rand()/ (double)RAND_MAX*(2)-1);
    for (size_t g = 0; g < (output_bias->sizevector); g++)
	    output_bias->matrix[g] = (double) (rand()/ (double)RAND_MAX*(2)-1);

}

//Feed forward

void hidden_layers()
{
	hidden = dotM(input, hidden_weight);
	hidden = sigM(addM(hidden, hidden_bias),false);
}

void output_neurons()
{
	output = dotM( hidden, output_weight);
	output = sigM( addM(output, output_bias),false);
}

//Backpropagation
void error() //error for each case
{
	error_values = subM(wanted_output,output);
}

//TODO
void derivatives()//repercution of the error for each layer
{
    derivative_output = dotM(error_values,sigM(output,true));
    derivative_hidden = dotM(dotM(sigM(derivative_hidden,true),hidden_weight),derivative_output);
}

void update_weights()//update of the different matrices
{
	//update of the weight btw input and hidden layer
	//hidden_w += dot(input, derivative_hidden)*lr
	hidden_weight =addM(hidden_weight, scalM(dotM(input, derivative_hidden), lr));

	//update of the bias of the hidden layer
	//hidden_bias += dot(sigmoid(hidden_bias), derivative_hidden)*lr))
	hidden_bias = addM(hidden_bias, scalM(dotM(sigM(hidden_bias,0), derivative_hidden), lr));
	
   	//update of the weight btw hidden and output layer
   	//output_w += dot(input, derivative_output)*lr
     output_weight = addM(output_weight, scalM(dotM(hidden, derivative_output), lr));
     
	//update of the bias of the output layer
	//output_bias += dot(sigmoid(output_bias), derivative_output)*lr))
	output_bias = addM(output_bias, scalM(dotM(derivative_output, mulM(sigM(output_bias, 0),derivative_output)), lr));
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
            //displayepoch();
	    k+=1;
    }
}

/*void displayepoch(int x)//displays the results of the start and the last epoch
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
}*/

void save_datas()
{
    saveM(hidden,false);
    saveM(hidden_weight,true);
    saveM(hidden_bias,true);
    saveM(output,true);
    saveM(output_weight,true);
    saveM(output_bias,true);
    saveM(derivative_output,true);
    saveM(derivative_hidden,true);
}



int taille[2] = {0};

void load_datas(Matrix* matrixarray[])
{
    FILE* fichier = fopen("../datasaved.txt","r");

    if (fichier != NULL)
    {
        int i = 0;

        while (i<8)
        {
            fscanf(fichier, "%d %d",&taille[0],&taille[1]);

            int size = taille[0]*taille[1];
            fgetc(fichier);
            double* matrixvalues = malloc(sizeof(double)*size);

            fread(matrixvalues, sizeof(double),size,fichier);

            matrixarray[i] = initwithvaluesM(taille[0],taille[1], matrixvalues);

            i++;

            fgetc(fichier);
            fgetc(fichier);
        }

        fclose(fichier);
    }
    else
        errx(1,"LOADMATRIX : No file datasaved.txt.");
}