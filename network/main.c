#include <stdio.h>
#include <stdlib.h>
#include "xor_network.h"

int main()
{
	printf("\nThe groupe HELE is happy to show you its XOR machine!\n");
    generate_wgt();
    train_neural();
    save_datas();
    printf("\n");
    return 0;
}
