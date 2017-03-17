// PROGRAMA p03.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


int way=1; // 1 is up, 0 is down;


void sigusr_handler(int signo){
	if(signo==SIGUSR1){
		way=1;
	}else{
		way=0;
	}
}

int main(void){

	if (signal(SIGUSR1, sigusr_handler) < 0){
		fprintf(stderr, "Unable to install SIGUSR1 handler\n");
		exit(1);
	}

	if (signal(SIGUSR2, sigusr_handler) < 0){
		fprintf(stderr, "Unable to install SIGUSR2 handler\n");
		exit(1);
	}
	int v=0;
	while(1){
		if(way){
			v++;
		}else{
			v--;
		}
		printf("v: %d\n", v);
		usleep(1000000);
	}

	exit(0);
}
