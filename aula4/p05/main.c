// PROGRAM p05.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wait.h>
#include <signal.h>


int main(void) 
{ 
	pid_t pid; 
	int i, n, status;
    signal(SIGCHLD, SIG_IGN);
	for (i=1; i<=3; i++) { 
		pid=fork(); 

		if (pid == 0){ 
			printf("CHILD no. %d (PID=%d) working ... \n",i,getpid()); 
			sleep(i*7); // child working ... 
			printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());  
			exit(0); 
		} 
	} 
	for (i=1 ;i<=4; i++ ) {  
		printf("PARENT: working hard (task no. %d) ...\n",i); 
		n=20; while((n=sleep(n))!=0); 
		printf("PARENT: end of task no. %d\n",i); 
	} 
	exit(0); 
} 