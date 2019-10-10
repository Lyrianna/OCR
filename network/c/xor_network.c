#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//SIGMOID
double sigmoid( double x)
{
    return (double)(1/(1+exp(-x)));
}

double sigmoid_prime(double x)
{
    return x*(1-x); //return sigmoid(x)*(1-sigmoid(x));
}