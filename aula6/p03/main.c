// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

void *PrintHello(void *threadnum){
	printf("Hello from thread no. %d!\n", *(int *) threadnum);
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[NUM_THREADS];
	int tt[NUM_THREADS];
	int t;
	for(t=0; t< NUM_THREADS; t++){
		tt[t]=t;
		printf("Creating thread %d\n", t);
		pthread_create(&threads[t], NULL, PrintHello, (void *)&tt[t]);
	}
	pthread_exit(0);

	// exit(0); // a chamada pthread_exit é a única que não termina as threads-filho do main.
}
