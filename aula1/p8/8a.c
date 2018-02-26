#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define INVALID_ARGUMENT -1

int main(int argc, char** argv) {
    // set a seed that changes everytime the program runs (time when the program is launched for example)
    srand(time(NULL));

    // extract the arguments
    unsigned int n1, n2;
    if(argc == 3) {
        n1 = atoi(*(argv+1));
        n2 = atoi(*(argv+2));
    } else {
        exit(INVALID_ARGUMENT);
    }

    // declare needed variables to hold pseudo-random number generated and an iteration counter
    unsigned int randNum, iter = 0;
    do {
        randNum = rand() % n1;
        printf("%-5d iter:%d\n", randNum, iter++);
    } while(randNum != n2);
}