#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"i

void printM(Matrix mat)
{
    //TODO
}

void saveM(FILE out, Matrix mat)
{
    //TODO
}

void freeM(Matrix mat)
{
    //TODO
}

void initM(Matrix *mat, size_t n, size_t p)
{
    mat->n = n;
    mat->p = p;

    for(size_t i = 0; i< mat.n;i++)
    {
        for(size_t j = 0; j < mat.p;j++)
        {
            mat->matrix[i,j] = 0;
        }
    }
}

void addM(Matrix mat1, Matrix mat2, Matrix *result)
{
    size_t rows = mat1.n;
    size_t cols = mat2.p;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; i < cols.p)
        {
            result->matrix[i*cols+j] = mat1[i*cols+j]+ mat2[i*cols+j];
        }
    }
}

void mulM(Matrix mat1, Matrix mat2, Matrix *result)
{
    size_t r1 = mat1.n;
    size_t c1 = mat1.p;
    size_t c2 = mat2.p;

    for (size_t i = 0; i<r1; i++)
    {
        for (size_t j = 0; j<c2; i++)
        {
            for (size_t k = 0; k <c1; k++)
            {
                result->matrix[i*c2+j]+=(mat1.matrix[i*c1+k])*(mat2.matrix[k*c2+j]);
            }
        }
    }
}

void hadaM(Matrix mat1, Matrix mat2, Matrix *result)
{
    //TODO
}

void scalM(Matrix *result, Matrix m, double s)
{
    //TODO
}

void dotM(Matrix *result, Matrix a, Matrix b)
{
    //TODO
}

void transpM(Matrix *result, Matrix m)
{
    //TODO
}

void sigM(Matrix *result, Matrix m)
{
    //TODO
}