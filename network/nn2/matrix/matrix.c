#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "matrix.h"

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

void freeM(Matrix* mat)
{
    free(mat->matrix);
    free(mat);
}

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

Matrix* addM(Matrix* mat1, Matrix* mat2)
{
    if(mat1->n!= mat2->n || mat1->p != mat2->p)
    {
        errx(1, "ADD : matrices do not have the same dimension. M1(%i,%i) and M2(%i,%i).\n",
                mat1->n,mat1->p,mat2->n,mat2->p);
    }

    size_t rows = mat1->n;
    size_t cols = mat2->p;

    Matrix* result = initM(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; i < cols;i++)
        {
            result->matrix[i*cols+j] = ((mat1->matrix[i*cols+j]) + (mat2->matrix[i*cols+j]));
        }
    }
    return result;
}

Matrix* mulM(Matrix mat1, Matrix mat2)
{
    size_t r1 = mat1.n;
    size_t c1 = mat1.p;
    size_t c2 = mat2.p;

    Matrix* result = initM(r1,c2);

    for(size_t i = 0; i<r1; i++)
    {
        for (size_t j = 0; j<c2; i++)
        {
            for (size_t k = 0; k <c1; k++)
            {
                result->matrix[i*c2+j]+=(mat1.matrix[i*c1+k])*(mat2.matrix[k*c2+j]);
            }
        }
    }
    return result;
}

Matrix* hadaM(Matrix mat1, Matrix mat2)
{
    if(mat1.n!= mat2.n || mat1.p != mat2.p)
    {
        errx(1, "HADAMARD PRODUCT : matrices do not have the same dimension. M1(%i,%i) and M2(%i,%i).\n",
             mat1.n,mat1.p,mat2.n,mat2.p);
    }

    size_t rows = mat1.n;
    size_t cols = mat2.p;

    Matrix* result = initM(rows,cols);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; i < cols;i++)
        {
            result->matrix[i*cols+j] = mat1.matrix[i*cols+j] * mat2.matrix[i*cols+j];
        }
    }
    return result;
}

Matrix* scalM(Matrix m, double s)
{
    size_t rows = m.n;
    size_t cols = m.p;

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

Matrix* dotM(Matrix a, Matrix b)
{
    /*size_t rows = m.n;
    size_t cols = m.p;*/

    /*Matrix* result = initM(TODO);
    //TODO
    return result;*/
}

Matrix* transpM(Matrix *m)
{
    size_t rows = m->p;
    size_t cols = m->n;

    Matrix* result = initM(rows,cols);

    for (size_t i=0; i<rows; i++)
    {
        for(size_t j=0; j<cols; j++)
        {
            result->matrix[j*rows+i] = m->matrix[i*cols+j];
        }
    }
    return result;
}

Matrix* sigM(Matrix m)
{
    //TODO errx

    size_t rows = m.n;
    size_t cols = m.p;

    Matrix* result = initM(rows,cols);
    //TODO
    return result;
}

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