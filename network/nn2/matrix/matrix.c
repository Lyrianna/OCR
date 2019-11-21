#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "matrix.h"

// Created by Néphélie on 13/11/2019.

//Print a matrice on console (DEBUGGED)
void printM(Matrix* mat, char s[]) {
    size_t rows = mat->n;
    size_t cols = mat->p;

    printf("%s =\n", s);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%4g", mat->matrix[i * cols + j]);
        }

        printf("\n");
    }
}

//Save the space of matrice (NOT
// TODO : to review (save properties of matrices) + do loadM
void saveM(Matrix mat)
{
    FILE* fichier = NULL;
    fichier = fopen("datasaved.txt", "w");

    if (fichier != NULL)
    {
        for (int i = 0; i < mat.n; i++)
        {
            for (int j = 0; j < mat.p; ++j) {
                fprintf(fichier,"%lf ",mat.matrix[i*mat.n+j]);
            }
        }

        fclose(fichier);
    }
}

//Free the space init with the matrice (NOT)
void freeM(Matrix* mat)
{
    free(mat->matrix);
    free(mat);
}

//Init a matrices with no special values (DEBUGGED)
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
void initM2(Matrix *mat, size_t n, size_t p)
{
    size_t size = n*p;

    mat = malloc(sizeof(Matrix));

    mat->n = n;
    mat->p = p;
    mat->sizevector = size;
    mat->matrix = calloc(size, sizeof(double));

    return init;
}

//Add 2 matrices in a new matrice (DEBUGGED)
Matrix* addM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "ADD : matrices do not have the same dimension. M1(%i*%i) and M2(%i*%i).\n",
                mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    Matrix* result = initM(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols;j++)
        {
            result->matrix[i*cols+j] = ((mat1->matrix[i*cols+j]) + (mat2->matrix[i*cols+j]));
        }
    }
    return result;
}

//Substract 2 matrices in a new matrix
Matrix* subM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "ADD : matrices do not have the same dimension. M1(%i*%i) and M2(%i*%i).\n",
                mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    Matrix* result = initM(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols;j++)
        {
            result->matrix[i*cols+j] = ((mat1->matrix[i*cols+j]) - (mat2->matrix[i*cols+j]));
        }
    }
    return result;
}

//Multiply 2 matrices (DEBUGGED)
Matrix* mulM(Matrix* mat1, Matrix* mat2)
{
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
Matrix* hadaM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "HADAMARD PRODUCT : matrices do not have the same dimension. M1(%i,%i) and M2(%i,%i).\n",
             mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    Matrix* result = initM(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols;j++)
        {
            result->matrix[i*cols+j] = mat1->matrix[i*cols+j] * mat2->matrix[i*cols+j];
        }
    }
    return result;
}

//Scalar product (NOT)
Matrix* scalM(Matrix* m, double s)
{
    size_t rows = m->n;
    size_t cols = m->p;

    Matrix* result = initM(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; i < cols;i++)
        {
            result->matrix[i*cols+j] = s*result->matrix[i*cols+j];
        }
    }
    return result;
}

//Transpose a matrix m (DEBUGGED)
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
/*
//Sigmoid functions
double sigmoid( double x)
{
    return (double)(1/(1+exp(-x)));
}

double sigmoid_derivate(double x)
{

    return x*(1-x);
}
 */

//Calculate the sigmoid of each value in matrice (NOT)
Matrix* sigM(Matrix* m)
{
    size_t rows = m->n;
    size_t cols = m->p;

    Matrix* result = initM(rows,cols);
    //TODO
    return result;
}

//Init a matrix with special values (DEBUGGED)
Matrix* initwithvaluesM(size_t n, size_t p, double* m)
{
    size_t size = n*p;

    Matrix* init = malloc(sizeof(Matrix));

    init->n = n;
    init->p = p;
    init->sizevector = size;
    init->matrix = m;

    return init;
}
