// PROGRAM p05b.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wait.h>
#include <signal.h>

int childrenCaught=0;

void myHandler(int a){
	wait(NULL);
	childrenCaught++;
}

int main(void) 
{ 
	pid_t pid; 
	int i, n;
    signal(SIGCHLD, myHandler);
	for (i=1; i<=30; i++) { 
		pid=fork(); 

		if (pid == 0){ 
			printf("CHILD no. %d (PID=%d) working ... \n",i,getpid()); 
			sleep(2); // child working ... 
			printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());  
			exit(0); 
		} 
	} 
	sleep(1);
	printf("PARENT: I've launched 30 sons. I expect to catch them all, using the SIGCHLD handler I installed.\n"); 

	n=2; while((n=sleep(n+1))!=0); 
	printf("My handler caught %d of %d children.\n", childrenCaught, 30);
	printf("Press ENTER to check out 'ps a'. You should see %d defunct processes...", 30-childrenCaught);
	getc(stdin);
	execlp("ps", "ps", "a", NULL);
	exit(0); 
} 