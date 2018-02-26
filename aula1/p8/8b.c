#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <sys/times.h>
#include <unistd.h>

#define INVALID_ARGUMENT -1

int main(int argc, char** argv) {
    // get current clock ticks (relative to some arbitrary point in the past like system boot time)
    clock_t t_init, t_end;
    struct tms t;
    t_init = times(&t);

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

    // get current clock ticks and CPU time, stored in previously declared struct tms
    t_end = times(&t);
    long ticks = sysconf(_SC_CLK_TCK);
    printf("CPU time (user): %ld\n", t.tms_cutime/ticks);
    printf("CPU time (system): %ld\n", t.tms_cstime/ticks);
    printf("Real time: %ld\n", (t_end-t_init)/ticks);
/*
    printf("System time: %4.2f s\n", (double)t.tms_stime/ticks);
 printf("Children user time: %4.2f s\n", (double)t.tms_cutime/ticks);
 printf("Children system time: %4.2f s\n", (double)t.tms_cstime/ticks); */
}