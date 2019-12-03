#include "matrix.h"
// Created by Néphélie on 13/11/2019.

//Print a matrice on console (DEBUGGED)
void printM(Matrix* mat, char s[])
{
    size_t rows = mat->n;
    size_t cols = mat->p;

    printf("%s =\n", s);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%4g ", mat->matrix[i * cols + j]);
        }

        printf("\n");
    }
}

//Save the space of matrice (NOT
// TODO : to review (save properties of matrices) + do loadM
void saveM(Matrix *mat, bool iscontinuous)
{
    FILE* fichier = NULL;
    if(iscontinuous)
        fichier = fopen("datasaved.txt","a");
    else
        fichier = fopen("datasaved.txt", "w");

    if (fichier != NULL)
    {
        fprintf(fichier,"%ld %ld\n",mat->n,mat->p);
        fwrite(mat->matrix, sizeof(double),mat->sizevector,fichier);
        fputs("\n\n",fichier);

        fclose(fichier);
    }
    else
        errx(1,"SAVEMATRIX : Impossible to open datasaved.txt.");
}

Matrix* loadM(char* filename)
{
    FILE* fichier = fopen(filename,"r");

    if (fichier != NULL)
    {
        size_t size = 28*28;
        double* matrixvalues = malloc(sizeof(double)*size);

        for (int i = 0; i < 28; ++i) {
            for (int j = 0; j < 28; ++j) {
                char e = fgetc(fichier);
                double f = 5;
                //double f = (e == 48) ? 0: 1;
                if (e == 48)
                    f = 0;
                else if (e == 49)
                    f = 1;
                matrixvalues[i*28+j] = f;
            }
            fgetc(fichier);
            fgetc(fichier);

        }

        Matrix* result = initwithvaluesM(28,28, matrixvalues);
        return result;
    }
    else
        errx(1,"LOADM : Impossible to open file.");
}

//Free the space init with the matrice (NOT)
void freeM(Matrix* mat)
{
    free(mat->matrix);
    free(mat);
}

//Init a matrices with no special values as matrices + not defined globally (DEBUGGED)
Matrix* initM(size_t n, size_t p)
{
    size_t size = n*p;

    Matrix* init = malloc(sizeof(Matrix));

    init->n = n;
    init->p = p;
    init->sizevector = size;
    init->matrix = calloc(size, sizeof(double));

    return init;
}


//Add 2 matrices in a new matrice (DEBUGGED)
Matrix* addM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "ADD : matrices do not have the same dimension. M1(%zi*%zi) and M2(%zi*%zi).\n",
             mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols;j++)
        {
            mat1->matrix[i*cols+j] += mat2->matrix[i*cols+j];
        }
    }
    return mat1;
}

//Substract 2 matrices in a new matrix
Matrix* subM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "SUB : matrices do not have the same dimension. M1(%zi*%zi) and M2(%zi*%zi).\n",
             mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols;j++)
        {
            mat1->matrix[i*cols+j] -= mat2->matrix[i*cols+j];
        }
    }
    return mat1;
}

//Multiply 2 matrices (NOT)
Matrix* mulM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->p != mat2->n)
    {
        errx(1, "MUL : mat1 row not same dimension as mat2 col. M1(%zi,%zi) and M2(%zi,%zi).\n",
             mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t r1 = mat1->n;
    size_t c1 = mat1->p;
    size_t c2 = mat2->p;

    Matrix* result = initM(r1,c2);

    for(size_t i = 0; i<r1; i++)
    {
        for (size_t j = 0; j<c2; j++)
        {
            for (size_t k = 0; k <c1; k++)
            {
                result->matrix[i*c2+j]+=(mat1->matrix[i*c1+k])*(mat2->matrix[k*c2+j]);
            }
        }
    }
    return result;
}

//Hadamar Product on matrices (DEBUGGED)
Matrix* dotM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "HADAMARD PRODUCT : matrices do not have the same dimension. M1(%zi,%zi) and M2(%zi,%zi).\n",
             mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols;j++)
        {
            mat1->matrix[i*cols+j] *= mat2->matrix[i*cols+j];
        }
    }
    return mat1;
}

//Scalar product (DEBUGGED)
Matrix* scalM(Matrix* m, double s)
{
    for (size_t i = 0; i < m->sizevector; ++i) {
        m->matrix[i] *= s;
    }
    return m;
}

//Transpose a matrix m (NOT)
Matrix* transpM(Matrix* m)
{
    size_t rows = m->n;
    size_t cols = m->p;

    Matrix* result = initM(cols,rows);

    for (size_t i=0; i<rows; i++)
    {
        for(size_t j=0; j<cols; j++)
        {
            result->matrix[j*rows+i] = m->matrix[i*cols+j];
        }
    }
    return result;
}

//Calculate the sigmoid of each value in matrice (NOT)
Matrix* sigM(Matrix* m, bool is_derivate)
{

    if (!is_derivate)
    {
        for (size_t i = 0; i < m->sizevector; ++i) {
            m->matrix[i] = (1/(1+exp(-(m->matrix[i]))));
        }
    }
    else
    {
        for (size_t i = 0; i < m->sizevector; ++i) {
            m->matrix[i] = (m->matrix[i])*(1-(m->matrix[i]));
        }
    }
    return m;
}

//Computes the softmax of each value in the matrix given
Matrix* softmaxM(Matrix* m){

    double max = m->matrix[0];

    for (size_t i = 0 ; i < m->sizevector;i++)
        if (max < m->matrix[i])
            max = m->matrix[i];

    double sum_of_exp = 0;

    for (size_t i = 0 ; i < m->sizevector;i++)
        sum_of_exp +=exp(m->matrix[i]-max);

    for (size_t j = 0 ; j < m->sizevector; j++)
        m->matrix[j]=exp(m->matrix[j]-max)/sum_of_exp;

    return m;
}

//Init a matrix with special values (DEBUGGED)
Matrix* initwithvaluesM(size_t n, size_t p, double *m)
{
    size_t size = n*p;

    Matrix* init = malloc(sizeof(Matrix));

    init->n = n;
    init->p = p;
    init->sizevector = size;
    init->matrix = m;

    return init;
}

#include <stdio.h>
#include <stdlib.h>

// inline function to swap two numbers
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);

    return buffer;
}

// Implement itoa() function in C
char* itoa(int value, char* buffer, int base)
{
    // consider absolute value of number
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;

        n = n / base;
    }

    // if number is 0
    if (i == 0)
        buffer[i++] = '0';

    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0)
        buffer[i++] = '-';

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}