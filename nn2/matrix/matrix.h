//
// Created by Néphélie on 13/11/2019.
//
#ifndef NN2_MATRIX_H
#define NN2_MATRIX_H

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

typedef struct Matrix{

    size_t n;
    size_t p;
    size_t sizevector;
    double *matrix;
} Matrix ;


void printM(Matrix* mat, char s[]);
void saveM(Matrix *mat, bool iscontinuous);
Matrix* loadM(char* filename);
void freeM(Matrix* mat);

Matrix* initM(size_t n, size_t p);
void initM2(Matrix *mat, size_t n, size_t p);

Matrix* addM(Matrix* mat1, Matrix* mat2);
Matrix* subM(Matrix* mat1, Matrix* mat2);
Matrix* mulM(Matrix* mat1, Matrix* mat2);
Matrix* dotM(Matrix* mat1, Matrix* mat2);
Matrix* scalM(Matrix* m, double s);
Matrix* transpM(Matrix* m);
Matrix* sigM(Matrix* m, bool is_derivate);

Matrix* initwithvaluesM(size_t n, size_t p, double *m);

#endif //NN2_MATRIX_H
