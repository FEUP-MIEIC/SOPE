#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void cnt(int sig){
	// DO NOTHING AT ALL!
}

struct twoint{
	int op1;
	int op2;
};


int main(){
	int pfd[2];
	
	pipe(pfd);
		
	if(fork()==0){ // child
		close(pfd[1]); // close write pipe;
		//printf("child reporting\n");
		struct twoint a;
		while(read(pfd[0], &a, sizeof(struct twoint)) > 0){
			printf("%d + %d = %d\n", a.op1, a.op2, a.op1+a.op2);
			printf("%d - %d = %d\n", a.op1, a.op2, a.op1-a.op2);
			printf("%d * %d = %lld\n", a.op1, a.op2, (long long)a.op1*a.op2);
			printf("%d / %d = %f\n", a.op1, a.op2, (double)a.op1/a.op2);
			
			kill(getppid(), SIGUSR1);
			
		}
		//printf("Father closed the pipe!\n");
		exit(0);
	}
	
	signal(SIGUSR1, cnt);
	
	close(pfd[0]); // close read pipe
	struct twoint a;
	
	printf("Insert two operands: ");
	while(scanf("%d %d", &a.op1, &a.op2)!=EOF){
		//printf("Read %d %d\n", a.op1, a.op2);
		write(pfd[1], &a, sizeof(struct twoint));
		pause();
		printf("\n");
		printf("Insert two operands: ");
	}
	
	close(pfd[1]); // close read pipe
	wait(NULL);
}