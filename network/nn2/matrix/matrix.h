//
// Created by Lyrianna on 13/11/2019.
//

#ifndef NN2_MATRIX_H
#define NN2_MATRIX_H

typedef struct Matrix{

    size_t n;
    size_t p;
    size_t sizevector;
    double *matrix;
} Matrix ;


void printM(Matrix mat);
void saveM(Matrix mat);
void freeM(Matrix* mat);

Matrix* initM(size_t n, size_t p);

Matrix* addM(Matrix mat1, Matrix mat2);
Matrix* mulM(Matrix mat1, Matrix mat2);
Matrix* hadaM(Matrix mat1, Matrix mat2);
Matrix* scalM(Matrix m, double s);
Matrix* dotM(Matrix a, Matrix b);
Matrix* transpM(Matrix *m);
Matrix* sigM(Matrix m);

#endif //NN2_MATRIX_H
