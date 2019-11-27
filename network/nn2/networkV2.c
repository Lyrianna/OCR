#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "networkV2.h"
#include "matrix/matrix.h"

//NEURAL NETWORK - Sarah and Nephelie//
//ADAPTATION TO MATRIX STARTED ON 17/11/2019 BY SARAH AND NEPHELIE

double lr = 2; //learning rate

unsigned long int epoch = 10000;//number of epoch for the training

size_t inputNb;//number of neurons in the input
Matrix *input = NULL;
Matrix *wanted_output = NULL;

size_t hiddenNb = 40;//number of hidden neurons
Matrix *hidden = NULL;
Matrix *hidden_weight = NULL;
Matrix *hidden_bias = NULL;

size_t outputNb;//output neurons
Matrix *output = NULL;
Matrix *output_weight = NULL;
Matrix *output_bias = NULL;


Matrix *derivative_output = NULL;
Matrix *derivative_hidden = NULL;

Matrix *error_values = NULL;

//initialization of matrices
void initAll(){

    //Hidden layers
    hidden = initM(1,hiddenNb);
    hidden_weight = initM(inputNb,hiddenNb);
    hidden_bias = initM(1,hiddenNb);

    //Output Layer
    output = initM(1,outputNb);
    output_weight = initM(hiddenNb,outputNb);
    output_bias = initM(1,outputNb);

    //Update weights
    error_values = initM(1,outputNb);
    derivative_output = initM(1,outputNb);
    derivative_hidden = initM(1,hiddenNb);
}

void generate_wgt()
{
    srand(time(NULL));
    for (size_t i = 0; i < (hidden_weight->sizevector) ; i++) {
        hidden_weight->matrix[i] =(rand() / (double) RAND_MAX * (2) - 1);
    }
    for (size_t j = 0 ; j < (output_weight->sizevector) ;j++)
	    output_weight->matrix[j] = (rand()/ (double)RAND_MAX*(2)-1);
    for (size_t k = 0 ; k < (hidden_bias->sizevector); k++)
	    hidden_bias->matrix[k] = (rand()/ (double)RAND_MAX*(2)-1);
    for (size_t g = 0; g < (output_bias->sizevector); g++)
	    output_bias->matrix[g] = (rand()/ (double)RAND_MAX*(2)-1);

}

//Feed forward

void hidden_layers()
{
	hidden = mulM(input, hidden_weight);
	hidden = sigM(addM(hidden, hidden_bias),false);
}

void output_neurons()
{
	output = mulM(hidden, output_weight);
	output = sigM( addM(output, output_bias),false);
}

//Backpropagation
void error() //error for each case
{
	error_values = subM(wanted_output,output);
}

void derivatives()//repercution of the error for each layer
{
    derivative_output = dotM(error_values,sigM(output,true));
    derivative_hidden = dotM(mulM(derivative_output, transpM(output_weight)),sigM(hidden, true));
}

void update_weights()//update of the different matrices
{
	//update of the weight btw input and hidden layer
	//hidden_w += dot(input, derivative_hidden)*lr
	hidden_weight =addM(hidden_weight, scalM(mulM(transpM(input), derivative_hidden), lr));

	//update of the bias of the hidden layer
	//hidden_bias += dot(sigmoid(hidden_bias), derivative_hidden)*lr))
	hidden_bias = addM(hidden_bias, scalM(dotM(sigM(hidden_bias,false), derivative_hidden), lr));
	
   	//update of the weight btw hidden and output layer
   	//output_w += dot(input, derivative_output)*lr
	output_weight = addM(output_weight, scalM(mulM(transpM(hidden), derivative_output), lr));
     
	//update of the bias of the output layer
	//output_bias += dot(sigmoid(output_bias), derivative_output)*lr))
	output_bias = addM(output_bias, scalM(dotM(sigM(output_bias, false),derivative_output), lr));
}

//training
void train_neural(Matrix *in , Matrix *wanted_out)
{
    printf("MATRICE TRAINING");

    input = in;
    wanted_output = wanted_out;

	inputNb = input->p;
	outputNb = wanted_out->p;

	freeM(in);
	freeM(wanted_out);

	initAll();
	generate_wgt();

	unsigned long int k = 0;
    while ( k < epoch)
    {
	    hidden_layers();
	    printf("hidden layers done");
	    output_neurons();
        printf("output neurons done");
	    error();
        printf("error done");
        derivatives();
        printf("derivatives done");
        update_weights();
        printf("update weights done");
	    k+=1;
    }
    save_datas();//saves the important datas of the NN
    freeAll();
}

/*void character_translator(char filename)
{
    //FILE* fichier = fopen(filename,'r');

    *input;
        inputNb = input->n;
	output;//output matrix - gives the final result
        initAll();
	hidden_layers();
	output_neurons();
}*/

void freeAll(){

    //Hidden layers
    freeM(hidden);
    freeM(hidden_weight);
    freeM(hidden_bias);

    //Output Layer
    freeM(output);
    freeM(output_weight);
    freeM(output_bias);

    //Update weights
    freeM(error_values);
    freeM(derivative_output);
    freeM(derivative_hidden);
}

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
