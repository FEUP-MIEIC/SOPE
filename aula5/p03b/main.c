#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	if(argc!=2){ /******		Error checking 		*****/
		printf("Error! I must get one argument!\n");
		exit(-1);
	}

	int pfd1[2], pfd2[2];
	if(pipe(pfd1)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};
	if(pipe(pfd2)==-1){ /******		Error checking 		*****/
		printf("Error! Could not open pipe!\n");
		exit(-3);
	};

	if(fork()==0){ // child
		close(pfd1[1]); // close write pipe;
		close(pfd1[0]); // close read pipe;
		close(pfd2[0]); // close read pipe;
		dup2(pfd2[1], STDOUT_FILENO);
		execlp("cat", "cat", argv[1], NULL);
		printf("Error calling exec!\n");
		exit(-10);
	}
	close(pfd2[1]);
	if(fork()==0){ // child
		close(pfd2[1]); // close write pipe;
		close(pfd1[0]); // close read pipe;
		dup2(pfd2[0], STDIN_FILENO);
		//dup2(pfd1[1], STDOUT_FILENO);
		execlp("sort", "sort", NULL);
		printf("Error calling exec!\n");
		exit(-10);
	}

	// Parent

	close(pfd1[1]); // close write pipe
	wait(NULL);
	wait(NULL);
	//dup2(STDOUT_FILENO, pfd1[0]);
	return 0;

	char* buf=malloc(100);
	int rr;
	while((rr=read(pfd1[0], buf, 100))>0){
		write(STDOUT_FILENO, buf, rr);
	}

	free(buf);

	return 0;
}
