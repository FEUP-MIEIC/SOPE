/**

This was a nice try, but unnecessary.
See man 3 sleep, RETURN VALUE section.

*/

// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

void sigint_handler(int signo){
	printf("In SIGINT handler ...\n");
}

int main(void){

	if (signal(SIGINT,sigint_handler) < 0){
		fprintf(stderr,"Unable to install SIGINT handler\n");
		exit(1);
	}

	printf("Sleeping for 30 seconds ...\n");
	int tr=10;
	//sleep(30);
	while(tr=sleep(tr))
		sleep(tr);
	printf("Waking up ...\n");
	exit(0);
}
