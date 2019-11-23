#include "matrix.h"

#define ROWS1 1
#define COLS1 2
double m1[] =
        {
                1, 2
        };

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
    //TODO - INIT
    Matrix* mat1 = initwithvaluesM(ROWS1,COLS1,m1);
    Matrix* mat2 = initwithvaluesM(ROWS2,COLS2,m2);
    Matrix* mat3 = initwithvaluesM(ROWS3,COLS3,m3);
    Matrix* mat4 = initwithvaluesM(ROWS4,COLS4,m4);
    Matrix* mat5 = initwithvaluesM(ROWS5,COLS5,m5);

    /*printM(mat1,"mat1");
    printM(mat2,"mat2");
    printM(mat3,"mat3");
    printM(mat4,"mat4");
    printM(mat5,"mat5");*/

    //TODO - TRANSPOSE MATRICE
    Matrix* mat1_tr = transpM(mat1);
    Matrix* mat2_tr = transpM(mat2);
    Matrix* mat3_tr = transpM(mat3);
    Matrix* mat4_tr = transpM(mat4);
    Matrix* mat5_tr = transpM(mat5);


    /*printM(mat1_tr,"mat1_tr");
    printM(mat2_tr,"mat2_tr");
    printM(mat3_tr,"mat3_tr");
    printM(mat4_tr,"mat4_tr");
    printM(mat5_tr,"mat5_tr");*/

    //TODO - ADD MATRICES
    Matrix* mat3_plus_mat3 = addM(mat3,mat3);
    Matrix* mat4_plus_mat5tr = addM(mat4,mat5_tr);
    Matrix* mat5_plus_mat4tr = addM(mat5,mat4_tr);

    /*printM(mat3_plus_mat3, "mat3_plus_mat3");
    printM(mat4_plus_mat5tr,"mat4_plus_mat5tr");
    printM(mat5_plus_mat4tr,"mat5_plus_mat4tr");*/

    //TODO - MULTIPLY MATRICES
    Matrix* mat2_times_mat2 = mulM(mat2,mat2);
    Matrix* mat4_times_mat5 = mulM(mat4,mat5);
    Matrix* mat5_times_mat4 = mulM(mat5,mat4);

    /*printM(mat2_times_mat2,"mat2_times_mat2");
    printM(mat4_times_mat5,"mat4_times_mat5");
    printM(mat5_times_mat4,"mat5_times_mat4");*/

    //TODO - HADAMAR PRODUCT
    Matrix* mat3_had_mat3 = dotM(mat3,mat3);
    Matrix* mat4_had_mat5tr = dotM(mat4,mat5_tr);
    Matrix* mat5_had_mat4tr = dotM(mat5,mat4_tr);

    /*printM(mat3_had_mat3, "mat3_had_mat3");
    printM(mat4_had_mat5tr,"mat4_had_mat5tr");
    printM(mat5_had_mat4tr,"mat5_had_mat4tr");*/

    //TODO - SIGMOID ON MATRICES
    /*mat1 = sigM(mat1,false);
    printM(mat1,"mat1");
    mat1 = sigM(mat1,true);
    printM(mat1,"mat1");*/

    saveM(mat1,false);
    saveM(mat2,true);
    saveM(mat3,true);
    saveM(mat4,true);
    saveM(mat5,true);
    saveM(mat3_plus_mat3,true);
    saveM(mat3_plus_mat3,true);
    saveM(mat5_times_mat4,true);

    return 0;
}
