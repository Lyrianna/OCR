#include "networkV2.h"
#include "../ImageAnalysis/TestOCR/letter.h"

char* ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ0123456789,.";

//NEURAL NETWORK - Sarah and Nephelie//

float lr = 0.1; //learning rate

//inputs
size_t inputNb = 784;//number of neurons in the input
Matrix *input, *wanted_output;

//hidden layer
size_t hiddenNb = 40;//number of hidden neurons
Matrix *hidden, *hidden_weight, *hidden_bias;

//output layer
size_t outputNb = 64;//output neurons
Matrix *output, *output_weight, *output_bias;

//matrices for the gradient
Matrix *derivative_output, *derivative_hidden;

Matrix *error_values;

Matrix matarray[7] = {0};
Matrix* alphabettrain[64] = {0};

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
    for (size_t i = 0; i < (hidden_weight->sizevector) ; i++) 
        hidden_weight->matrix[i] =(rand() / (float) RAND_MAX * (2) - 1);
    for (size_t j = 0 ; j < (output_weight->sizevector) ;j++)
	    output_weight->matrix[j] = (rand()/ (float)RAND_MAX*(2)-1);
    for (size_t k = 0 ; k < (hidden_bias->sizevector); k++)
	    hidden_bias->matrix[k] = (rand()/ (float)RAND_MAX*(2)-1);
	for (size_t g = 0; g < (output_bias->sizevector); g++)
	    output_bias->matrix[g] = (rand()/ (float)RAND_MAX*(2)-1);
}

//Feed forward

void hidden_layers(){

    hidden = mulM(input, hidden_weight);
	hidden = sigM(addM(hidden, hidden_bias),false);
}

void output_neurons()
{
	output = mulM(hidden, output_weight);
	output = sigM(addM(output, softmaxM(output_bias)),false);
}

//Backpropagation
void error() //error for each case
{
	error_values = subM(wanted_output,output);
}

void derivatives()//repercution of the error for each layer
{
	Matrix *temp1,*temp2;
	derivative_output = dotM(error_values,sigM(output,true));
	temp1 = transpM(output_weight);
	temp2 = mulM(derivative_output, temp1);
    derivative_hidden = dotM(sigM(hidden, true), temp2);
    freeM(temp1);
    freeM(temp2);
}

void update_weights()//update of the different matrices
{
	Matrix *temp1,*temp2;
	//update of the weight btw input and hidden layer
	//hidden_w += dot(input, derivative_hidden)*lr
	temp1 = transpM(input);
	temp2 = mulM(temp1, derivative_hidden);
	hidden_weight = addM(hidden_weight, scalM(temp2, lr));
	freeM(temp1);
	freeM(temp2);

	//update of the bias of the hidden layer
	//hidden_bias += dot(sigmoid(hidden_bias), derivative_hidden)*lr
	hidden_bias = addM(hidden_bias, scalM(dotM(sigM(hidden_bias,false), derivative_hidden), lr));
	
   	//update of the weight btw hidden and output layer
   	//output_w += dot(input, derivative_output)*lr
   	temp1 = transpM(hidden);
   	temp2 = mulM(temp1, derivative_output);
	output_weight = addM(output_weight, scalM(temp2, lr));
    freeM(temp1);
	freeM(temp2);
	//update of the bias of the output layer
	//output_bias += dot(sigmoid(output_bias), derivative_output)*lr))
	output_bias = addM(output_bias, scalM(dotM(softmaxM(output_bias), derivative_output), lr));
}

//training
void train_neural(bool istherearg, unsigned long int epochuser)
{
    FILE* fichier = fopen("../datasaved.txt","r");
    
    if (fichier != NULL)
    {
        load_datas(matarray,fichier);
    }
    else
    {
        initAll();
        generate_wgt();
    }

    unsigned long int k = 0;
    unsigned long int epoch = 10000;

    if (istherearg) //put the user's epoch
        epoch = epochuser;

    //put all matrices of train in an array
    for (int j = 0; j < 64; ++j) {
        printf("Init Alphabet\n");

	 //path to folder with writing
        char str[32] = "./BDI/Training/arialalphabet/";
        char str2[3];

	 //number of matrice to write (in the ordrer of ALPHABET) put in str2
        //sprintf(str2,"%u",j);
        itoa(j,str2,10);
        strcat(str,str2); //concatenate the 2 str
        printf("str = %s\n",str);

        alphabettrain[j] = loadM(str); //load the matrice with the path
    }

    while ( k < epoch)
    {
        printf(" ----- EPOCH NUMBER %lu -----\n",k);
        for (int i = 0; i < 64; ++i) {
            input = alphabettrain[i];

            //the matrix formation is change to fit the NN
            input->p = (input->n)*(input->p);
            input->n = 1;

            wanted_output = createouttrain(i);

            hidden_layers();
            output_neurons();
            error();
            derivatives();
            update_weights();
        }

        k+=1;
    }

    printM(output, "outputttt");
    save_datas();//saves the important datas of the NN
    printf("saved datas\n");
    freeAll();//frees all the matrix used in the NN
}

//create the wantedouput based on the i of its place in the output layer
Matrix* createouttrain(int i)
{
    Matrix* result = initM(1,64);
    result->matrix[i] = 1;
    return result;
}

void ocr(Matrix* in)
{
    FILE* fichier2 = fopen("datasaved.txt","r");
    load_datas(matarray,fichier2);
    printf("1");
    input->n = 1;//the matrix formation is change to fit the NN
    input->p = 784;
    bool isspace = false;
    
    printf("2");
    initAll();
    hidden_layers();
    output_neurons();
    printf("3");
    int max = 0;

    for (size_t i = 0; i < output->sizevector; ++i) {
        if (output->matrix[i]>output->matrix[max])
        {
            max = i;
        }

    FILE* fichier = fopen("text.txt", "a");
        if (fichier!=NULL)
        {
            for (size_t k = 0; k < input->sizevector; ++k)
            {
                if (input->matrix[k] == 0)
                    isspace = true;
            }
            if (isspace)
            {
                fputs(" ",fichier);
            }
            else
            {
                for (int j = 0; j < 64; ++j) {
                    if (j==max)
                    {
                        fputs(&ALPHABET[i],fichier);
                    }
                }
            }
        }
    }
	freeAll();
}

void freeAll(){

    freeM(input);
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
    freeM(wanted_output);

    for (int i = 0; i < 7; ++i) {
        freeM(&matarray[i]);
    }
    for (int j = 0; j < 64; ++j) {
        freeM(alphabettrain[j]);
    }

}

void save_datas()
{
    saveM(hidden,false);
    saveM(hidden_weight,true);
    saveM(hidden_bias,true);
    saveM(output_weight,true);
    saveM(output_bias,true);
    saveM(derivative_output,true);
    saveM(derivative_hidden,true);
}



int taille[2] = {0};

void load_datas(Matrix* matrixarray[], FILE* fichier)
{

    if (fichier != NULL)
    {
        int i = 0;

        while (i<7)
        {
            int mn = fscanf(fichier, "%d %d",&taille[0],&taille[1]);
	    printf("use fscanf: %i", mn);
            int size = taille[0]*taille[1];
            fgetc(fichier);
            double* matrixvalues = malloc(sizeof(double)*size);


            int pt = fread(matrixvalues, sizeof(double),size,fichier);
	        printf("use fread = %i", pt);

            matrixarray[i] = initwithvaluesM(taille[0],taille[1], matrixvalues);

            i++;

            fgetc(fichier);
            fgetc(fichier);
        }

        fclose(fichier);

        hidden = matrixarray[0];
        hidden_weight = matrixarray[1];
        hidden_bias = matrixarray[2];
        output_weight = matrixarray[3];
        output_bias = matrixarray[4];
        derivative_output = matrixarray[5];
        derivative_hidden = matrixarray[6];
    }
    else
        errx(1,"LOADMATRIX : No file datasaved.txt.");
}
