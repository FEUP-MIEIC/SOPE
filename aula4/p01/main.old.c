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

	//sleep(30);
	struct timeval tv;
	struct timezone tz;
	int a=gettimeofday(&tv, &tz);
	unsigned long int epoch=tv.tv_sec;
	alarm(30); pause();
	gettimeofday(&tv, &tz);
	while(tv.tv_sec<epoch+30){
		printf("Something woke me up, but it's not my time yet.\nSleeping for another %lu seconds.\n", epoch+30-tv.tv_sec);
		gettimeofday(&tv, &tz);
		alarm(epoch+30-tv.tv_sec);pause();
	}
	//pause();
	printf("Waking up ...\n");
	exit(0);
}
