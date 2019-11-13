//
// Created by Lyrianna on 13/11/2019.
//

#ifndef NN2_MATRIX_H
#define NN2_MATRIX_H

typedef struct Matrix{

    size_t n;
    size_t p;
    size_t size;
    double matrix[];
} Matrix ;


void printM(Matrix mat);
void saveM(FILE out, Matrix mat);
void freeM(Matrix mat);

void initM(Matrix *mat, size_t n, size_t p);

void addM(Matrix mat1, Matrix mat2, Matrix *result);
void mulM(Matrix mat1, Matrix mat2, Matrix *result);
void hadaM(Matrix mat1, Matrix mat2, Matrix *result);
void scalM(Matrix *result, Matrix m, double s);
void dotM(Matrix *result, Matrix a, Matrix b);
void transpM(Matrix *result, Matrix m);
void sigM(Matrix *result, Matrix m);

#endif //NN2_MATRIX_H
