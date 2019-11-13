#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void printM(Matrix mat) {
    size_t rows = mat.n;
    size_t cols = mat.p;

    printf("%s =\n", mat);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%4g", mat.matrix[i * cols + j]);
        }

        printf("\n");
    }
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
    mat->size = sizeof(mat);

    for(size_t i = 0; i < n;i++)
    {
        for(size_t j = 0; j < p;j++)
        {
            mat->matrix[i*n+j] = 0;
        }
    }
}

void addM(Matrix mat1, Matrix mat2, Matrix *result)
{
    size_t rows = mat1.n;
    size_t cols = mat2.p;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; i < cols;i++)
        {
            result->matrix[i*cols+j] = (mat1.matrix[i*cols+j]) + (mat2.matrix[i*cols+j]);
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
    size_t rows = mat1.n;
    size_t cols = mat2.p;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; i < cols;i++)
        {
            result->matrix[i*cols+j] = mat1.matrix[i*cols+j] * mat2.matrix[i*cols+j];
        }
    }
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
    size_t rows = m.n;
    size_t cols = m.p;

    for (size_t i=0; i<rows; i++)
    {
        for(size_t j=0; j<cols; j++)
        {
            result->matrix[j*rows+i]=m.matrix[i*cols+j];
        }
    }
}

void sigM(Matrix *result, Matrix m)
{
    //TODO
}

//MAIN


#define ROWS1 1
#define COLS1 2

Matrix m1;

initM(m1,1,2);

/*double m1[] =
        {
                1, 2
        };*/

#define ROWS2 2
#define COLS2 2
double m2[] =
        {
                1, 2,
                3, 4
        };

#define ROWS3 3
#define COLS3 2
double m3[] =
        {
                1, 2,
                3, 4,
                5, 6
        };

#define ROWS4 4
#define COLS4 3
double m4[] =
        {
                1, 0, 3,
                1, 2, 0,
                0, 2, 3,
                1, 0, 3
        };

#define ROWS5 3
#define COLS5 4
double m5[] =
        {
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
        };

// Results for the transpositions.
double m1_tr[ROWS1 * COLS1];
double m2_tr[ROWS2 * COLS2];
double m3_tr[ROWS3 * COLS3];
double m4_tr[ROWS4 * COLS4];
double m5_tr[ROWS5 * COLS5];

// Results for the additions.
double m3_plus_m3[ROWS3 * COLS3];
double m4_plus_m5tr[ROWS4 * COLS4];
double m5_plus_m4tr[ROWS5 * COLS5];

// Results for the multiplications.
double m2_times_m2[ROWS2 * COLS2];
double m4_times_m5[ROWS4 * COLS5];
double m5_times_m4[ROWS5 * COLS4];

int main()
{
    printM(m1);
    print_matrix("m2", m2, ROWS2, COLS2);
    print_matrix("m3", m3, ROWS3, COLS3);
    print_matrix("m4", m4, ROWS4, COLS4);
    print_matrix("m5", m5, ROWS5, COLS5);

    transpose(m1,ROWS1,COLS1,m1_tr);
    print_matrix("m1_tr",m1_tr,COLS1,ROWS1);
    transpose(m2,ROWS2,COLS2,m2_tr);
    print_matrix("m2_tr",m2_tr,COLS2,ROWS2);
    transpose(m3,ROWS3,COLS3,m3_tr);
    print_matrix("m3_tr",m3_tr,COLS3,ROWS3);
    transpose(m4,ROWS4,COLS4,m4_tr);
    print_matrix("m4_tr",m4_tr,COLS4,ROWS4);
    transpose(m5,ROWS5,COLS5,m5_tr);
    print_matrix("m5_tr",m5_tr,COLS5,ROWS5);

    add(m3,m3,ROWS3,COLS3,m3_plus_m3);
    print_matrix("m3_plus_m3",m3_plus_m3,ROWS3,COLS3);
    add(m4,m5_tr,ROWS4,COLS4,m4_plus_m5tr);
    print_matrix("m4_plus_m5tr",m4_plus_m5tr,ROWS4,COLS4);
    add(m5,m4_tr,ROWS5,COLS5,m5_plus_m4tr);
    print_matrix("m5_plus_m4tr",m5_plus_m4tr,ROWS5,COLS5);

    mul(m2,m2,ROWS2,COLS2,COLS2,m2_times_m2);
    print_matrix("m2_times_m2",m2_times_m2,ROWS2,COLS2);
    mul(m4,m5,ROWS4,COLS4,COLS5,m4_times_m5);
    print_matrix("m4_times_m5",m4_times_m5,ROWS4,COLS5);
    mul(m5,m4,ROWS5,COLS5,COLS4,m5_times_m4);
    print_matrix("m5_times_m4",m5_times_m4,ROWS5,COLS4);

    return 0;
}



