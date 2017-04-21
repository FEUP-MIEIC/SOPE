// PROGRAMA p02.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define STDERR 2

int n=50000;

void * thrfunc(void * arg){
	int* res=malloc(sizeof(int));
	*res=0;
	fprintf(stderr, "Starting thread %s\n", (char *) arg);
	while(n>0){
		write(STDERR,arg,1);
		(*res)++;
		n--;
	}
	pthread_exit(res);
}

int main(){
	pthread_t ta, tb;
	pthread_create(&ta, NULL, thrfunc, "1");
	pthread_create(&tb, NULL, thrfunc, "2");

	int* temp;
	pthread_join(ta, (void*) &temp);
	printf("\n\nThread 1 printed %d of %d entries.\n", *temp, 50000);

	int* temp2;
	pthread_join(tb, (void*) &temp2);
	printf("Thread 2 printed %d of %d entries.\n", *temp2, 50000);

	printf("sum: %d.\n", *temp+*temp2);
	return 0;
}
