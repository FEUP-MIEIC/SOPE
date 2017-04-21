// PROGRAMA p04.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

#define NUM_THREADS 10

void* myThread(void *arg){
	sleep(1);
	printf("My TID is: %ld or %lu! My PID is: %d\n", syscall(SYS_gettid), pthread_self(), getpid());
	pthread_exit(arg);
}

int main(){
	pthread_t threads[NUM_THREADS];
	int tt[NUM_THREADS];
	int t;
	for(t=0; t< NUM_THREADS; t++){
		tt[t]=t;
		pthread_create(&threads[t], NULL, myThread, (void *)&tt[t]);
	}

	for(t=0; t< NUM_THREADS; t++){
		tt[t]=t;
		int* res;
		pthread_join(threads[t], (void*) &res);
		printf("Thread %d returned!\n", *res);
	}

	pthread_exit(0);
	return 0;
}
