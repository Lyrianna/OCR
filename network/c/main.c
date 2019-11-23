#include <stdio.h>
#include <stdlib.h>
#include "xor_network.c"

int main()
{
    generate_wgt();
    train_neural();
    start_input();
}