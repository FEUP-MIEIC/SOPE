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

struct res{
	int resSum;
	int resSub;
	long long int resPro;
	double resDiv;
};


int main(){
	int pfd1[2];
	int pfd2[2];
	
	pipe(pfd1);
	pipe(pfd2);
		
	if(fork()==0){ // child
		close(pfd1[1]); // close write pipe;
		close(pfd2[0]); // close read pipe;
		//printf("child reporting\n");
		int buf;
		struct twoint a;
		int i=0;
		while(read(pfd1[0], &buf, sizeof(int)) > 0){
			i++;
			if(i%2!=0){
				a.op1=buf;
			}else{
				a.op2=buf;
				printf("%d + %d = %d\n", a.op1, a.op2, a.op1+a.op2);
				printf("%d - %d = %d\n", a.op1, a.op2, a.op1-a.op2);
				printf("%d * %d = %lld\n", a.op1, a.op2, (long long)a.op1*a.op2);
				printf("%d / %d = %f\n", a.op1, a.op2, (double)a.op1/a.op2);
				kill(getppid(), SIGUSR1);
				
			}
		}
		//printf("Father closed the pipe!\n");
		exit(0);
	}
	
	signal(SIGUSR1, cnt);
	
	close(pfd1[0]); // close read pipe
	close(pfd2[1]); // close write pipe
	struct twoint a;
	
	printf("Insert two operands: ");
	while(scanf("%d %d", &a.op1, &a.op2)!=EOF){
		//printf("Read %d %d\n", a.op1, a.op2);
		write(pfd1[1], &a, sizeof(struct twoint));
		pause();
		printf("\n");
		printf("Insert two operands: ");
	}
	
	close(pfd1[1]); // close read pipe
	wait(NULL);
}